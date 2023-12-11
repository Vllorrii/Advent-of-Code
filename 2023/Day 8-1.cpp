#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

inline int nodeToNum(std::string s) {
	return (s[0] - 'A') * 676 + (s[1] - 'A') * 26 + (s[2] - 'A');
}

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line, instr;
	std::stringstream ssline;
	int numInstr, currentNode;

	std::getline(file, instr);
	std::getline(file, line);
	numInstr = instr.size();
	int map[17576][2];
	memset(map, 0, sizeof map);
	while (std::getline(file, line)) {
		map[nodeToNum(line.substr(0, 3))][0] = nodeToNum(line.substr(7, 3));
		map[nodeToNum(line.substr(0, 3))][1] = nodeToNum(line.substr(12, 3));
	}

	file.close();

	currentNode = 0;
	while (currentNode != 17575) {
		if (instr[answer % numInstr] == 'L') currentNode = map[currentNode][0];
		else currentNode = map[currentNode][1];
		++answer;
	}

	return 0;
}