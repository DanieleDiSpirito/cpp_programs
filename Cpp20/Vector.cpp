#include <iostream>
#include <vector>

using namespace std;

class Vector {
private:
	vector<int> v;
	int size;

public:
	Vector() {
		this->size = 0;
	}

	Vector(const vector<int>& v1) {
		this->v = v1;
		this->size = v1.size();
	}

	void print() const {
		cout << "Vector{";
		for(const auto& el: v) {
			cout << el << ",";
		}
		cout << "}";
	}

	void add(int new_el) {
		this->v.push_back(new_el);
		this->size++;
	}

	int getSize() const {
		return this->size;
	}

	int operator[](int i) const {
		if(i >= 0 && i < this->size) return this->v[i];
		return 0;
	}

	Vector operator+(const Vector& v1) const {
		int l = this->getSize();
		int s = v1.getSize();
		vector<int> res(max(l, s), 0);
		for(int i = 0; i < min(l, s); i++) {
			res[i] = this->v[i] + v1[i];
		}
		int k = min(l, s);
		if(l <= s) {
			while(k < s) res[k++] = v1[k];
		} else {
			while(k < l) res[k++] = v[k];
		}
		return Vector(res);
	}
};

ostream& operator<<(ostream& os, const Vector& v) {
	v.print();
	return os;
}

int main() {
	Vector v1;
	v1.add(2);
	v1.add(3);
	v1.add(4);
	cout << "v1 == " << v1 << endl;
	vector<int> tmp = {1,3,0,2};
	Vector v2(tmp);
	cout << "v2 == " << v2 << endl;
	cout << "v1 + v2 == " << v2 + v1 << endl;
	for(int i = 0; i < v1.getSize(); i++) {
		cout << "v[" << i << "] == " << v1[i] << endl;
	}
	return 0;
}

