#include "komponenten.h"

idef(cf64wertbei, f64raumzeit, complex double)
idef(f64wertbei, f64raumzeit, double)

fdef(rungekuttaD, arbeiter, rungekuttaD_args, void*, int){
	int i;
	int k;
	int rungezaehler = 0;// zaehlet durch d
	int ordnung = selbst->ordnung;
	double * rungematrix  = selbst->rungematrix;
	void* alt = selbst->zustand_alt;
	void* neu = selbst->zustand_neu;
	void** tempvektoren = selbst->tempvektoren;
	double zeitschritt = selbst->zeitschritt;
	int sizeofvector = selbst->bytelaenge;
	paramvektorwandel aenderung = selbst -> aenderung;
	paramvektorwandel adiereauf = selbst -> adiereauf;
	double gewicht;
	

	memcpy(neu, alt, sizeofvector);
	for (i=0;i<ordnung;i++){
	for(k=0;k<i;k++){
	  gewicht = rungematrix[rungezaehler++];
	  if(gewicht!= 0)
	  	paramvektorwandel_f(&adiereauf, (paramvektorwandel_args){tempvektoren[k], neu, gewicht*zeitschritt});
	}
	paramvektorwandel_f(&aenderung, (paramvektorwandel_args){neu, tempvektoren[i], rungematrix[rungezaehler++] });
	memcpy(neu, alt, sizeofvector);
	}
	for (i=0;i<ordnung;i++){
	gewicht = rungematrix[rungezaehler++];
	  if(gewicht!= 0)
	paramvektorwandel_f(&adiereauf, (paramvektorwandel_args){tempvektoren[i], neu, gewicht*zeitschritt});
	}
	return 0;
}
arbeiter* EMSCRIPTEN_KEEPALIVE mache_rungekutta_D(void* zustand_alt, void* zustand_neu, int ord, int bytelaenge, paramvektorwandel aenderung, paramvektorwandel adiereauf, double* rungematrix, double zeitschritt){
	arbeiter* ptr = malloc(sizeof(arbeiter));
	void** tempvektoren = malloc(sizeof(tempvektoren)*ord);
	int i;
	for(i = 0; i<ord; i++)
		tempvektoren[i] = malloc(bytelaenge);
	rungekuttaD_args rkd = (rungekuttaD_args){zustand_alt,zustand_neu,ord, tempvektoren,  bytelaenge, aenderung, adiereauf, rungematrix, zeitschritt};
	*ptr = rungekuttaD_neu(rkd);
	return ptr;
}
void EMSCRIPTEN_KEEPALIVE veksetzen_rungekutta_D(arbeiter* pvw, double* alt, double* neu){
	rungekuttaD_args* ptr = pvw->inhalt;
	ptr->zustand_alt = alt;
	ptr->zustand_neu = neu;
}
void EMSCRIPTEN_KEEPALIVE free_rungekutta_D(arbeiter* pvw){
	rungekuttadetails* rkd = pvw->inhalt;
	int ord = rkd->ordnung;
	void** tempvektoren = rkd->tempvektoren;
	int i;
	for(i = 0; i<ord; i++)
		free(tempvektoren[i]);
	free(tempvektoren);
	free(pvw->inhalt);
	free(pvw);
}


