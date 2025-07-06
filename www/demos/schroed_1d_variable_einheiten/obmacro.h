#ifndef OBMACRO_FILE
#define OBMACRO_FILE

#include"funkmacro.h"
#include"muell.h"



#define odek(obname)\
	obname ## _inh;\
	typedef struct obname{\
		obname ## _inh inh;\
		zersetzungsplan zer;\
	} obname;\
	void obname ## _zer (obname * o);\
	obname obname ## _neu(obname ## _inh inhalt, zersetzungsplan delf);\
	void obname ## _add_zer(obname * o, zersetzungsplan zerp);

#define odef(obname)\
	void obname ## _zer (obname * o){\
		zersetzen( &o->zer);\
	}\
	void obname ## _add_zer(obname * o, zersetzungsplan zerp)\
	{\
		zersetzung_schachteln(zerp, &o->zer);\
	}\
	obname obname ## _neu(obname ## _inh inhalt, zersetzungsplan delf){\
		return (obname){inhalt, delf};\
	}
	

#define neuob(obname,delf, obargs...) obname ## _neu((obname ## _inh){obargs}, delf)



#endif
