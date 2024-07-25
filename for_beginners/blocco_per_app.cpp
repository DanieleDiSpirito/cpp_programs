#include <iostream>
using namespace std;

int main () {
	int numero1;
	int numero2;
	int numero3;
	int numero4;
	int numerop1;
	int numerop2;
	int numerop3;
	int numerop4;
	do {
	cout<<"Inserire il primo numero: ";
	cin>>numero1;
	if (numero1>=10 || numero1<0) {
	cout<<"Numero sbagliato, sono compresi solo numeri con 1 cifra"<<endl;
	}	
	} while (numero1>=10 || numero1<0);
	do {
	cout<<"Inserire il secondo numero: ";
	cin>>numero2;
	if (numero2>=10 || numero2<0) {
	cout<<"Numero sbagliato, sono compresi solo numeri con 1 cifra"<<endl;
	}	
	} while (numero2>=10 || numero2<0);
	do {
	cout<<"Inserire il terzo numero: ";
	cin>>numero3;
	if (numero3>=10 || numero3<0) {
	cout<<"Numero sbagliato, sono compresi solo numeri con 1 cifra"<<endl;
	}	
	} while (numero3>=10 || numero3<0);
	do {
	cout<<"Inserire il quarto numero: ";
	cin>>numero4;
	if (numero4>=10 || numero4<0) {
	cout<<"Numero sbagliato, sono compresi solo numeri con 1 cifra"<<endl;
	}	
	} while (numero4>=10 || numero4<0);
	do {
	cout<<"Inserire il primo numero di sblocco: ";	
	cin>>numerop1;
	cout<<"Inserire il secondo numero di sblocco: ";
	cin>>numerop2;
	cout<<"Inserire il terzo numero di sblocco: ";
	cin>>numerop3;
	cout<<"Inserire il quarto numero di sblocco: ";
	cin>>numerop4;
	if (numerop1==numero1 && numerop2==numero2 && numerop3==numero3 && numerop4==numero4) {
		cout<<"App sbloccata"<<endl;
	}
	if (numerop1!=numero1 || numerop2!=numero2 || numerop3!=numero3 || numerop4!=numero4) {
		cout<<"Codice errato, riprovare"<<endl;
	}
} while (numerop1!=numero1 || numerop2!=numero2 || numerop3!=numero3 || numerop4!=numero4);
}
