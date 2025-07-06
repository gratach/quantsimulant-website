#ifndef def_schroed_komponenten
#define def_schroed_komponenten

#include <emscripten.h>
#include<math.h>
#include "schroed.h"
#include"rungekutta.h"
#include"funkmacro.h"
#include <tgmath.h>

/*typedef struct {} D1DEulerAenderung_args;
fdek(D1DEulerAenderung, paramvektorwandel, D1DEulerAenderung_args, paramvektorwandel_args, void)*/

typedef struct{void* zustand_alt; void* zustand_neu; int ordnung; void** tempvektoren;  int bytelaenge; paramvektorwandel aenderung; paramvektorwandel adiereauf; double* rungematrix; double zeitschritt;} rungekuttaD_args;
fdek(rungekuttaD, arbeiter, rungekuttaD_args, void*, int);

typedef struct {double* altpot; double* neupot; size_t vektorlaenge; double laplace_gewichtung;} D1D_pot_euler_vektoraenderung_args;
fdek(D1D_pot_euler_vektoraenderung, paramvektorwandel, D1D_pot_euler_vektoraenderung_args, paramvektorwandel_args, void);

fdek(D_vektoraddieren, paramvektorwandel, int, paramvektorwandel_args, void);

typedef struct {double raum; double zeit;} f64raumzeit;
idek(cf64wertbei, f64raumzeit, complex double)
idek(f64wertbei, f64raumzeit, double)

fdek(CDR_wertbei, f64wertbei, cf64wertbei, f64raumzeit, double);
fdek(CDI_wertbei, f64wertbei, cf64wertbei, f64raumzeit, double);
fdek(CDQ_wertbei, f64wertbei, cf64wertbei, f64raumzeit, double);

typedef struct {complex double* moden; int ord; double dreh; double xstretch; double xoff;} kasten_moden_D_args;
fdek(kasten_moden_D, cf64wertbei, kasten_moden_D_args, f64raumzeit, complex double);

typedef struct {complex double* ptr; int len; double anf; double lendurchbreite;} cf64arr_args;
fdek(cf64arr, cf64wertbei, cf64arr_args, f64raumzeit, complex double)

typedef struct {double* ptr; int len; double anf; double lendurchbreite;} f64arr_args;
fdek(f64arr, f64wertbei, f64arr_args, f64raumzeit, double)

typedef struct {int ordnung; double * matrix;} rungekuttamatrix_D;
#endif
