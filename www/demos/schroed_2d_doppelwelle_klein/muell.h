
#ifndef def_schroed_muell
#define def_schroed_muell
#include <stdlib.h>
#include "funkmacro.h"

idek(zersetzungsfunk, void*, void);

void zersetzungsfunk_intern(void* selb, void* arg);
zersetzungsfunk keinezersetzung();

typedef struct{
	zersetzungsfunk** mitteilungen;
	int Laenge;
	int inhaltLaenge;
}muellmitteiler;

typedef struct{
	void** muell;
	int eimerLaenge;
	int inhaltLaenge;
}muelleimer;

typedef struct{
	muelleimer eimer;
	muellmitteiler mitteiler;
}zersetzungsplan;


#define alloc_var(pointername, structname, zer_plan_ptr, structargumente...)\
  structname* pointername = zmalloc(sizeof(structname), zer_plan_ptr);\
  (*pointername) = (structname){structargumente}

#define funkmuellmerken(funkname, muelleimer) muellmerken(funkname.inhalt, muelleimer)

#define f_var(varname, fname, iname, zplan_ptr, arg)\
	iname varname = fname ## _neu(arg);\
	muellmerken(varname.inhalt, &(zplan_ptr)->eimer);

#define argf_var(varname, fname, iname, zplan_ptr, argname, argargs ...)\
	argname argname ## varname ## _temp = (argname){argargs};\
	f_var(varname, fname, iname, zplan_ptr,argname ## varname ## _temp);
	

void zersetzen(zersetzungsplan * plan);

muelleimer neuermuelleimer();
muellmitteiler neuermuellmitteiler();
zersetzungsplan neuerzersetzungsplan();

void zersetzung_schachteln(zersetzungsplan innen, zersetzungsplan * aussen);

void erweiterungerwaegen(void *** buff, int * laenge, int inhaltsLaenge);

void muellmitteilungmerken(zersetzungsfunk mitteilung, muellmitteiler* mitteiler);
void zersetzungmitteilen(muellmitteiler* mitteiler);
void zmerken(zersetzungsfunk mitteilung, zersetzungsplan* zp);

void muellmerken(void * muell, muelleimer* eimer);
void muellleeren(muelleimer* eimer);

void * mallocm(size_t laenge, muelleimer* eimer);
void * callocm(size_t laenge, muelleimer* eimer);
void * zmalloc(size_t laenge, zersetzungsplan * zerp);
void * zcalloc(size_t laenge, zersetzungsplan * zerp);


fdek(muelleimerfunk, zersetzungsfunk, muelleimer, void*, void);
fdek(planzersetzung, zersetzungsfunk, zersetzungsplan, void*, void);


#endif
