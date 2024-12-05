#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	std::vector<std::pair<int, int>> rules;
	std::pair<int, int> rule;
	while (std::getline(file, line)) {
		if (line.empty()) break;
		ssline = std::stringstream(line);
		std::getline(ssline, line, '|');
		rule.first = std::stoi(line);
		std::getline(ssline, line);
		rule.second = std::stoi(line);
		rules.push_back(rule);
	}

	int temp;
	size_t r;
	bool correct;
	std::vector<int> pages;
	while (std::getline(file, line)) {
		pages.clear();
		ssline = std::stringstream(line);
		while (std::getline(ssline, line, ',')) pages.push_back(std::stoi(line));

		correct = true;
		for (size_t i = 0; i < pages.size(); ++i) {
			for (size_t j = i + 1; j < pages.size(); ++j) {
				for (r = 0; r < rules.size(); ++r) {
					if (pages[j - 1] == rules[r].second && pages[j] == rules[r].first) {
						correct = false;
						//temp = pages[j];
						//pages[j] = pages[j - 1];
						//pages[j - 1] = temp;
						break;
					}
				}
				if (!correct) break;
			}
			if (!correct) break;
		}

		if (correct) answer += pages[(pages.size() - 1) / 2];
	}

	file.close();

	return 0;
}