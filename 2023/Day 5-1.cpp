#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main() {
	long long answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;

	long long destRgStart, srcRgStart, rgLen;
	std::vector<bool> conv;
	std::vector<long long> seeds = std::vector<long long>();

	std::getline(file, line);
	ssline = std::stringstream(line.substr(7));
	while (std::getline(ssline, line, ' ')) seeds.push_back(std::stoll(line));
	conv = std::vector<bool>(seeds.size(), false);
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::fill(conv.begin(), conv.end(), false);
		std::getline(file, line);
		while (!line.empty()) {
			ssline = std::stringstream(line);
			std::getline(ssline, line, ' ');
			destRgStart = std::stoll(line);
			std::getline(ssline, line, ' ');
			srcRgStart = std::stoll(line);
			std::getline(ssline, line);
			rgLen = std::stoll(line);

			for (size_t i = 0u; i < seeds.size(); ++i) {
				if (!conv[i]) {
					if (seeds[i] >= srcRgStart && seeds[i] < srcRgStart + rgLen) {
						seeds[i] = destRgStart + seeds[i] - srcRgStart;
						conv[i] = true;
					}
				}
			}
			std::getline(file, line);
		}
	}

	file.close();

	answer = *(std::min_element(seeds.begin(), seeds.end()));

	return 0;
}