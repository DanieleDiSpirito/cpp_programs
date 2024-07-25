#include <iostream>

using namespace std;

bool isPrime(int p) {
	int k = 3;
	while(k*k <= p) {
		if(p % k == 0) {
			return false;
		}
		k += 2;
	}
	return true;
}

int main() {
	int t;
	cout << "Insert the numbers of intervals: ";
	cin >> t;
	for(int i = 0; i < t; i++) {
		int n, m;
		cout << "Insert the 2 extreme of a valid integer: ";
		cin >> m >> n;
		if(m == 1) m++;
		if(m % 2 == 0) {
			if(m == 2) cout << m << endl;
			m++;
		}
		for(int p = m; p <= n; p += 2) { 
			if(isPrime(p)) cout << p << endl;
		}
	}
	return 0;
}
