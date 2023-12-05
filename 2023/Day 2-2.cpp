#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line, elem, cubes;
	std::stringstream ssline, sselem;
	int gameID, pos, amount;
	int gameMin[3];
	while (std::getline(file, line)) {
		ssline = std::stringstream(line);
		ssline.ignore(5);
		std::getline(ssline, elem, ':');
		gameID = std::stoi(elem);
		memset(gameMin, 0, sizeof gameMin);
		while (std::getline(ssline, elem, ';')) {
			sselem = std::stringstream(elem);
			while (std::getline(sselem, cubes, ',')) {
				pos = cubes.rfind(' ');
				amount = std::stoi(cubes.substr(1, pos - 1));
				switch (cubes.substr(pos + 1).at(0)) {
				case 'r': gameMin[0] = std::max(gameMin[0], amount); break;
				case 'g': gameMin[1] = std::max(gameMin[1], amount); break;
				default:  gameMin[2] = std::max(gameMin[2], amount); break;
				}
			}
		}
		answer += gameMin[0] * gameMin[1] * gameMin[2];
	}

	file.close();

	return 0;
}