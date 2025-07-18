
#ifndef def_schroed_schroed
#define def_schroed_schroed

#include"funkmacro.h"
#include "obmacro.h"
#include <complex.h>
#include "arbeiter.h"



typedef struct{void * alt; void * neu;}doppelzustand;
typedef struct {doppelzustand *inhalt;}doppelzustandsbox;
fdek(zustandstausch, arbeiter, doppelzustandsbox, void*, int);

typedef struct{float complex links;float complex mitte;float complex rechts;}trippelcomplex;
idek(dreizueinscomplex, trippelcomplex, float complex);

typedef struct {void* sehralt; void* alt; void* neu;} triplezustand;
typedef struct {triplezustand *inhalt;}triplezustandsbox;
fdek(triplezustandstausch, arbeiter, triplezustandsbox, void*, int);

static inline float complex euler_plus(float complex links, float complex mitte, float complex rechts, float complex zeitschritt){
    return (links + rechts - mitte - mitte)* I*zeitschritt;
}
static inline float complex eulerpot_plus(float complex links, float complex mitte, float complex rechts, float complex zeitschritt, float pot_alt, float pot_neu, float zeitbruchteil){
    return (links + rechts - mitte * (pot_alt + (pot_neu-pot_alt)*zeitbruchteil + 2))*zeitschritt * I ;
}

#endif
