#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	size_t i;
	int lastdigit = 0;
	while (std::getline(file, line)) {
		for (i = 0u; i < line.size(); ++i) {
			if (isdigit(line[i])) {
				lastdigit = line[i] - '0';
				answer += lastdigit * 10;
				break;
			}
		}

		for (; i < line.size(); ++i) {
			if (isdigit(line[i])) {
				lastdigit = line[i] - '0';
			}
		}
		answer += lastdigit;
	}

	file.close();

	return 0;
}