#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main() {
	int answer = 1;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;

	std::vector<int> time = std::vector<int>();
	std::vector<int> dist = std::vector<int>();

	std::getline(file, line);
	ssline = std::stringstream(line);
	while (ssline.good()) {
		if (!isdigit(ssline.peek())) {
			ssline.get();
			continue;
		}
		std::getline(ssline, line, ' ');
		time.push_back(std::stoi(line));
	}
	std::getline(file, line);
	ssline = std::stringstream(line);
	while (ssline.good()) {
		if (!isdigit(ssline.peek())) {
			ssline.get();
			continue;
		}
		std::getline(ssline, line, ' ');
		dist.push_back(std::stoi(line));
	}

	file.close();

	int tmin, tmax;
	for (size_t i = 0u; i < time.size(); ++i) {
		tmin = (int)floor(0.5 * time[i] - 0.5 * sqrt((double)time[i] * time[i] - 4.0 * dist[i])) + 1;
		tmax = (int)ceil(0.5 * time[i] + 0.5 * sqrt((double)time[i] * time[i] - 4.0 * dist[i])) - 1;
		answer *= (tmax - tmin + 1);
	}

	return 0;
}