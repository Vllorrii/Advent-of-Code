#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

inline std::string rmvWhitespace(std::string str) {
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	return str;
}

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	int i, winning[10], mine, score;
	bool first;
	while (std::getline(file, line)) {
		memset(winning, 0, sizeof winning);
		for (i = 0; i < 10; ++i) {
			winning[i] = std::stoi(rmvWhitespace(line.substr(10 + i * 3, 2)));
		}
		first = true;
		score = 0;
		for (i = 0; i < 25; ++i) {
			mine = std::stoi(rmvWhitespace(line.substr(42 + i * 3, 2)));
			for (int j = 0; j < 10; ++j) {
				if (mine == winning[j]) {
					if (first) { score = 1; first = false; }
					else score *= 2;
				}
			}
		}
		answer += score;
	}

	file.close();

	return 0;
}