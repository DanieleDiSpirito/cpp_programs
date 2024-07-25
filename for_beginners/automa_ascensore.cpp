#include <iostream>
using namespace std;

int main () {
	int piano_iniziale;
	int pulsante;
	cout<<"Inserire il numero del piano da cui si parte: ";
	cin>>piano_iniziale;
	if (piano_iniziale==0) {
		cout<<"Inserire il numero del pulsante da cliccare: ";
		cin>>pulsante;
	    if (pulsante==0) {
	    cout<<"Fermo\n"<<"Pulsante terra"<<endl;
        }
	    if (pulsante==1) {
		cout<<"Salgo\n"<<"Primo piano"<<endl;
	    }
  	    if (pulsante==2) {
		cout<<"Salgo\n"<<"Secondo piano"<<endl;
	    }
	    if (pulsante!=0 && pulsante!=1 && pulsante!=2) {
		cout<<"Pulsante sbagliato, scegliere un numero tra 0 a 2"<<endl;
	    }
	}
	if (piano_iniziale==1) {
		cout<<"Inserire il numero del pulsante da cliccare: ";
		cin>>pulsante;
	    if (pulsante==0) {
	    cout<<"Scendo\n"<<"Piano terra"<<endl;
        }
	    if (pulsante==1) {
		cout<<"Fermo\n"<<"Primo piano"<<endl;
	    }
  	    if (pulsante==2) {
		cout<<"Salgo\n"<<"Secondo piano"<<endl;
	    }
	    if (pulsante!=0 && pulsante!=1 && pulsante!=2) {
		cout<<"Pulsante sbagliato, scegliere un numero tra 0 a 2"<<endl;
	    }
	}
	if (piano_iniziale==2) {
		cout<<"Inserire il numero del pulsante da cliccare: ";
		cin>>pulsante;
	    if (pulsante==0) {
	    cout<<"Scendo\n"<<"Piano terra"<<endl;
        }
	    if (pulsante==1) {
		cout<<"Scendo\n"<<"Primo piano"<<endl;
	    }
  	    if (pulsante==2) {
		cout<<"Fermo\n"<<"Secondo piano"<<endl;
	    }
	    if (pulsante!=0 && pulsante!=1 && pulsante!=2) {
		cout<<"Pulsante sbagliato, scegliere un numero tra 0 a 2"<<endl;
	    }
	}
	if (piano_iniziale!=0 && piano_iniziale!=1 && piano_iniziale!=2) {
		cout<<"Piano sbagliato, scegliere un numero tra 0 a 2"<<endl;
	    }
	system ("pause");
	return 0;
}
