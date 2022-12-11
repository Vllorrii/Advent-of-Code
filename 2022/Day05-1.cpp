#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

struct Instruction {
	int amount;
	int from;
	int to;
};

// Day 5 - Part 2
int main() {
	char* answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	std::vector<std::vector<char>> crates;
	std::vector<Instruction> instructions;
	Instruction instr;
	char crate[4];
	int piles = 0;

	do {
		file.read(crate, 4);
		++piles;
	} while (crate[3] != '\n');
	file.clear();
	file.seekg(0);

	crates = std::vector<std::vector<char>>(piles, std::vector<char>());

	while (std::getline(file, line)) {
		if (line.size() == 0) break;

		ssline = std::stringstream(line);
		piles = 0;
		while (!ssline.eof()) {
			ssline.read(crate, 4);
			if (isalpha(crate[1])) crates[piles].push_back(crate[1]);
			++piles;
		}
	}
	for (std::vector<std::vector<char>>::iterator it = crates.begin(); it < crates.end(); ++it) {
		std::reverse((*it).begin(), (*it).end());
	}
	while (std::getline(file, line)) {
		ssline = std::stringstream(line);
		instr = {};
		ssline >> line >> instr.amount >> line >> instr.from >> line >> instr.to;
		instructions.push_back(instr);
	}

	file.close();

	for (std::vector<Instruction>::iterator it = instructions.begin(); it < instructions.end(); ++it) {
		for (int i = 0; i < (*it).amount; ++i) {
			crates[(*it).to - 1].push_back(crates[(*it).from - 1].back());
			crates[(*it).from - 1].pop_back();
		}
	}

	answer = new char[crates.size() + 1];
	for (int i = 0; i < crates.size(); ++i) {
		answer[i] = crates[i].back();
	}
	answer[crates.size()] = '\0';

	delete[] answer;

	return 0;
}