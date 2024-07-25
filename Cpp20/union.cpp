#include <iostream>
#include <variant>

using namespace std;

enum class Type { integer, floating };

struct Entry {
	string name;
	Type type;
	double n;
	int i;
};

struct BetterEntry {
	string name;
	variant<double, int> n;
};

int main() {
	
	Entry entry = Entry();

	entry.name = "entry";
	entry.type = Type::integer;
	entry.n = 1.2;
	entry.i = (int) entry.n;
	
	// using enum Type; // for C++20 only
	
	if(entry.type == Type::integer) {
		cout << entry.i << endl;
	} else {
		cout << entry.n << endl;
	}

	BetterEntry be = BetterEntry();

	be.name = "betterEntry";
	be.n = 1.2;

	if(holds_alternative<int>(be.n)) {
		cout << get<int>(be.n) << endl;
	} else {
		cout << get<double>(be.n) << endl;
	}

	return 0;
}
