#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>

size_t maxlen = 0;
std::unordered_set<std::string> towels;

bool towelpartition(std::string pattern, size_t off, std::vector<bool>& blacklist) {
	if (off == pattern.size()) return true;
	for (int len = std::min(maxlen, pattern.size() - off); len >= 1; --len) {
		if (blacklist[off + len]) continue;
		if (towels.find(pattern.substr(off, (size_t)len)) != towels.end()) {
			if (towelpartition(pattern, off + len, blacklist)) return true;
			else blacklist[off + len] = true;
		}
	}
	return false;
}

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	std::vector<bool> blacklist;
	std::getline(file, line);
	ssline = std::stringstream(line);
	while (std::getline(ssline, line, ',')) {
		towels.insert(line);
		ssline.ignore();
		maxlen = std::max(maxlen, line.size());
	}
	std::getline(file, line);
	while (std::getline(file, line)) {
		blacklist = std::vector<bool>(line.size() + 1, false);
		if (towelpartition(line, 0, blacklist)) ++answer;
	}

	file.close();

	return 0;
}