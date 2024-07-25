#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

main () {
	char carattere;
	int CAR_IN_ASCII, i;
	for (i=0;i=-1;i++) {
	cout <<"Inserire il carattere da convertire \n";
	cin >>carattere;
	cout <<"\n";
	CAR_IN_ASCII = int(carattere);
	cout <<"\n";
	cout <<"Il carattere in ASCII corrisponde a "<<CAR_IN_ASCII<<endl;
    }  
	system ("pause");
}
