#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

bool isSafe(std::vector<int> report) {
	int fac = report[1] > report[0] ? 1 : -1;
	for (size_t i = 1; i < report.size(); ++i) {
		if (fac * (report[i] - report[i - 1]) < 1 || fac * (report[i] - report[i - 1]) > 3) return false;
	}
	return true;
}

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	std::vector<int> report;
	std::vector<int> damped;
	int num;
	while (std::getline(file, line)) {
		ssline = std::stringstream(line);
		report.clear();
		while (ssline >> num) report.push_back(num);
		for (size_t i = 0; i < report.size(); ++i) {
			damped = report;
			damped.erase(damped.begin() + i);
			if (isSafe(damped)) {
				++answer;
				break;
			}
		}
	}
	
	file.close();

	return 0;
}