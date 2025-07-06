#include"schroed_1d.h"
#include <emscripten.h>

int vhoehe;
int vbreite;
int vektorlaenge;
void* neuvek;
void* neupot;
void* altpot;
void* mittelpot;
void* altvek;
void* altpot;
unsigned char* grafik;

float zeitschritt;

paramvektorwandel schroed_wandel;
paramvektorwandel add_wandel;

doppelzustand vek;
doppelzustand pot;

int aktuelle_pot_nummer;

zersetzungsplan zerp;
arbeiter rungekutta;

float rungematrix[14] = rungekuttamatrix_4;

fdef(euler_1D_pot_vektoraenderung, paramvektorwandel, euler_1D_pot_vektoraenderung_args, paramvektorwandel_args, void){
    float complex * alt = arg.alt;
    float complex * neu = arg.neu;
    float * altpot = selbst->potential->alt;
    float * neupot = selbst->potential->neu;
    float param = arg.parameter;
    size_t laenge = selbst->vektorlaenge;
    float zeitschritt = selbst->zeitschritt;
    int i;
    for(i = 2;i<laenge;i++){
        neu[i-1] = eulerpot_plus(alt[i-2], alt[i-1], alt[i], zeitschritt, altpot[i], neupot[i], param);
    }
}

fdef(euler_2D_pot_vektoraenderung, paramvektorwandel, euler_2D_pot_vektoraenderung_args, paramvektorwandel_args, void){
    float complex * alt = arg.alt;
    float complex * neu = arg.neu;
    float * altpot = selbst->potential->alt;
    float * neupot = selbst->potential->neu;
    float param = arg.parameter;
    size_t hoehe = selbst->vektorhoehe;
    size_t breite = selbst->vektorbreite;
    float zeitschritt = selbst->zeitschritt;
    int x;
    int y;
    for(y = 2;y<vhoehe;y++){
		for(x = 2;x<vbreite;x++){
			neu[(y-1)*vbreite+(x-1)] = eulerpot_plus(alt[(y-2)*vbreite+(x-1)] + alt[(y-1)*vbreite+(x-2)], 2*alt[(y-1)*vbreite+(x-1)], alt[(y)*vbreite+(x-1)] + alt[(y-1)*vbreite+(x)], zeitschritt, altpot[(y-1)*vbreite+(x-1)], neupot[(y-1)*vbreite+(x-1)], param);
		}
	}
}

EMSCRIPTEN_KEEPALIVE
int euler_2D_pot_vorbereiten(int breite_arg,int hoehe_arg, void* grafik_arg, void* vek_0, void* vek_1, void* pot_0, void* pot_1, float zeitschritt_arg){
	vbreite = breite_arg;
	vhoehe = hoehe_arg;
	vektorlaenge = vbreite*vhoehe;
	grafik = grafik_arg;
	altvek = vek_0;
	altpot = pot_0;
	neuvek = vek_1;
	neupot = pot_1;
	
	zeitschritt = zeitschritt_arg;
	
	vek = (doppelzustand){altvek, neuvek};
	pot = (doppelzustand){altpot, neupot};

	schroed_wandel = euler_2D_pot_vektoraenderung_neu((euler_2D_pot_vektoraenderung_args){vhoehe, vbreite, &pot, zeitschritt_arg});
	add_wandel = floatvektoraddieren_neu(vektorlaenge*2);
	
	zerp = neuerzersetzungsplan();
	rungekutta = macherungekutta_neu(&altvek, &neuvek, 4, vektorlaenge*sizeof(float complex), schroed_wandel, add_wandel, rungematrix, &zerp);
	
	int aktuelle_pot_nummer = 0;
	
	EM_ASM({
		console.log('I received: ' + $0);
	}, 22);
	
	return aktuelle_pot_nummer;
}

EMSCRIPTEN_KEEPALIVE
int iteration(){
	int i =0;
	for(i=0;i<5;i++){
		arbeiter_f(&rungekutta, NULL);
		void* temp = altpot;
		altpot = neupot;
		neupot = temp;
		memcpy(neupot, altpot, vektorlaenge*sizeof(float));
		
		temp = altvek;
		altvek = neuvek;
		neuvek = temp;
		aktuelle_pot_nummer = (aktuelle_pot_nummer+1)%2;
	}
	float complex * vek2d = neuvek;
	float * pot2d = neupot;
	
	int x;
    int y;
    for(y = 0;y<vhoehe;y++){
		for(x = 0;x<vbreite;x++){
			if(creal(vek2d[y*vbreite+x])<0)
				grafik[(y*vbreite+x)*4]=255;
			else
				grafik[(y*vbreite+x)*4]=0;
		}
	}
	
	return aktuelle_pot_nummer;
}


