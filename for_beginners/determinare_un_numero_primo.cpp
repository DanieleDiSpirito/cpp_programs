#include <iostream>
using namespace std;

int main () {
    int i=2,n;	
	for (cin>>n;n%i!=0;i++) {
		if (n==i+1) {
    		cout<<"Il numero e' primo\n";
    		return 0;
		}
	}
	cout<<"Il numero e' composto\n";
}
