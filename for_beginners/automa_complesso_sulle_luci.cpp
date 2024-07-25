#include <iostream>
using namespace std;

int main () {
	int p;
	char stato_iniziale;
	cin>>stato_iniziale;
	do {
	if (stato_iniziale=='b') {
		cout<<"Inserire il pulsante da premere: ";
		cin>>p;
		if (p==1) {
		    cout<<"Luce destra accesa e luce sinistra spenta"<<endl;
		    stato_iniziale='d';
	    }
		if (p==2) {
			cout<<"Luce destra spenta e luce sinistra accesa"<<endl;
			stato_iniziale='s';
		}
		if (p!=1 && p!=2) {
			cout<<"Numero sbagliato, esistono solo 2 pulsanti"<<endl;
		}
	}
	if (stato_iniziale=='l') {
		cout<<"Inserire il pulsante da premere: ";
		cin>>p;
		if (p==1) {
		    cout<<"Luce destra spenta e luce sinistra accesa"<<endl;
		    stato_iniziale='s';
	    }
		if (p==2) {
			cout<<"Luce destra accesa e luce sinistra spenta"<<endl;
			stato_iniziale='d';
		}
		if (p!=1 && p!=2) {
			cout<<"Numero sbagliato, esistono solo 2 pulsanti"<<endl;
		}
	}
	if (stato_iniziale=='d') {
		cout<<"Inserire il pulsante da premere: ";
		cin>>p;
		if (p==1) {
		    cout<<"Entrambe le luci sono spente"<<endl;
		    stato_iniziale='b';
	    }
		if (p==2) {
			cout<<"Entrambe le luci sono accese"<<endl;
			stato_iniziale='l';
		}
		if (p!=1 && p!=2) {
			cout<<"Numero sbagliato, esistono solo 2 pulsanti"<<endl;
		}
    }
	if (stato_iniziale=='s') {
		cout<<"Inserire il pulsante da premere: ";
		cin>>p;
		if (p==1) {
		    cout<<"Entrambe le luci sono accese"<<endl;
		    stato_iniziale='l';
	    }
		if (p==2) {
			cout<<"Entrambe le luci sono spente"<<endl;
			stato_iniziale='b';
		}
		if (p!=1 && p!=2) {
			cout<<"Numero sbagliato, esistono solo 2 pulsanti"<<endl;
		}
	}
	} while (0!=1);
	system ("pause");
}
