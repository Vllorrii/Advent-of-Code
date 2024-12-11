#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>

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

	std::map<long long, long long> stones, newstones;
	long long stone;
	while (file >> stone) stones.insert({ stone, 1 });
	file.close();

	int numdig, left, right;
	for (int blink = 0; blink < 75; ++blink) {
		newstones.clear();
		for (std::map<long long, long long>::iterator it = stones.begin(); it != stones.end(); ++it) {
			if (it->first == 0) newstones[1] += it->second;
			else if ((numdig = numdigits(it->first)) % 2 == 0) {
				split(it->first, numdig / 2, &left, &right);
				newstones[left] += it->second;
				newstones[right] += it->second;
			}
			else newstones[it->first * 2024] += it->second;
		}
		stones = newstones;
	}

	for (std::map<long long, long long>::iterator it = stones.begin(); it != stones.end(); ++it) { answer += it->second;

	return 0;
}