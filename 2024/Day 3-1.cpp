#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

int main() {
	long long answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	long long a, b;
	while (std::getline(file, line)) {
		for (size_t pos = 0; pos < line.size(); ++pos) {
			if (line[pos] != 'm') continue;
			if (line.substr(pos, 4) != "mul(") continue;
			pos += 3;

			a = 0ll;
			b = 0ll;
			while (++pos < line.size()) {
				if (isdigit(line[pos])) {
					a *= 10ll;
					a += (long long)(line[pos] - '0');
				} else break;
			}
			if (line[pos] != ',') continue;
			while (++pos < line.size()) {
				if (isdigit(line[pos])) {
					b *= 10;
					b += (long long)(line[pos] - '0');
				} else break;
			}
			if (line[pos] != ')') continue;
			answer += a * b;
		}
	}
	
	file.close();

	return 0;
}