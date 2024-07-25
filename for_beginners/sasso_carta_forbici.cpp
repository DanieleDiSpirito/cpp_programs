#include <iostream>
#include <stdlib.h>
using namespace std;

main () {
	int mossaCPU;
	char mossaPlayer;
	int punteggioCPU=0;
	int punteggioPlayer=0;
	do {
		cin >>mossaPlayer;
		mossaCPU = rand () %4 -1;
		if (mossaCPU==-1)
		cout <<"forbici";
		if (mossaCPU==0)
		cout <<"sasso";
		if (mossaCPU==1)
		cout <<"carta";
		if (mossaCPU==2)
		cout <<"forbici";
		if (mossaCPU-1==mossaPlayer)	punteggioCPU++;
		if (mossaCPU+1==mossaPlayer)	punteggioPlayer++;
	} while (punteggioCPU == 5 or punteggioPlayer == 5);
	system ("pause");
	return 0;
}
