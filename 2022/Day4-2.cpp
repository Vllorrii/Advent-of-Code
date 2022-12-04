#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Day 4 - Part 2
int main() {
	long long answer = 0LL;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::string num;
	std::stringstream ssline;
	int range[2][2] = {};
	while (std::getline(file, line)) {
		ssline = std::stringstream(line);
		std::getline(ssline, num, '-');
		range[0][0] = std::stoi(num);
		std::getline(ssline, num, ',');
		range[0][1] = std::stoi(num);
		std::getline(ssline, num, '-');
		range[1][0] = std::stoi(num);
		std::getline(ssline, num);
		range[1][1] = std::stoi(num);

		if (range[0][0] <= range[1][1] && range[0][1] >= range[1][0]) ++answer;
	}

	file.close();

	return 0;
}