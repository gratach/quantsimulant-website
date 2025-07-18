#include <stdio.h>
#include <emscripten.h>
#include "wa.h"

idef(testi, int, int);

fdef(zbf, testi, int, int, int){
	return *selbst + arg + 2;
}

int main(){
	EM_ASM( bereit() );
	nichtda();
}

EMSCRIPTEN_KEEPALIVE
int halli(int i){
	testi t = zbf_neu(22);
	return testi_f(&t, 44);
}
