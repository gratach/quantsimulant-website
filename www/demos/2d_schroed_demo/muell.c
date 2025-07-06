#include "muell.h"
#include <string.h>

idef(zersetzungsfunk, void*, void);
void zersetzungsfunk_intern(void* selb, void* arg){
}
zersetzungsfunk keinezersetzung()
{
	return zersetzungsfunk_neu(zersetzungsfunk_intern, NULL);
}

muelleimer neuermuelleimer(){
	return (muelleimer){malloc(sizeof(size_t)), 1, 0};
}

muellmitteiler neuermuellmitteiler(){
	return (muellmitteiler){malloc(sizeof(size_t)), 1, 0};
}
zersetzungsplan neuerzersetzungsplan(){
	return (zersetzungsplan){neuermuelleimer(),neuermuellmitteiler()};
}


void erweiterungerwaegen(void *** buff, int * laenge, int inhaltLaenge){
	if(*laenge == inhaltLaenge){
		*laenge = inhaltLaenge*2;
		void** neu = malloc(*laenge*sizeof(void*));
		memcpy(neu, *buff, inhaltLaenge*sizeof(void*));
		free(*buff);
		*buff = neu;
	}
}

void zersetzen(zersetzungsplan * plan){
	zersetzungmitteilen(&plan->mitteiler);
	muellleeren(&plan->eimer);
}

void muellmitteilungmerken(zersetzungsfunk mitteilung, muellmitteiler* mitteiler){
	zersetzungsfunk * ptr = malloc(sizeof(zersetzungsfunk));
	*ptr = mitteilung;
	erweiterungerwaegen((void***)&mitteiler->mitteilungen, &mitteiler->Laenge, mitteiler->inhaltLaenge);
	mitteiler->mitteilungen[mitteiler->inhaltLaenge]=ptr;
	mitteiler->inhaltLaenge += 1;
}
void zersetzungmitteilen(muellmitteiler* mitteiler){
	int i;
	for(i = 0; i < mitteiler->inhaltLaenge;i++)
	{
		zersetzungsfunk * ptr = mitteiler->mitteilungen[i];
		zersetzungsfunk_f(ptr, NULL);
		zersetzungsfunk_leeren(ptr);
		free(ptr);
	}
	free(mitteiler->mitteilungen);
}
void zmerken(zersetzungsfunk mitteilung, zersetzungsplan* zp){
	muellmitteilungmerken(mitteilung, &zp->mitteiler);
}

void muellmerken(void * muell, muelleimer * eimer){
	erweiterungerwaegen(&eimer->muell, &eimer->eimerLaenge, eimer->inhaltLaenge);
	eimer->muell[eimer->inhaltLaenge]=muell;
	eimer->inhaltLaenge += 1;
}
void muellleeren(muelleimer* eimer){
	int i;
	for(i = 0; i < eimer->inhaltLaenge;i++)
		free(eimer->muell[i]);
	free(eimer->muell);
}
void * mallocm(size_t laenge, muelleimer* eimer){
	void* rueck = malloc(laenge);
	muellmerken(rueck, eimer);
	return rueck;
}void * callocm(size_t laenge, muelleimer* eimer){
	void* rueck = calloc(1,laenge);
	muellmerken(rueck, eimer);
	return rueck;
}
void * zmalloc(size_t laenge, zersetzungsplan * zerp){
	return mallocm(laenge, &zerp->eimer);
}
void * zcalloc(size_t laenge, zersetzungsplan * zerp){
	return callocm(laenge, &zerp->eimer);
}

fdef(muelleimerfunk, zersetzungsfunk, muelleimer, void*, void){
	muellleeren(selbst);
}
fdef(planzersetzung, zersetzungsfunk, zersetzungsplan, void*, void){
	zersetzen(selbst);
}

void zersetzung_schachteln(zersetzungsplan innen, zersetzungsplan * aussen){
	muellmitteilungmerken(planzersetzung_neu(innen), &aussen->mitteiler);
}
