#include <iostream>
using namespace std;

int main () {
	int a;
	int b;
	int c;
	cin >>a;
	cin >>b;
	cin >>c;
	if (a==b)
	    if (a==c)
	    cout <<"Triangolo equilatero"<<endl;
	    else
	    cout <<"Triangolo isoscele"<<endl;
	else
	    if (a==c)
	    cout <<"Triangolo isoscele"<<endl;
	    else
	        if (b==c)
	        cout <<"Triangolo isoscele"<<endl;
	        else
	        cout <<"Triangolo scaleno"<<endl;
	system ("pause");
}
