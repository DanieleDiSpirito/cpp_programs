#include <iostream>
using namespace std;

int main () {
	float a,b,n;
	for (;n!=5;) {
	cin>>a;
	n++;
	cin>>b;
	n++;
	if (a+b==5) {
		cout<<"La somma tra "<<a<<" e "<<b<<" e' 5";
		return 0;
	}
	else {
		cout<<"La somma tra "<<a<<" e "<<b<<" non e' 5 ma "<<a+b;
	}
    }
}
