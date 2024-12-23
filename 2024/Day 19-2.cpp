#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>

size_t maxlen = 0;
std::unordered_set<std::string> towels;

long long towelpartition(std::string pattern, size_t off, std::vector<long long>& memory) {
	long long result = 0ll, subpar;
	if (off == pattern.size()) return 1;
	for (int len = std::min(maxlen, pattern.size() - off); len >= 1; --len) {
		if (towels.find(pattern.substr(off, (size_t)len)) != towels.end()) {
			if (memory[off + len] != -1ll) {
				result += memory[off + len];
				continue;
			}
			subpar = towelpartition(pattern, off + len, memory);
			memory[off + len] = subpar;
			result += subpar;
		}
	}
	return result;
}

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	std::vector<long long> memory;
	std::getline(file, line);
	ssline = std::stringstream(line);
	while (std::getline(ssline, line, ',')) {
		towels.insert(line);
		ssline.ignore();
		maxlen = std::max(maxlen, line.size());
	}
	std::getline(file, line);
	while (std::getline(file, line)) {
		memory = std::vector<long long>(line.size() + 1, -1ll);
		answer += towelpartition(line, 0, memory);
	}

	file.close();

	return 0;
}