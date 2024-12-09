#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::getline(file, line);
	std::vector<int> disk = std::vector<int>();
	for (size_t i = 0; i < line.size(); ++i) {
		if (i % 2 == 0) {
			for (size_t j = 0; j < (line[i] - '0'); ++j) disk.push_back(i / 2);
		} else {
			for (size_t j = 0; j < (line[i] - '0'); ++j) disk.push_back(-1);
		}
	}

	file.close();

	size_t currpos = 0;
	while (disk[++currpos] != -1);
	for (int i = disk.size() - 1; i >= 0; --i) {
		if (disk[i] == -1) continue;
		if (i <= currpos) break;
		disk[currpos] = disk[i];
		disk[i] = -1;
		while (disk[++currpos] != -1);
	}

	for (size_t i = 0; i < currpos; ++i) answer += i * disk[i];

	return 0;
}