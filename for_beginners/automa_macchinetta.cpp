#include <iostream>
using namespace std;

int main () {
	int moneta;
	int nmonete;
	do {
	cout<<"Inserire la moneta da 1 o 2 euro: ";
	cin>>moneta;
	if (moneta!=1 && moneta !=2) {
		cout<<"Bisogna inserire una moneta da 1 o da 2 euro"<<endl;
	}
	if (moneta==1 || moneta==2) {
	nmonete+=moneta;
	cout<<"Le monete inserite sono: "<<nmonete<<endl;
	}
	if (nmonete>=4) {
		nmonete-=5;
	}
    } while (0!=1);
    system ("pause");
}
