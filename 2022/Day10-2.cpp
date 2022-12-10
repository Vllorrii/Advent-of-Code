#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Day 10 - Part 2
int main() {
	std::ifstream file("input.txt", std::ios::in);

	std::string cmd;
	int cycle = 0;
	int X = 1;
	const int SCREEN_WIDTH = 40;
	while (file >> cmd) {
		std::cout << (std::abs(X - (cycle % SCREEN_WIDTH)) <= 1 ? '#' : '.');
		++cycle;
		if (cycle % SCREEN_WIDTH == 0) std::cout << std::endl;

		if (cmd == "addx") {
			std::cout << (std::abs(X - (cycle % SCREEN_WIDTH)) <= 1 ? '#' : '.');
			++cycle;
			if (cycle % SCREEN_WIDTH == 0) std::cout << std::endl;

			file >> cmd;
			X += std::stoi(cmd);
		}
	}

	file.close();

	return 0;
}