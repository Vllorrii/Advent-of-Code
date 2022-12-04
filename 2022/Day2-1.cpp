#include <iostream>
#include <fstream>
#include <string>

// Day 2 - Part 1
int main() {
	long long answer = 0LL;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	while (std::getline(file, line)) {
		if (line.size() > 0) {
			answer += line[2] - 'W';
			if      (line[0] == 'A' && line[2] == 'Y' || line[0] == 'B' && line[2] == 'Z' || line[0] == 'C' && line[2] == 'X') answer += 6LL;
			else if (line[0] == 'A' && line[2] == 'X' || line[0] == 'B' && line[2] == 'Y' || line[0] == 'C' && line[2] == 'Z') answer += 3LL;
			else if (line[0] == 'A' && line[2] == 'Z' || line[0] == 'B' && line[2] == 'X' || line[0] == 'C' && line[2] == 'Y') answer += 0LL;
		}
	}

	file.close();

	return 0;
}