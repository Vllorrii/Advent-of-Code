#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

inline std::string rmvWhitespace(std::string str) {
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	return str;
}

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	int i, cardNum, winning[10], mine, amount[219], numMatches;
	bool first;
	
	for (i = 0; i < 219; ++i) amount[i] = 1;
	cardNum = 0;
	while (std::getline(file, line)) {
		memset(winning, 0, sizeof winning);
		for (i = 0; i < 10; ++i) {
			winning[i] = std::stoi(rmvWhitespace(line.substr(10 + i * 3, 2)));
		}
		first = true;
		numMatches = 0;
		for (i = 0; i < 25; ++i) {
			mine = std::stoi(rmvWhitespace(line.substr(42 + i * 3, 2)));
			for (int j = 0; j < 10; ++j) {
				if (mine == winning[j]) ++numMatches;
			}
		}
		
		for (i = cardNum + 1; i < std::min(219, cardNum + 1 + numMatches); ++i) {
			amount[i] += amount[cardNum];
		}

		answer += amount[cardNum];
		++cardNum;
	}

	file.close();

	return 0;
}