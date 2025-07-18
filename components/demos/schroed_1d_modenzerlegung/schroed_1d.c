#include"schroed_1d.h"
#include <emscripten.h>

int vektorlaenge;
void* neuvek;
void* neupot;
void* altpot;
void* mittelpot;
void* altvek;
void* altpot;
void* betrquad;

float* zeitschritt;
float* laplace_gewichtung;

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
	float laplace_gewichtung = selbst -> laplace_gewichtung;
	float param = arg.parameter;
	size_t laenge = selbst->vektorlaenge;
	int i;
	for(i = 2;i<laenge;i++){
	neu[i-1] = eulerpot_plus(alt[i-2], alt[i-1], alt[i], altpot[i], neupot[i], param, laplace_gewichtung);
	}
}

EMSCRIPTEN_KEEPALIVE
int euler_1D_doppel_vorbereiten(int vektorlaenge_arg, void* vek_0, void* vek_1, void* betr_quad, void* pot_0, void* pot_1, float zeitschritt_arg, float laplace_gewicht){
	vektorlaenge = vektorlaenge_arg;
	altvek = vek_0;
	altpot = pot_0;
	neuvek = vek_1;
	neupot = pot_1;
	betrquad = betr_quad;
	
	float zeitschr = zeitschritt_arg;
	
	vek = (doppelzustand){altvek, neuvek};
	pot = (doppelzustand){altpot, neupot};

	schroed_wandel = euler_1D_pot_vektoraenderung_neu((euler_1D_pot_vektoraenderung_args){vektorlaenge, &pot, laplace_gewicht});
	laplace_gewichtung = &((euler_1D_pot_vektoraenderung_args*)schroed_wandel.inhalt)->laplace_gewichtung;
	add_wandel = floatvektoraddieren_neu(vektorlaenge*2);
	
	zerp = neuerzersetzungsplan();
	rungekutta = macherungekutta_neu(&altvek, &neuvek, 4, vektorlaenge*sizeof(float complex), schroed_wandel, add_wandel, rungematrix, zeitschr, &zerp);
	zeitschritt = &((rungekuttadetails*)rungekutta.inhalt)->zeitschritt;
	
	int aktuelle_pot_nummer = 0;
	
	EM_ASM({
		console.log('I received: ' + $0);
	}, 22);
	
	return aktuelle_pot_nummer;
}

EMSCRIPTEN_KEEPALIVE
void laplace_gewichtung_aendern(float neu){
	*laplace_gewichtung = neu;
}
EMSCRIPTEN_KEEPALIVE
void zeitschritt_aendern(float neu){
	*zeitschritt = neu;
}
EMSCRIPTEN_KEEPALIVE
int iteration(int anzahl){
	int i =0;
	for(i=0;i<anzahl;i++){
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
	float complex * vekt = neuvek;
	float * quad = betrquad;
	for(i = 0; i < vektorlaenge; i++)
		quad[i] = creal(vekt[i]) * creal(vekt[i]) + cimag(vekt[i]) * cimag(vekt[i]);
	return aktuelle_pot_nummer;
}

//float dreh = t*(PI/L)²/(2m)
EMSCRIPTEN_KEEPALIVE
void SchwingungsZerlegung(float complex * inparr, int laenge, float complex * outarr, float dreh, int ordnung){
	int n;
	int i;
	float complex integr;
	float complex winkel;
	float schritt;
	int lminuseins = (laenge - 1);
	for(n=1; n<=ordnung; n++){
		winkel = exp(dreh * n*n * I);
		schritt = n * M_PI / lminuseins;
		integr = 0;
		for(i = 0; i < laenge; i++){
			integr += sin(i*schritt)*inparr[i]*winkel;
		}
		outarr[n] = integr * 2 / lminuseins;
	}
}

//float dreh = t*(PI/L)²/(2m)
EMSCRIPTEN_KEEPALIVE
void SchwingungsZusammensetzung(float complex * inparr, float complex * outarr, int laenge, float dreh, int ordnung){
	int n;
	int i;
	float complex winkel;
	float schritt;
	memset(outarr, 0, sizeof(float complex) * laenge);
	int lminuseins = (laenge - 1);
	for(n = 1; n<=ordnung; n++){
		winkel = exp((-dreh) * n*n * I);
		schritt = n * M_PI / lminuseins;
		for(i = 0; i < laenge; i++){
			outarr[i] += sin(i*schritt)*inparr[n]*winkel;
		}
	}
}

//float dreh = t*(PI/L)²/(2m)
EMSCRIPTEN_KEEPALIVE
void ZusammensetzungsAenderung(float complex * inparr, int laenge, float complex * outarr, int vonx, int zux, float complex vony, float complex zuy, float dreh, int ordnung){
	
}


