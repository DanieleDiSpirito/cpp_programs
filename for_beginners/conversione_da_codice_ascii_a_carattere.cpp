#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

main () {
	char carattere;
	int CAR_IN_ASCII, i;
	for (i=0;i=-1;i++) {
	cout <<"Inserisci codice da convertire \n";
	cin >>CAR_IN_ASCII;
	carattere = char(CAR_IN_ASCII);
	cout <<"Che corrisponde al carattere "<<carattere<<endl;
    }  
	system ("pause");
}
