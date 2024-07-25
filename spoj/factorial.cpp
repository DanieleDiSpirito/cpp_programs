#include <iostream>

using namespace std;

int Z(int n) {
	int zeros = 0;
	while(n >= 5) {
		zeros += (n / 5);
		n /= 5;
	}
	return zeros;
}

int main() {
	int n, num;
	cin >> n;
	for(int i = 0; i < n; i++) {
		cin >> num;
		cout << Z(num) << endl;
	}
	return 0;
}
