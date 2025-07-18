#ifndef def_schroed_schroed_1d
#define def_schroed_schroed_1d

#include<math.h>
#include "schroed.h"
#include"rungekutta.h"
#include"muell.h"
#include"funkmacro.h"
#include "obmacro.h"

typedef struct {size_t vektorlaenge; doppelzustand * potential; float laplace_gewichtung;} euler_1D_pot_vektoraenderung_args;
fdek(euler_1D_pot_vektoraenderung, paramvektorwandel, euler_1D_pot_vektoraenderung_args, paramvektorwandel_args, void);

#endif
