#include <iostream>
#include <vector>

using namespace std;

bool update_vect(vector<int>&, int, int);
void print_vect(const vector<int>&);

int main() {
	int x {3};
	int& r = x; // reference
	int* p = &x; // pointer
	*p = 3;
	cout << p << " = " << &r << " = " << &x << endl;
	cout << *p << " = " << r << " = " << x << endl;

	vector<int> v(5, 0);
	uint8_t i = 0;
	for(auto& el: v) {
		el = ++i;
	}
	cout << "Size of i: " << sizeof(i) << "\nSize of x: " << sizeof(x) << endl; 
	print_vect(v);
	if(update_vect(v, 0, ++i)) {
		cout << "Updated vector: " << endl;
		print_vect(v);
	}
	return 0;
}

bool update_vect(vector<int>& v, int posix, int value) {
	if (posix >= v.size() && posix < 0) return false;
	v[posix] = value;
	return true;
}

void print_vect(const vector<int>& v) {
	for(const auto& el: v) {
		cout << el << " ";
	}
	cout << endl;
}
