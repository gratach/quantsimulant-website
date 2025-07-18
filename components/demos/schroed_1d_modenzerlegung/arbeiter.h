#ifndef def_schroed_arbeiter
#define def_schroed_arbeiter

#include<pthread.h>
#include "funkmacro.h"
#include "obmacro.h" 

idek(arbeiter, void *, int);
typedef struct{arbeiter a1; arbeiter a2;} zweiarbeiter;

fdek(mache_nacheinander, arbeiter, zweiarbeiter, void *, int);

fdek(keinearbeit, arbeiter, char, void*, int);
arbeiter arbeitslos();

tys{void(*f)(void*);}farbeiter_arg;
fdek(farbeiter, arbeiter, farbeiter_arg, void*, int);
arbeiter f_arb(void(*f)(void*), zersetzungsplan* zp);

typedef struct {arbeiter fortsetzung; pthread_mutex_t * mut; pthread_cond_t * bedingung; int * zaehler;} thread_abwarter;

typedef struct {arbeiter fortsetzung; pthread_cond_t * bedingung; int * zaehler;} thread_ausloeser;

typedef struct {arbeiter haupt; arbeiter neben;} synchilfe;
synchilfe mache_synchilfe(arbeiter haupt, arbeiter neben);


fdek( hauptthreadabwarten, arbeiter, thread_abwarter, void*, int);

fdek( nebenthreadmitnehmen, arbeiter, thread_ausloeser, void*, int);

#endif 
