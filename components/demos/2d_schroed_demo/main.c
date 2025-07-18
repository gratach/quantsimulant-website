/*#include <stdio.h>
#include <emscripten.h>
#include "main.h"

int main(){
	EM_ASM( bereit() );
}

char* bild;
int breite;
int hoehe;
int t = 0;


void vorbereiten(void* buff,int breit, int hoch){
	bild = buff;
	breite = breit;
	hoehe = hoch;
}

void iteration(){
	int x;
	int y;
	char* pos = bild;
	for(y = 0; y < hoehe; y++)
		for(x = 0; x < breite; x++)
		{
			*pos = (char)((x+y+t)%256);
			pos += 4;
		}
	t++;
}*/
