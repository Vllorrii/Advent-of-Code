#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

bool isSymbol(char c) {
	return (c != '.' && !isdigit(c));
}

int sumPartNums(std::string prev, std::string curr, std::string next) {
	int i, pos1, pos2, partNum, sumParts;
	int numElem = (int)curr.size();

	sumParts = 0;
	for (i = 0; i < numElem; ++i) {
		if (isdigit(curr[i])) {
			pos1 = i++;
			while (isdigit(curr[i])) {
				if (i == numElem) break;
				++i;
			}
			pos2 = i;

			partNum = std::stoi(curr.substr(pos1, pos2 - pos1));
			if (pos1 > 0) {
				if (isSymbol(curr[pos1 - 1])) {
					sumParts += partNum;
					continue;
				}
			}
			if (pos2 < curr.size()) {
				if (isSymbol(curr[pos2])) {
					sumParts += partNum;
					continue;
				}
			}
			for (int j = std::max(0, pos1 - 1); j < std::min(numElem, pos2 + 1); ++j) {
				if (isSymbol(prev[j]) || isSymbol(next[j])) {
					sumParts += partNum;
					break;
				}
			}
		}
	}

	return sumParts;
}

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line, prev, next;
	std::stringstream ssline;

	std::getline(file, line);
	std::getline(file, next);
	prev = std::string(line.size(), '.');
	answer += sumPartNums(prev, line, next);
	prev = line;
	line = next;
	while (std::getline(file, next)) {
		answer += sumPartNums(prev, line, next);
		prev = line;
		line = next;
	}
	next = std::string(line.size(), '.');
	answer += sumPartNums(prev, line, next);

	file.close();

	return 0;
}