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
	std::vector<int> program;
	for (int i = 0; i < 4; ++i) std::getline(file, line);
	std::getline(file, line);
	ssline = std::stringstream(line);
	ssline.ignore(9);
	while (std::getline(ssline, line, ',')) program.push_back(line[0] - '0');

	file.close();

	std::vector<long long> a, anew;
	long long n, shift, atest;
	for (long long astart = 0ll; ; ++astart) {
		a = std::vector<long long>(1, astart);
		anew.clear();
		for (int d = program.size() - 1; d >= 0; --d) {
			n = program[d];
			for (int i = 0; i < a.size(); ++i) {
				for (int b = 0; b < 8; ++b) {
					shift = b ^ 2;
					atest = (a[i] << 3) + b;
					if (((shift ^ ((atest >> shift) % 8)) ^ 7) == n) {
						anew.push_back(atest);
					}
				}
			}
			a = anew;
			if (a.size() == 0) break;
			anew.clear();
		}
		if (a.size() != 0) break;
	}

	answer = *std::min_element(a.begin(), a.end());

	return 0;
}