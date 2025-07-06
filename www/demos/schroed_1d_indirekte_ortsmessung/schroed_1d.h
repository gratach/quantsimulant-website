#ifndef def_schroed_schroed_1d
#define def_schroed_schroed_1d

#include<math.h>
#include "schroed.h"
#include"rungekutta.h"
#include"funkmacro.h"

typedef struct {size_t vektorlaenge; doppelzustand * potential; float laplace_gewichtung;} euler_1D_pot_vektoraenderung_args;
fdek(euler_1D_pot_vektoraenderung, paramvektorwandel, euler_1D_pot_vektoraenderung_args, paramvektorwandel_args, void);

typedef struct {size_t vektorlaenge; doppelzustand * potential; float laplace_gewichtung; int gekoppelt; int ort; int ortsunschaerfe; float kopplungsstaerke;} euler_1D_pot_ortsmessung_vektoraenderung_args;
fdek(euler_1D_pot_ortsmessung_vektoraenderung, paramvektorwandel, euler_1D_pot_ortsmessung_vektoraenderung_args, paramvektorwandel_args, void);

int euler_1D_doppel_vorbereiten(int vektorlaenge_arg, void* vek_0, void* vek_1, void* betr_quad, void* pot_0, void* pot_1, float zeitschritt_arg, float laplace_gewicht);
float aufaddieren(float * quelle, int laenge);
void skalieren(float complex * ziel, int laenge, float skalar);
void leeren(float * ziel, int laenge);

#endif
