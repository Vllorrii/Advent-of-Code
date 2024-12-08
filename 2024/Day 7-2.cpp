#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	std::vector<long long> cals;
	long long cal, test = 0ll;
	bool correct;
	while (std::getline(file, line)) {
		ssline = std::stringstream(line);
		std::getline(ssline, line, ':');
		cals.clear();
		while (ssline >> cal) cals.push_back(cal);
		correct = false;
		for (size_t p = 0; p < (size_t)std::pow(3.0, cals.size()); ++p) {
			cal = p;
			test = cals[0];
			for (size_t i = 1; i < cals.size(); ++i) {
				if (cal % 3 == 0) { test += cals[i]; }
				else if (cal % 3 == 1) { test *= cals[i]; }
				else {
					test *= (long long)std::pow(10.0, std::floor(std::log10(cals[i])) + 1.0);
					test += cals[i];
				}
				cal /= 3;
			}
			if (std::stoll(line) == test) {
				correct = true;
				break;
			}
		}
		if (correct) answer += test;
	}

	file.close();

	return 0;
}