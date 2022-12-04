#include <iostream>
#include <fstream>
#include <string>

// Day 3 - Part 1
int main() {
	long long answer = 0LL;

	std::ifstream file("input.txt", std::ios::in);

	unsigned long long rucksack1 = 0uLL;
	unsigned long long rucksack2 = 0uLL;
	unsigned long long item = 0uLL;
	size_t half;
	std::string line;
	while (std::getline(file, line)) {
		half = line.size() / 2;
		rucksack1 = 0uLL;
		rucksack2 = 0uLL;
		for (int i = 0; i < half; ++i) {
			if (isupper(line[i]))        rucksack1 |= 0x4000000uLL << (line[i] - 'A');
			else                         rucksack1 |= 0x0000001uLL << (line[i] - 'a');
			if (isupper(line[i + half])) rucksack2 |= 0x4000000uLL << (line[i + half] - 'A');
			else                         rucksack2 |= 0x0000001uLL << (line[i + half] - 'a');
		}
		item = rucksack1 & rucksack2;
		if (item == 0) continue;
		do ++answer; while (item >>= 1u);
	}

	file.close();

	return 0;
}