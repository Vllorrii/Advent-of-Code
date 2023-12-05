#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int game[] = {
	12, // red
	13, // green
	14  // blue
};

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line, elem, cubes;
	std::stringstream ssline, sselem;
	int gameID, pos, amount;
	bool impossible;
	while (std::getline(file, line)) {
		ssline = std::stringstream(line);
		ssline.ignore(5);
		std::getline(ssline, elem, ':');
		gameID = std::stoi(elem);
		impossible = false;
		while (std::getline(ssline, elem, ';')) {
			sselem = std::stringstream(elem);
			while (std::getline(sselem, cubes, ',')) {
				pos = cubes.rfind(' ');
				amount = std::stoi(cubes.substr(1, pos - 1));
				switch (cubes.substr(pos + 1).at(0)) {
				case 'r': if (amount > game[0]) { impossible = true; } break;
				case 'g': if (amount > game[1]) { impossible = true; } break;
				default:  if (amount > game[2]) { impossible = true; } break;
				}

				if (impossible) break;
			}

			if (impossible) break;
		}

		if (!impossible) answer += gameID;
	}

	file.close();

	return 0;
}