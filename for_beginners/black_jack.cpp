#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <>
using namespace std;

int main ()  {
	srand (time(NULL));
	int carta=(rand()%11)+1, punteggio1=carta, punteggio2=carta, valoreasso;
	char risposta;
	if (carta==1 || carta==11) {
		cout<<"E' uscito l'ASSO, dagli il valore (1 o 11): ";
		do {
			cin>>valoreasso;
			if (valoreasso!=1 && valoreasso!=11) {
				cout<<"Sbagliato, reinserire il valore"<<endl;
			}
		} while (valoreasso!=1 && valoreasso!=11);
		punteggio1=valoreasso;
	}
	cout<<"Tuo Punteggio: "<<punteggio1<<endl<<"Altra carta? ";
	while (risposta=='s') {
		carta=(rand()%11)+1;
		if (carta==1 || carta==11) {
		cout<<"E' uscito l'ASSO, dagli il valore (1 o 11): ";
		do {
			cin>>valoreasso;
			if (valoreasso!=1 && valoreasso!=11) {
				cout<<"Sbagliato, reinserire il valore"<<endl;
			}
		} while (valoreasso!=1 && valoreasso!=11);
		carta=valoreasso;
		}
		cout<<"\nE' uscito: "<<carta<<endl;
		punteggio1+=carta;
		cout<<"Tuo Punteggio: "<<punteggio1<<endl;
		if (punteggio1>=22) {
			cout<<"Hai perso";
			return 0;
		}
		else {
			cout<<"Altra carta?";
		}
		cin>>risposta;
	}
	cout<<"\nPunteggio avversario: "<<punteggio2;
	while (punteggio2<punteggio1) {
		carta=(rand()%11)+1;
		cout<<"\nE' uscito: "<<carta<<endl;
		punteggio2+=carta;
		cout<<"Punteggio avversario: "<<punteggio2<<endl;
		if (punteggio1>=22) {
			cout<<"Hai vinto";
			return 0;
		}
	}
	if (punteggio1>punteggio2) {
		cout<<"\nHai vinto";
	}
	else {
		cout<<"Hai perso";
	}
}
