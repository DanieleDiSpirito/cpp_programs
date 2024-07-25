#include <iostream>
using namespace std;

main () {
	char lettera;
	unsigned int numero;
	cin >>numero;
	/*inizio dalla decima riga così è più facile contare 26 if (cioè un if per ogni lettera)
	non mi va di lasciare spazi vuoti*/
	if (numero==1) lettera='a';
	if (numero==2) lettera='b';
	if (numero==3) lettera='c';
	if (numero==4) lettera='d';
	if (numero==5) lettera='e';
	if (numero==6) lettera='f';
	if (numero==7) lettera='g';
	if (numero==8) lettera='h';
	if (numero==9) lettera='i';
	if (numero==10) lettera='j';
	if (numero==11) lettera='k';
	if (numero==12) lettera='l';
	if (numero==13) lettera='m';
	if (numero==14) lettera='n';
	if (numero==15) lettera='o';
	if (numero==16) lettera='p';
	if (numero==17) lettera='q';
	if (numero==18) lettera='r';
	if (numero==19) lettera='s';
	if (numero==20) lettera='t';
	if (numero==21) lettera='u';
	if (numero==22) lettera='v';
	if (numero==23) lettera='w';
	if (numero==24) lettera='x';
	if (numero==25) lettera='y';
	if (numero==26) lettera='z';
	cout<<"La lettera e': "<<lettera<<"\n"<<endl;
	system ("pause");
}