fdef(D1D_pot_euler_vektoraenderung, paramvektorwandel, D1D_pot_euler_vektoraenderung_args, paramvektorwandel_args, void){
	double complex * alt = arg.alt;
	double complex * neu = arg.neu;
	double * altpot = selbst->altpot;
	double * neupot = selbst->neupot;
	double laplace_gewichtung = selbst -> laplace_gewichtung;
	double param = arg.parameter;
	size_t laenge = selbst->vektorlaenge;
	int i;
	for(i = 2;i<laenge;i++){
		neu[i-1] = eulerpot_plus(alt[i-2], alt[i-1], alt[i], altpot[i], neupot[i], param, laplace_gewichtung);
	}
}
paramvektorwandel* EMSCRIPTEN_KEEPALIVE mache_D1D_pot_euler_vektoraenderung(double* altpot, double* neupot, int len, double laplace_gewichtung){
	paramvektorwandel* ptr = malloc(sizeof(paramvektorwandel));
	*ptr = D1D_pot_euler_vektoraenderung_neu((D1D_pot_euler_vektoraenderung_args){altpot, neupot, len, laplace_gewichtung});
	return ptr;
}
void EMSCRIPTEN_KEEPALIVE potsetzen_D1D_pot_euler_vektoraenderung(paramvektorwandel* pvw, double* altpot, double* neupot){
	D1D_pot_euler_vektoraenderung_args* ptr = pvw->inhalt;
	ptr->altpot = altpot;
	ptr->neupot = neupot;
}
void EMSCRIPTEN_KEEPALIVE laplacegewichtungsetzen_D1D_pot_euler_vektoraenderung(paramvektorwandel* pvw, double laplace_gewichtung){
	((D1D_pot_euler_vektoraenderung_args*)pvw->inhalt)->laplace_gewichtung = laplace_gewichtung;
}
void EMSCRIPTEN_KEEPALIVE free_D1D_pot_euler_vektoraenderung(paramvektorwandel* pvw){
	free(pvw->inhalt);
	free(pvw);
}

fdef(D_vektoraddieren, paramvektorwandel, int, paramvektorwandel_args, void){
    double * alt = arg.alt;
    double * neu = arg.neu;
    double param = arg.parameter;
    size_t laenge = *selbst;
    int i;
    for(i=0;i<laenge;i++)
    {
        neu[i] += alt[i] * param;
    }
    
}
paramvektorwandel* EMSCRIPTEN_KEEPALIVE mache_D_vektoraddieren(int len){
	paramvektorwandel* ptr = malloc(sizeof(paramvektorwandel));
	*ptr = D_vektoraddieren_neu(len);
	return ptr;
}
void EMSCRIPTEN_KEEPALIVE free_D_vektoraddieren(paramvektorwandel* pvw){
	free(pvw->inhalt);
	free(pvw);
}

double EMSCRIPTEN_KEEPALIVE getf64(void* ort){
	double* ptr = ort;
	return *ptr;
}
void EMSCRIPTEN_KEEPALIVE setf64(void* ort, double wert){
	double* ptr = ort;
	*ptr = wert;
}

void EMSCRIPTEN_KEEPALIVE mache_arbeiter(arbeiter* ptr){
	arbeiter_f(ptr, NULL);
}

rungekuttamatrix_D* EMSCRIPTEN_KEEPALIVE mache_rungekuttamatrix_D(int ordnung){
	rungekuttamatrix_D * r = malloc(sizeof(rungekuttamatrix_D));
	double * ptr = malloc(sizeof(double) * (2 * ordnung + ordnung*(ordnung-1)/2));
	/*{0,0.5, 0.5,0,0.5,0.5,0,0,1,1,1.0/6,1.0/3,1.0/3,1.0/6}
	ptr[0] = 0;
	ptr[1] = 0.5;
	ptr[2] = 0.5;
	ptr[3] = 0;
	ptr[4] = 0.5;
	ptr[5] = 0.5;
	ptr[6] = 0;
	ptr[7] = 0;
	ptr[8] = 1;
	ptr[9] = 1;
	ptr[10] = 1.0/6;
	ptr[11] = 1.0/3;
	ptr[12] = 1.0/3;
	ptr[13] = 1.0/6;*/
	*r = (rungekuttamatrix_D){ordnung, ptr};
	return r;
}
void EMSCRIPTEN_KEEPALIVE free_rungekuttamatrix_D(rungekuttamatrix_D* rkm){
	free(rkm->matrix);
	free(rkm);
}
double* EMSCRIPTEN_KEEPALIVE get_rungekuttamatrix_D_ptr(rungekuttamatrix_D* rkm){
	return rkm->matrix;
}

