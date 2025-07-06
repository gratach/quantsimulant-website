
#include "rungekutta.h" 

idef(paramvektorwandel, paramvektorwandel_args, void)
arbeiter macherungekutta_neu(void** zustand_alt, void** zustand_neu, int ordnung, size_t sizeofvector, paramvektorwandel aenderung, paramvektorwandel adiereauf, float* rungematrix, zersetzungsplan * muell)
{
	int i;
	void** tempvektoren = malloc(sizeof(tempvektoren)*ordnung);
	for(i = 0; i<ordnung; i++)
		tempvektoren[i] = zmalloc(sizeofvector , muell);
	argf_var(rueck, 
		rungekutta, arbeiter, muell, rungekuttadetails, zustand_alt, zustand_neu, ordnung, tempvektoren, sizeofvector, aenderung,  adiereauf, rungematrix);
	return rueck;
}
void macherungekutta_dealloc(arbeiter* selbst){
	rungekuttadetails inhalt = *(rungekuttadetails*)selbst->inhalt;
	void** tempvektoren = inhalt.tempvektoren;
	int i;
	int ordnung = inhalt.ordnung;
	for(i =0;i<ordnung;i++)
	  free(tempvektoren[i]);
	free(tempvektoren);
}
fdef(floatvektoraddieren, paramvektorwandel, int, paramvektorwandel_args, void){
    float * alt = (float *)arg.alt;
    float * neu = (float *)arg.neu;
    float param = arg.parameter;
    size_t laenge = *selbst;
    int i;
    for(i=0;i<laenge;i++)
    {
        neu[i] += alt[i] * param;
    }
    
}
fdef(rungekutta, arbeiter, rungekuttadetails, void*, int){
  
  int i;
  int k;
  int rungezaehler = 0;// zaehlet durch d
  int ordnung = selbst->ordnung;
  float * rungematrix  = selbst->rungematrix;
  void* alt = *selbst->zustand_alt;
  void* neu = *selbst->zustand_neu;
  void** tempvektoren = selbst->tempvektoren;
  size_t sizeofvector = selbst->sizeofvector;
  paramvektorwandel aenderung = selbst -> aenderung;
  paramvektorwandel adiereauf = selbst -> adiereauf;
  float gewicht;
  

  memcpy(neu, alt, sizeofvector);
  for (i=0;i<ordnung;i++){
	for(k=0;k<i;k++){
	  gewicht = rungematrix[rungezaehler++];
	  if(gewicht!= 0)
	  	paramvektorwandel_f(&adiereauf, (paramvektorwandel_args){tempvektoren[k], neu, gewicht});
	}
    paramvektorwandel_f(&aenderung, (paramvektorwandel_args){neu, tempvektoren[i], rungematrix[rungezaehler++] });
	memcpy(neu, alt, sizeofvector);
  }
  for (i=0;i<ordnung;i++){
    gewicht = rungematrix[rungezaehler++];
	  if(gewicht!= 0)
        paramvektorwandel_f(&adiereauf, (paramvektorwandel_args){tempvektoren[i], neu, gewicht});
  }
  return 0;
}
