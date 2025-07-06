#include"schroed.h" 

idef(dreizueinscomplex, trippelcomplex, float complex);
fdef(zustandstausch, arbeiter, doppelzustandsbox, void*, int){
  doppelzustand * inhalt = (*selbst).inhalt;
  void * temp = (*inhalt).alt;
  (*inhalt).alt = (*inhalt).neu;
  (*inhalt).neu = temp;
  return 0;
}

fdef(triplezustandstausch, arbeiter, triplezustandsbox, void*, int){
  triplezustand * inhalt = (*selbst).inhalt;
  void * temp = (*inhalt).sehralt;
  (*inhalt).sehralt = (*inhalt).alt;
  (*inhalt).alt = (*inhalt).neu;
  (*inhalt).neu = temp;
  return 0;
}
