#include <iostream>
#include <stdlib.h>
using namespace std;
//inserire le cifre del codice//
int main () {
	int n,i;
	cin>>n;
	for (;n!=0;n--) {
		cout<<rand() % 10;
	}
	system ("pause");
}
