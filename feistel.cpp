#include <iostream>
#include <stdint.h>

using namespace std;


uint8_t non_linear(uint8_t x) {
	return (((x << 7) ^ (x >> 2) ) + (x & 93) - (x & 19) + 123) & 0xff;
}

void fn_round(uint8_t *p) {
	uint8_t l = p[0];
	uint8_t r = p[1];

	uint8_t new_l = r;
	uint8_t new_r = l ^ non_linear(r);

	p[0] = new_l;
	p[1] = new_r;
}

void fn_deround(uint8_t *p) {
	uint8_t l = p[0];
	uint8_t r = p[1];

	uint8_t old_r = l;
	uint8_t old_l = r ^ non_linear(l);

	p[0] = old_l;
	p[1] = old_r;
}


int main() {
	for(uint16_t i = 0; i <= 0xff; i++) {
		uint16_t n = i;
		uint8_t *p = (uint8_t*) &n;
		cout << n << " -> ";
		fn_round(p);
		cout << n << " -> ";
		fn_deround(p);
		cout << n << endl;
	}
	return 0;
}
