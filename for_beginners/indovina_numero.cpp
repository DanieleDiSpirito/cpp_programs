#include <iostream>
#include <stdlib.h>
using namespace std;

main () {
	int nMagico=rand();
	int tentativo;
	int nTentativi=0;
	do {
		cout <<"Qual e' il numero? ";
		cin >>tentativo;
		nTentativi++;
		if (tentativo == nMagico) {
			cout <<"INDOVINATO, ecco il numero magico"<<endl;
		    }
	    else { cout <<"Hai sbagliato, ";
	        if (tentativo > nMagico) 
	        	cout <<"Il numero e' troppo alto \n";
	        else
	        cout <<"Il numero e' troppo basso \n";
			}
		}while (tentativo != nMagico);
		cout <<"Numero tentativi = "<<nTentativi<<endl;
		system ("pause");
		return 0; 
}
