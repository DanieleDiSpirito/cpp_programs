#include <iostream>
#include <string>

using namespace std;

short isSubstring(string& needle, string& haystack) {
	int haySize = haystack.length(), needleSize = needle.length();
	for(int i = 0; i < haySize; i++) {
		int k = 0;
		for(int j = 0; j < needleSize; j++) {
			if(needle[j] == haystack[i+j]) k++;
		}
		if(k == needleSize) return 1;
	}
	return 0;
}

int main() {
	string A, B;
	for(int i = 0; i < 24; i++) {
		cin >> A >> B;
		cout << isSubstring(B, A) << endl;
	}
	return 0;
}
