#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

typedef std::pair<long long, long long> Interval; // [start, end)

std::vector<Interval> overlap(Interval a, Interval b) {
	std::vector<Interval> result;
	if (a.second > b.first && a.first < b.second) {
		result.push_back({ std::max(a.first, b.first), std::min(a.second, b.second) });
		if (a.first < b.first) result.push_back({ a.first, b.first });
		if (a.second > b.second) result.push_back({ b.second, a.second });
	}
	return result;
}

int main() {
	long long answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;

	long long destRgStart, srcRgStart, rgLen;
	std::vector<Interval> seeds = std::vector<Interval>();
	std::vector<Interval> ovlps, newseeds;
	Interval iv;

	std::getline(file, line);
	ssline = std::stringstream(line.substr(7));
	while (std::getline(ssline, line, ' ')) {
		srcRgStart = std::stoll(line);
		std::getline(ssline, line, ' ');
		seeds.push_back({ srcRgStart, srcRgStart + std::stoll(line) });
	}
	std::getline(file, line);

	while (std::getline(file, line)) {
		std::getline(file, line);
		while (!line.empty()) {
			ssline = std::stringstream(line);
			std::getline(ssline, line, ' ');
			destRgStart = std::stoll(line);
			std::getline(ssline, line, ' ');
			srcRgStart = std::stoll(line);
			std::getline(ssline, line);
			rgLen = std::stoll(line);

			iv = { srcRgStart, srcRgStart + rgLen };
			for (size_t i = 0; i < seeds.size(); ++i) {
				if (!(ovlps = overlap(seeds[i], iv)).empty()) {
					newseeds.push_back({
						destRgStart + ovlps[0].first - srcRgStart,
						destRgStart + ovlps[0].second - srcRgStart,
					});

					if (ovlps.size() == 1) {
						seeds.erase(seeds.begin() + i);
						--i;
					}
					if (ovlps.size() > 1) {
						seeds[i] = ovlps[1];
					}
					if (ovlps.size() == 3) {
						seeds.insert(seeds.begin() + i + 1, ovlps[2]);
						++i;
					}
				}
			}
			std::getline(file, line);
		}
		for (size_t i = 0u; i < seeds.size(); ++i) newseeds.push_back(seeds[i]);
		std::sort(newseeds.begin(), newseeds.end());
		for (size_t i = 1u; i < newseeds.size(); ++i) {
			if (newseeds[i].first <= newseeds[i - 1u].second) {
				newseeds[i - 1u].second = std::max(newseeds[i].second, newseeds[i - 1u].second);
				newseeds.erase(newseeds.begin() + i);
				--i;
			}
		}
		seeds = newseeds;
		newseeds.clear();
	}

	file.close();

	answer = (*(std::min_element(seeds.begin(), seeds.end()))).first;

	return 0;
}