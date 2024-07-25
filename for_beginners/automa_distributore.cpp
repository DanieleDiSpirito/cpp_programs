#include <iostream>
using namespace std;

int main () {
	int attesa, pronto;
	cout <<"Inserire 1 per dire che il distributore e' acceso, 0 che e' spento \n";
	cin >>attesa;
	while (attesa!=0 and attesa!=1) {
		cout <<"Reinserire un numero che sia 0 o 1 \n";
	    cin >>attesa;
	}
	if (attesa==1) {
	    do {
		cout <<"Inserire la moneta 1 per dire che hai inserito, 0 che non hai inserito \n";
		cin >>pronto;
    	} while (pronto == 0);
    while (pronto!=1) {
		cout <<"Reinserire un numero che sia 0 o 1 \n";
	    cin >>pronto;
    }
	cout <<"La bibita e' pronta da ritirare \n";
    }
    if (attesa==0) cout<<"Mi dispiace, il servizio e' disabilitato, prova piu' tardi \n";
	system ("pause");
	return 0;
}
