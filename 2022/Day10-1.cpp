#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Day 10 - Part 1
int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string cmd;
	int cycle = 0;
	int X = 1;
	while (file >> cmd) {
		++cycle;
		if ((cycle - 20) % 40 == 0) answer += X * cycle;

		if (cmd == "addx") {
			++cycle;
			if ((cycle - 20) % 40 == 0) answer += X * cycle;

			file >> cmd;
			X += std::stoi(cmd);
		}
	}

	file.close();

	return 0;
}