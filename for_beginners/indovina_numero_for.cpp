#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

main () {
	srand (time(NULL));
	int nMagico=rand()%100;
	int tentativo;
	int nTentativi;
	for (nTentativi=0;;nTentativi++) {
		cout <<"Qual e' il numero? ";
		cin >>tentativo;
	if (tentativo == nMagico) {
			cout <<"INDOVINATO, ecco il numero magico"<<endl;
			return 0;
		    }
	    else { cout <<"Hai sbagliato, ";
	        if (tentativo > nMagico) 
	        	cout <<"Il numero e' troppo alto \n";
	        else
	        cout <<"Il numero e' troppo basso \n";
			}
	}
	cout <<"Numero tentativi = "<<nTentativi<<endl;
	system ("pause");
	return 0; 
}