fdef(cf64arr, cf64wertbei, cf64arr_args, f64raumzeit, complex double){
	double r = (arg.raum - selbst->anf) * selbst->lendurchbreite;
	int u = floor(r);
	int o = u + 1;
	double complex ru = 0;
	double complex ro = 0;
	if(u > -1 && u < selbst->len)
		ru = selbst->ptr[u];
	if(o > -1 && o < selbst->len)
		ro = selbst->ptr[o];

	r -= u;
	return r * ro + (1 - r) * ru;
} 
//modus für rand: 'n' null; 's' schleife; 'r' reflektiert; 'l' letzterWert
void* EMSCRIPTEN_KEEPALIVE mache_CDArr(void* vek, double laenge, double anf, double end){
	cf64wertbei* rueck = malloc(sizeof(cf64wertbei));
	*rueck = cf64arr_neu((cf64arr_args){vek, laenge, anf, (laenge - 1) / (end - anf)});
	return rueck;
}
void EMSCRIPTEN_KEEPALIVE free_CDArr(void* ptr){
	cf64wertbei_leeren(ptr);
	free(ptr);
}
void EMSCRIPTEN_KEEPALIVE tausche_CDArr(cf64wertbei* wb, complex double* ptr){
	((cf64arr_args*)wb->inhalt)->ptr = ptr;
}

fdef(CDR_wertbei, f64wertbei, cf64wertbei, f64raumzeit, double){
	return creal(cf64wertbei_f(selbst, arg));
}
f64wertbei* EMSCRIPTEN_KEEPALIVE mache_CDR_wertbei(cf64wertbei* ptr){
	f64wertbei* r = malloc(sizeof(f64wertbei));
	*r = CDR_wertbei_neu_ptr(ptr);
	return r;
}

fdef(CDI_wertbei, f64wertbei, cf64wertbei, f64raumzeit, double){
	return cimag(cf64wertbei_f(selbst, arg));
}
f64wertbei* EMSCRIPTEN_KEEPALIVE mache_CDI_wertbei(cf64wertbei* ptr){
	f64wertbei* r = malloc(sizeof(f64wertbei));
	*r = CDI_wertbei_neu_ptr(ptr);
	return r;
}

fdef(CDQ_wertbei, f64wertbei, cf64wertbei, f64raumzeit, double){
	complex double r = cf64wertbei_f(selbst, arg);
	double re = creal(r);
	double im = cimag(r);
	return re*re + im*im;
}
f64wertbei* EMSCRIPTEN_KEEPALIVE mache_CDQ_wertbei(cf64wertbei* ptr){
	f64wertbei* r = malloc(sizeof(f64wertbei));
	*r = CDQ_wertbei_neu_ptr(ptr);
	return r;
}
void EMSCRIPTEN_KEEPALIVE free_CDR_CDI_CDQ_wertbei(f64wertbei* ptr){
	free(ptr);
}

void EMSCRIPTEN_KEEPALIVE copy_vek(void* von, void* zu, int bytelen){
	memcpy(zu, von, bytelen);
}


fdef(kasten_moden_D, cf64wertbei, kasten_moden_D_args, f64raumzeit, complex double){
	int max = selbst->ord + 1;
	double ort = (arg.raum - selbst->xoff)*selbst->xstretch;
	double complex dreh = selbst->dreh * arg.zeit * I;
	double complex* arr = selbst->moden;
	int i;
	double complex r = 0;
	for(i = 1; i < max; i++){
		r += arr[i]*sin(ort*i)*exp(i*i*dreh);
	}
	return r;
}

void* EMSCRIPTEN_KEEPALIVE mache_kasten_moden_D(int ord, double xanf, double xend, double mass){
	double breite = xend - xanf;
	double dreh = -M_PI*M_PI/(2*mass*breite*breite);
	double xstretch = M_PI / breite;
	double complex* arr = malloc((ord + 1) * sizeof(double)*2);
	cf64wertbei* ptr = malloc(sizeof(cf64wertbei));
	*ptr = kasten_moden_D_neu((kasten_moden_D_args){arr, ord, dreh, xstretch, xanf});
	return ptr;
}
complex double* EMSCRIPTEN_KEEPALIVE getmoden_kasten_moden_D(cf64wertbei* ptr){
	return ((kasten_moden_D_args*)ptr->inhalt)->moden;
}
void EMSCRIPTEN_KEEPALIVE free_kasten_moden_D(cf64wertbei* ptr){
	free(((kasten_moden_D_args*)ptr->inhalt)->moden);
	free(ptr);
}


