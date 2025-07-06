#ifndef def_schroed_rungekutta
#define def_schroed_rungekutta

#include<string.h>
#include"funkmacro.h"
#include "obmacro.h"
#include"arbeiter.h"

#define rungekuttamatrix_4 {0,0.5, 0.5,0,0.5,0.5,0,0,1,1,1.0/6,1.0/3,1.0/3,1.0/6}

typedef struct {void* alt; void* neu; float parameter;} paramvektorwandel_args;
idek(paramvektorwandel, paramvektorwandel_args, void)
fdek(floatvektoraddieren, paramvektorwandel, int, paramvektorwandel_args, void)



typedef struct{void** zustand_alt; void** zustand_neu; int ordnung; void** tempvektoren; size_t sizeofvector; paramvektorwandel aenderung; paramvektorwandel adiereauf; float* rungematrix;} rungekuttadetails;
fdek(rungekutta, arbeiter, rungekuttadetails, void*, int);

arbeiter macherungekutta_neu(void** zustand_alt, void** zustand_neu, int ordnung, size_t sizeofvector, paramvektorwandel aenderung, paramvektorwandel adiereauf, float* rungematrix, zersetzungsplan * muell);
void macherungekutta_dealloc(arbeiter* selbst);

#endif
