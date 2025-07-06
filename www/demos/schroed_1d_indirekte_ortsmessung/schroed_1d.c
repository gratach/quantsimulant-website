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
float* kopplungsstaerke;
int* gekoppelt;
int* messort;
int* ortsunschaerfe;

paramvektorwandel schroed_wandel;
paramvektorwandel add_wandel;

doppelzustand vek;
doppelzustand pot;

int aktuelle_pot_nummer;

arbeiter runge;

float rungematrix[14] = rungekuttamatrix_4;

int main(int count, char ** args){
	EM_ASM( bereit() );
	return 0;
}

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
fdef(euler_1D_pot_ortsmessung_vektoraenderung, paramvektorwandel, euler_1D_pot_ortsmessung_vektoraenderung_args, paramvektorwandel_args, void){
	float complex * alt = arg.alt;
	float complex * neu = arg.neu;
	float * altpot = selbst->potential->alt;
	float * neupot = selbst->potential->neu;
	float laplace_gewichtung = selbst -> laplace_gewichtung;
	float param = arg.parameter;
	int ort = selbst->ort;
	int unsch = selbst->ortsunschaerfe;
	int kopp = selbst->gekoppelt;
	float complex kopplung = selbst->kopplungsstaerke;
	size_t laenge = selbst->vektorlaenge;
	int i;
	for(i = 2;i<laenge;i++){
	neu[i-1] = eulerpot_plus(alt[i-2], alt[i-1], alt[i], altpot[i], neupot[i], param, laplace_gewichtung);
	}
	//neu[55] = I;
	neu = neu + laenge;
	alt = alt + laenge;
	for(i = 2;i<laenge;i++){
		neu[i-1] = eulerpot_plus(alt[i-2], alt[i-1], alt[i], altpot[i], neupot[i], param, laplace_gewichtung);
	}
	if(kopp > 0){
		int anfang =ort - unsch / 2;
		anfang = anfang > 1 ? anfang:1;
		int ende =ort + unsch / 2 + 1;
		ende = ende < laenge - 2 ? ende : laenge - 2;
		for(i = anfang; i < ende; i++){
			neu[i] += alt[i - laenge]*kopplung * I;
			neu[i - laenge] += alt[i]*kopplung* I;
		}
	}
}

EMSCRIPTEN_KEEPALIVE
int euler_1D_doppel_vorbereiten(int vektorlaenge_arg, void* vek_0, void* vek_1, void* betr_quad, void* pot_0, void* pot_1, float zeitschritt_arg, float laplace_gewicht){
	EM_ASM({
		console.log('I received: ' + $0);
	}, 27);

	vektorlaenge = vektorlaenge_arg;
	altvek = vek_0;
	altpot = pot_0;
	neuvek = vek_1;
	neupot = pot_1;
	betrquad = betr_quad;
	
	float zeitschr = zeitschritt_arg;
	
	vek = (doppelzustand){altvek, neuvek};
	pot = (doppelzustand){altpot, neupot};

	schroed_wandel = euler_1D_pot_ortsmessung_vektoraenderung_neu((euler_1D_pot_ortsmessung_vektoraenderung_args){vektorlaenge, &pot, laplace_gewicht,0, 800, 200, 0.003 + 0*I});
	laplace_gewichtung = &((euler_1D_pot_ortsmessung_vektoraenderung_args*)schroed_wandel.inhalt)->laplace_gewichtung;
	gekoppelt = &((euler_1D_pot_ortsmessung_vektoraenderung_args*)schroed_wandel.inhalt)->gekoppelt;
	messort = &((euler_1D_pot_ortsmessung_vektoraenderung_args*)schroed_wandel.inhalt)->ort;
	kopplungsstaerke = &((euler_1D_pot_ortsmessung_vektoraenderung_args*)schroed_wandel.inhalt)->kopplungsstaerke;
	ortsunschaerfe = &((euler_1D_pot_ortsmessung_vektoraenderung_args*)schroed_wandel.inhalt)->ortsunschaerfe;
	add_wandel = floatvektoraddieren_neu(vektorlaenge*2*2);
	
	int ord = 4;
	size_t sizeofvector = vektorlaenge*sizeof(float complex)*2;
	void** tempvektoren = malloc(sizeof(tempvektoren)*ord);
	int i;
	for(i = 0; i<ord; i++)
		tempvektoren[i] = malloc(sizeofvector);
	runge = rungekutta_neu((rungekuttadetails){&altvek, &neuvek, ord, tempvektoren, sizeofvector, schroed_wandel, add_wandel, rungematrix, zeitschr});
	
	zeitschritt = &((rungekuttadetails*)runge.inhalt)->zeitschritt;
	
	int aktuelle_pot_nummer = 0;
	
	
	
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
void kopplung_aendern(float neu){
	*gekoppelt = neu;
}
EMSCRIPTEN_KEEPALIVE
void ortsunschaerfe_aendern(float neu){
	*ortsunschaerfe = neu;
}
EMSCRIPTEN_KEEPALIVE
void messort_aendern(float neu){
	*messort = neu;
}
EMSCRIPTEN_KEEPALIVE
void kopplungsstaerke_aendern(float neu){
	*kopplungsstaerke = neu;
}
EMSCRIPTEN_KEEPALIVE
int iteration(int anzahl){
	int i =0;
	for(i=0;i<anzahl;i++){
		arbeiter_f(&runge, NULL);
		void* temp = altpot;
		altpot = neupot;
		neupot = temp;
		memcpy(neupot, altpot, vektorlaenge*sizeof(float));
		
		temp = altvek;
		altvek = neuvek;
		neuvek = temp;
		aktuelle_pot_nummer = (aktuelle_pot_nummer+1)%2;
	}
	return aktuelle_pot_nummer;
}
EMSCRIPTEN_KEEPALIVE
void betragsquad(float complex* quelle, float* ziel, int laenge){
	int i;
	for(i = 0; i < laenge; i++){
		ziel[i] = creal(quelle[i]) * creal(quelle[i]) + cimag(quelle[i]) * cimag(quelle[i]);
	}
}
EMSCRIPTEN_KEEPALIVE
void skalieren(float complex * ziel, int laenge, float skalar){
	int i;
	for(i = 0; i < laenge; i++){
		ziel[i] = ziel[i] * skalar;
	}
}
EMSCRIPTEN_KEEPALIVE
void leeren(float * ziel, int laenge){
	int i;
	for(i = 0; i < laenge; i++){
		ziel[i] = 0.0f;
	}
}
EMSCRIPTEN_KEEPALIVE
float aufaddieren(float * quelle, int laenge){
	float rueck = 0;
	int i;
	for(i = 0; i < laenge; i++){
		rueck = rueck +  quelle[i];
	}
	return rueck;
}