double EMSCRIPTEN_KEEPALIVE CDquad_diff(double complex* p1, double complex* p2, int len, double intervall){
	int i;
	double r;
	double re;
	double im;
	for(i = 0; i<len; i++){
		re = creal(p1[i])-creal(p2[i]);
		im = cimag(p2[i])-cimag(p1[i]);
		r += re*re+im*im;
	}
	return r * intervall / (len - 1);
}


void EMSCRIPTEN_KEEPALIVE DSchwingungsZerlegung(double complex * inparr, int laenge, double complex * outarr, int ordnung, double masse,  double zeit){
	double dreh =  zeit*M_PI*M_PI/(laenge*laenge*2*masse);
	int n;
	int i;
	double complex integr;
	double complex winkel;
	double schritt;
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

void EMSCRIPTEN_KEEPALIVE DSchwingungsZusammensetzung(double complex * inparr, int ordnung, double complex * outarr, int laenge, double masse, double zeit){
	double dreh =  zeit*M_PI*M_PI/(laenge*laenge*2*masse);
	int n;
	int i;
	double complex winkel;
	double schritt;
	memset(outarr, 0, sizeof(double complex) * laenge);
	int lminuseins = (laenge - 1);
	for(n = 1; n<=ordnung; n++){
		winkel = exp((-dreh) * n*n * I);
		schritt = n * M_PI / lminuseins;
		for(i = 0; i < laenge; i++){
			outarr[i] += sin(i*schritt)*inparr[n]*winkel;
		}
	}
}

fdef(f64arr, f64wertbei, f64arr_args, f64raumzeit, double){
	double r = (arg.raum - selbst->anf) * selbst->lendurchbreite;
	int u = floor(r);
	int o = u + 1;
	double ru = 0;
	double ro = 0;
	//EM_ASM({alert($0+", "+$1+", "+$2+", "+$3+", "+$4+", ")}, r, u, o, ru, ro);
	if(u > -1 && u < selbst->len)
		ru = selbst->ptr[u];
	if(o > -1 && o < selbst->len)
		ro = selbst->ptr[o];

	r -= u;
	return r * ro + (1 - r) * ru;
}

void* EMSCRIPTEN_KEEPALIVE mache_DArr(void* vek, double laenge, double anf, double end){
	f64wertbei* rueck = malloc(sizeof(f64wertbei));
	*rueck = f64arr_neu((f64arr_args){vek, laenge, anf, (laenge - 1) / (end - anf)});
	return rueck;
}
void EMSCRIPTEN_KEEPALIVE free_DArr(void* ptr){
	f64wertbei_leeren(ptr);
	free(ptr);
}
void EMSCRIPTEN_KEEPALIVE tausche_DArr(f64wertbei* wb, double* ptr){
	((f64arr_args*)wb->inhalt)->ptr = ptr;
}

void EMSCRIPTEN_KEEPALIVE fuelle_CDArr(complex double* ptr, int len, cf64wertbei* wb, double start, double schritt, double zeit){
	double ort = start;
	int i;
	for(i=0;i<len;i++){
		ptr[i] = cf64wertbei_f(wb,(f64raumzeit){ort, zeit});
		ort += schritt;
	}
}

double temp_im_wertbei;
double EMSCRIPTEN_KEEPALIVE d_wertbei(void* ptr, double raum, double zeit){
	return f64wertbei_f(ptr,(f64raumzeit){raum, zeit});
}
double EMSCRIPTEN_KEEPALIVE re_d_wertbei(void* ptr, double raum, double zeit){
	complex double r = cf64wertbei_f(ptr,(f64raumzeit){raum, zeit});
	temp_im_wertbei = cimag(r);
	return creal(r);
}
double EMSCRIPTEN_KEEPALIVE im_d_wertbei_nachreichen(){
	return temp_im_wertbei;
}
