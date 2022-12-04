#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// Day 1 - Part 1 and 2
int main() {
	long long answer = 0LL;

	std::ifstream file("input.txt", std::ios::in);

	size_t TOP = 1; // Part 1
	// size_t TOP = 3; // Part 2
	std::string line;
	std::vector<int> cals = std::vector<int>();
	std::vector<int> calsmax = std::vector<int>(TOP, 0);
	int j = 0;
	bool repl = false;
	int cal = 0;
	while (std::getline(file, line)) {
		if (line == "") {
			cals.push_back(cal);
			repl = false;
			for (j = 0; j < TOP; ++j) {
				if (cal > calsmax[j]) {
					repl = true;
				} else {
					break;
				}
			}
			--j;
			if (repl) {
				for (int k = 0; k < j && k < TOP - 1; ++k) {
					calsmax[k] = calsmax[k + 1];
				}
				calsmax[j] = cal;
			}
			cal = 0;
		} 		else cal += std::stoi(line);
	}

	file.close();

	if (cal != 0) cals.push_back(cal);
	for (j = 0; j < TOP; ++j) answer += calsmax[j];

	return 0;
}