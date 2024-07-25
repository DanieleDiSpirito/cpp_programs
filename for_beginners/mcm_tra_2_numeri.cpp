#include <iostream>
using namespace std;

int main() {
  int a;
  int b;
  int n;
  cin >>a;
  cin >>b;
  for (n=1;n<100;n++) {
  	if (a*n==b) 
	  cout<<b<<endl;
  	else
  	    if (b*n==a) 
		  cout<<a<<endl;
  	    else 
  	      n=a*b;
		  cout<<n<<endl;
  }
  return 0;
}
