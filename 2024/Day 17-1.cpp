#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

inline int pow2(int n) {
	int result = 1;
	while (n > 0) {
		result *= 2;
		--n;
	}
	return result;
}

int main() {
	std::string answer;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	int reg[3] = {}, i = 0;
	std::vector<int> program;
	std::getline(file, line);
	while (line.size() > 0) {
		sscanf_s(line.c_str(), "Register %*c: %d", &reg[i++]);
		std::getline(file, line);
	}
	std::getline(file, line);
	ssline = std::stringstream(line);
	ssline.ignore(9);
	while (std::getline(ssline, line, ',')) program.push_back(line[0] - '0');

	file.close();

	int opcode, combo, lit;
	for (std::vector<int>::iterator it = program.begin(); it != program.end();) {
		opcode = *it;
		lit = *(it + 1);
		combo = lit;
		if (lit == 4 || lit == 5 || lit == 6) combo = reg[lit - 4];

		switch (opcode) {
		case 0: /* adv */ reg[0] = reg[0] / pow2(combo); break;
		case 1: /* bxl */ reg[1] = reg[1] ^ lit; break;
		case 2: /* bst */ reg[1] = combo % 8; break;
		case 3: /* jnz */
			if (reg[0] != 0) {
				it = program.begin() + lit;
				continue;
			}
			break;
		case 4: /* bxc */ reg[1] = reg[1] ^ reg[2]; break;
		case 5: /* out */ if (answer.size() != 0) { answer.push_back(','); } answer.push_back('0' + combo % 8); break;
		case 6: /* bdv */ reg[1] = reg[0] / pow2(combo); break;
		case 7: /* cdv */ reg[2] = reg[0] / pow2(combo); break;
		}

		it += 2;
	}

	return 0;
}