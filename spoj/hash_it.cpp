#include <iostream>
#include <cstring>
#include <string>
#include <vector>

using namespace std;
	
class Table {
private:
	vector<string> mp;
	int size;
	
	
	int hash(const string& key) const {
		return h(key) % 101;
	}

	int h(const string& key) const {
		int res = 0;
		int i = 1;
		for(const auto& ch: key) {
			res += static_cast<int>(ch) * i++;
		}
		return res * 19;
	}
public:
	Table(): mp(101, ""), size(0) {}
	
	void add(const string& key) {
		int Hash = this->hash(key);
		for(int j = 0; j < 20; j++) {
			int pos = (Hash + j*j + 23*j) % 101;
			if(mp[pos] == key) return;
		}
		for(int j = 0; j < 20; j++) {
			int pos = (Hash + j*j + 23*j) % 101;
			if(mp[pos] == "") {
				mp[pos] = key;
				size++;
				return;
			}
		}
	}

	void del(const string& key) {
		int Hash = this->hash(key);
		for(int j = 0; j < 20; j++) {
			int pos = (Hash + j*j + 23*j) % 101;
			if(mp[pos] == key) {
				mp[pos] = ""; // empty
				size--;
				return;
			}
		}
	}
	
	int getSize() const {
		return this->size;
	}
	
	void print() {
		for(int k = 0; k < this->mp.size(); k++) {
			if(mp[k] != "") cout << k << ":" << mp[k] << endl;
		}
	}
	
	
};

int main() {
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		Table table;
		int n_op;
		cin >> n_op;
		for(int j = 0; j < n_op; j++) {
			string command;
			cin >> command;
			string cmd = command.substr(0, 3);
			string key = command.substr(4);
			if(key == "") continue;
			if(cmd == "ADD") {
				table.add(key);
			} else { // "DEL"
				table.del(key);
			}
		}
		cout << table.getSize() << endl;
		table.print();
	}
	return 0;
}
