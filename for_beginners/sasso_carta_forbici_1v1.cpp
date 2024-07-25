#include <iostream>
#include <stdlib.h>
using namespace std;

main () {
	int mp1;
	int mp2;
	int pp1=0;
	int pp2=0;
	cout<<"REGOLE:\n8 vale 'sasso'\n9 vale 'carta'\n0 vale 'forbici"<<endl;
	do {
		cout<<"Player 1: ";
		cin>>mp1;
		cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"<<endl;
		cout<<"Player 2: ";
		cin>>mp2;
		if (mp1==8 and mp2==9) pp2++;
		if (mp1==8 and mp2==0) pp1++;
		if (mp1==9 and mp2==0) pp2++;
		if (mp2==8 and mp1==9) pp1++;
		if (mp2==8 and mp1==0) pp2++;
		if (mp2==9 and mp1==0) pp1++;
		cout <<pp1<<" a "<<pp2<<endl;
	//per decretare il vincitore//
		if (pp1==10 or pp2==10) 
	 if (pp2>9) return 0; cout<<"Player 1 won";
	 if (pp1>9) return 0; 8ocout<<"Player 2 won";
	} while (1!=0);
}
