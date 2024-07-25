#include <iostream>
using namespace std;

int main () {
	int fatt,  n, i;
	fatt = 1;
	cin>>n;
	for (i=n; i>1; i--)
	{
	fatt = fatt*i;
	}
	cout <<fatt<<endl;
	system ("pause");
}

