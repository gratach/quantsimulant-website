
#include "arbeiter.h"
idef(arbeiter, void *, int);
fdef(mache_nacheinander, arbeiter, zweiarbeiter, void *, int){
  arbeiter_f(&(*selbst).a1, arg);
  arbeiter_f(&(*selbst).a2, arg);
  return 0;
}
fdef(keinearbeit, arbeiter, char, void*, int){return 0;}
fdef( hauptthreadabwarten, arbeiter, thread_abwarter, void*, int){
  __sync_fetch_and_add((*selbst).zaehler, 1);
  pthread_mutex_lock((*selbst).mut);
  pthread_cond_wait((*selbst).bedingung, (*selbst).mut);
  int i = arbeiter_f(&(*selbst).fortsetzung,arg);
  pthread_mutex_unlock((*selbst).mut);
  __sync_fetch_and_add((*selbst).zaehler, -1);
  return i;
}

fdef( nebenthreadmitnehmen, arbeiter, thread_ausloeser, void*, int){
  if(__sync_fetch_and_add((*selbst).zaehler, 1)==1)
    pthread_cond_signal((*selbst).bedingung);
  int i = arbeiter_f(&(*selbst).fortsetzung,arg);
  __sync_fetch_and_add((*selbst).zaehler, -1);
  return i;
}

arbeiter arbeitslos(){return keinearbeit_neu('\0');}

synchilfe mache_synchilfe(arbeiter haupt, arbeiter neben){
  pthread_cond_t * cv = malloc(sizeof(pthread_cond_t));
  pthread_mutex_t * lock = malloc(sizeof(pthread_mutex_t));
  int * zaeler = malloc(sizeof(int));
  return (synchilfe){nebenthreadmitnehmen_neu((thread_ausloeser){haupt, cv, zaeler}), hauptthreadabwarten_neu((thread_abwarter){neben, lock, cv, zaeler})};
} 

fdef(farbeiter, arbeiter, farbeiter_arg, void*, int){
	selbst->f(arg);
	return 0;
}
arbeiter f_arb(void(*f)(void*), zersetzungsplan *  zerp){
	argf_var(rueck, 
		farbeiter, arbeiter, zerp, farbeiter_arg, f)
	return rueck;
}


