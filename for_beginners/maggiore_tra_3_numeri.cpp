#include <iostream>
using namespace std;

int main () {
	int a;
	int b;
	int c;
	int nummaggiore;
	cout <<"Inserisci il primo numero"<<endl;
	cin >> a;
	cout <<"Inserisci il secondo numero"<<endl;
	cin >> b;
	cout <<"Inserisci il terzo numero"<<endl;
	cin >> c;
	if (a>b)
        if (a>c)
        nummaggiore = a;
        else  //sei un romanazzi//
        nummaggiore = c;
    else
        if (b>c)
        nummaggiore = b; //nanni è stato qui//
        else
        nummaggiore = c;
    cout <<"Il numero maggiore dei 3 = "<<nummaggiore<<endl;
    system ("pause");
    }
