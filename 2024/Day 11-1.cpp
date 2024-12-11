#include <stdio.h>
#include <iostream>
#include <fstream>
#include <list>

inline int numdigits(long long n) {
	int result = 0;
	while (n > 0) {
		++result;
		n /= 10;
	}
	return result;
}

inline void split(long long n, int numdig, int* a, int* b) {
	*b = n;
	for (int i = 0; i < numdig; ++i) n /= 10;
	*a = n;
	for (int i = 0; i < numdig; ++i) n *= 10;
	*b -= n;
}

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::list<long long> stones;
	long long stone;
	while (file >> stone) stones.push_back(stone);
	file.close();

	int numdig, left, right;
	for (int blink = 0; blink < 75; ++blink) {
		for (std::list<long long>::iterator it = stones.begin(); it != stones.end(); ++it) {
			if (*it == 0) {
				*it = 1;
			} else if ((numdig = numdigits(*it)) % 2 == 0) {
				split(*it, numdig / 2, &left, &right);
				*it = right;
				stones.insert(it, left);
			} else {
				*it *= 2024;
			}
		}
	}

	answer = stones.size();

	return 0;
}