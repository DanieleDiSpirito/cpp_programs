#include <iostream>
using namespace std;

int main () {
    int a, b;
    do {
	cout<<"Digitare il valore di a"<<endl;
	cin>>a;
	switch (a) {
	case (3):
		cout<<"a e' uguale a 3"<<endl;
		break;
	case (2):
		cout<<"a e' uguale a 3"<<endl;
		break;
	default:
		cout<<"a e' diverso da 2 e 3"<<endl;
		b++;
	}
	} while (b!=1);
}
