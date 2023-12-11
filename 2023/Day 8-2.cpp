#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

long long gcd(long long a, long long b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

long long lcm(long long a, long long b) {
	return (a / gcd(a, b)) * b;
}

inline int nodeToNum(std::string s) {
	return (s[0] - 'A') * 676 + (s[1] - 'A') * 26 + (s[2] - 'A');
}

int main() {
	long long answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line, instr;
	std::stringstream ssline;
	int map[17576][2];
	int numInstr, node, period;
	std::vector<int> currentNodes;

	std::getline(file, instr);
	std::getline(file, line);
	numInstr = instr.size();
	memset(map, 0, sizeof map);
	while (std::getline(file, line)) {
		node = nodeToNum(line.substr(0, 3));
		map[node][0] = nodeToNum(line.substr(7, 3));
		map[node][1] = nodeToNum(line.substr(12, 3));
		if (line[2] == 'A') currentNodes.push_back(node);
	}

	file.close();

	answer = 1;
	for (int i = 0; i < currentNodes.size(); ++i) {
		period = 0;
		while (currentNodes[i] % 26 != 25) {
			if (instr[period % numInstr] == 'L') currentNodes[i] = map[currentNodes[i]][0];
			else currentNodes[i] = map[currentNodes[i]][1];
			period += 1;
		}
		answer = lcm(answer, lcm(period, instr.size()));
	}

	return 0;
}