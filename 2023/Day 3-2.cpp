#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int sumGearRatios(std::string prev, std::string curr, std::string next) {
	int i, pos1, pos2, partNum, sumGear;
	int numElem = (int)curr.size();

	std::vector<std::pair<int, int>> isGearRatio = std::vector<std::pair<int, int>>(numElem, std::pair<int, int>(0, 1));
	for (i = 0; i < numElem; ++i) {
		if (isdigit(prev[i])) {
			pos1 = i++;
			while (isdigit(prev[i])) {
				if (i == numElem) break;
				++i;
			}
			pos2 = i;
			partNum = std::stoi(prev.substr(pos1, pos2 - pos1));

			for (int j = std::max(0, pos1 - 1); j < std::min(numElem, pos2 + 1); ++j) {
				if (curr[j] == '*') {
					isGearRatio[j].first += 1;
					isGearRatio[j].second *= partNum;
				}
			}
		}
	}

	for (i = 0; i < numElem; ++i) {
		if (isdigit(next[i])) {
			pos1 = i++;
			while (isdigit(next[i])) {
				if (i == numElem) break;
				++i;
			}
			pos2 = i;
			partNum = std::stoi(next.substr(pos1, pos2 - pos1));

			for (int j = std::max(0, pos1 - 1); j < std::min(numElem, pos2 + 1); ++j) {
				if (curr[j] == '*') {
					isGearRatio[j].first += 1;
					isGearRatio[j].second *= partNum;
				}
			}
		}
	}

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
				if (curr[pos1 - 1] == '*') {
					isGearRatio[pos1 - 1].first += 1;
					isGearRatio[pos1 - 1].second *= partNum;
				}
			}
			if (pos2 < curr.size()) {
				if (curr[pos2] == '*') {
					isGearRatio[pos2].first += 1;
					isGearRatio[pos2].second *= partNum;
				}
			}
		}
	}

	sumGear = 0;
	for (i = 0; i < numElem; ++i) {
		if (isGearRatio[i].first == 2) {
			sumGear += isGearRatio[i].second;
		}
	}

	return sumGear;
}

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line, prev, next;
	std::stringstream ssline;

	std::getline(file, line);
	std::getline(file, next);
	prev = std::string(line.size(), '.');
	answer += sumGearRatios(prev, line, next);
	prev = line;
	line = next;
	while (std::getline(file, next)) {
		answer += sumGearRatios(prev, line, next);
		prev = line;
		line = next;
	}
	next = std::string(line.size(), '.');
	answer += sumGearRatios(prev, line, next);

	file.close();

	return 0;
}