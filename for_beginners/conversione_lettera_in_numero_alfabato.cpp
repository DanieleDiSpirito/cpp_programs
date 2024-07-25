#include <iostream>
using namespace std;

main () {
	char lettera;
	unsigned int numero;
	cin >>lettera;
	/*inizio dalla decima riga così è più facile contare 26 if (cioè un if per ogni lettera)
	non mi va di lasciare spazi vuoti*/
	if (lettera=='a') numero=1;
	if (lettera=='b') numero=2;
	if (lettera=='c') numero=3;
	if (lettera=='d') numero=4;
	if (lettera=='e') numero=5;
	if (lettera=='f') numero=6;
	if (lettera=='g') numero=7;
	if (lettera=='h') numero=8;
	if (lettera=='i') numero=9;
	if (lettera=='j') numero=10;
	if (lettera=='k') numero=11;
	if (lettera=='l') numero=12;
	if (lettera=='m') numero=13;
	if (lettera=='n') numero=14;
	if (lettera=='o') numero=15;
	if (lettera=='p') numero=16;
	if (lettera=='q') numero=17;
	if (lettera=='r') numero=18;
	if (lettera=='s') numero=19;
	if (lettera=='t') numero=20;
	if (lettera=='u') numero=21;
	if (lettera=='v') numero=22;
	if (lettera=='w') numero=23;
	if (lettera=='x') numero=24;
	if (lettera=='y') numero=25;
	if (lettera=='z') numero=26;
	cout<<"Il numero e': "<<numero<<"\n"<<endl;
	system ("pause");
}
