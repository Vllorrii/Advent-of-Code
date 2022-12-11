#include <iostream>
#include <fstream>
#include <string>

// Day 3 - Part 2
int main() {
	long long answer = 0LL;

	std::ifstream file("input.txt", std::ios::in);

	const unsigned int grouping = 3u;
	unsigned long long rucksack[grouping];
	unsigned long long item = 0uLL;
	std::string line;
	while (!file.eof()) {
		memset(rucksack, 0uLL, sizeof(rucksack[0]) * grouping);
		item = UINT64_MAX;
		for (int i = 0; i < grouping; ++i) {
			std::getline(file, line);
			for (int j = 0; j < temp.size(); ++j) {
				if (isupper(line[j])) rucksack[i] |= 0x4000000uLL << (line[j] - 'A');
				else                  rucksack[i] |= 0x0000001uLL << (line[j] - 'a');
			}
			item &= rucksack[i];
		}
		if (item == 0) continue;
		do ++answer; while (item >>= 1u);
	}

	file.close();

	return 0;
}