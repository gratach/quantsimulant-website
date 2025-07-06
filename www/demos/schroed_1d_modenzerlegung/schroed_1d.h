#ifndef def_schroed_schroed_1d
#define def_schroed_schroed_1d

#include<math.h>
#include "schroed.h"
#include"rungekutta.h"
#include"muell.h"
#include"funkmacro.h"
#include "obmacro.h"
#include <tgmath.h>

typedef struct {size_t vektorlaenge; doppelzustand * potential; float laplace_gewichtung;} euler_1D_pot_vektoraenderung_args;
fdek(euler_1D_pot_vektoraenderung, paramvektorwandel, euler_1D_pot_vektoraenderung_args, paramvektorwandel_args, void);
void SchwingungsZusammensetzung(float complex * inparr, float complex * outarr, int laenge, float dreh, int ordnung);
void ZusammensetzungsAenderung(float complex * inparr, int laenge, float complex * outarr, int vonx, int zux, float complex vony, float complex zuy, float dreh, int ordnung);
void laplace_gewichtung_aendern(float neu);
void zeitschritt_aendern(float neu);

#endif
