#include <iostream>
using namespace std;

int main () {
	int a, n=1;
	cin>>a;
	do {
		if (n<10) {
			cout<<n<<")    "<<a<<"\n";
		}
		else {
		    if (n<100) {
			cout<<n<<")   "<<a<<"\n";
		    }
		    else {
		    	if (n<1000) {
		    		cout<<n<<")  "<<a<<"\n";
				}
				else {
					cout<<n<<") "<<a<<"\n";
				}
			}
		}
		a--;
		n++;
	} while (a>=1);
}
