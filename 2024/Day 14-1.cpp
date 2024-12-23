#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#define WIDTH    101
#define HEIGHT   103
#define DURATION 100

inline size_t mod(long long a, long long b) {
	long long r = a % b;
	return r < 0 ? r + b : r;
}

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	long long pos[2], vel[2];
	int finalState[HEIGHT][WIDTH] = {};
	while (std::getline(file, line)) {
		sscanf_s(line.c_str(), "p=%lld,%lld v=%lld,%lld", &pos[1], &pos[0], &vel[1], &vel[0]);
		finalState[mod(pos[0] + vel[0] * DURATION, HEIGHT)][mod(pos[1] + vel[1] * DURATION, WIDTH)] += 1;
	}

	file.close();

	size_t middlerow = (size_t)std::floor((double)HEIGHT / 2.0);
	size_t middlecol = (size_t)std::floor((double)WIDTH / 2.0);
	size_t offsetrow = (size_t)std::ceil((double)HEIGHT / 2.0);
	size_t offsetcol = (size_t)std::ceil((double)WIDTH / 2.0);
	long long quads[4] = {};
	for (size_t row = 0; row < middlerow; ++row) {
		for (size_t col = 0; col < middlecol; ++col) {
			quads[0] += finalState[row][col];
			quads[1] += finalState[row][col + offsetcol];
			quads[2] += finalState[row + offsetrow][col];
			quads[3] += finalState[row + offsetrow][col + offsetcol];
		}
	}
	answer = quads[0] * quads[1] * quads[2] * quads[3];

	return 0;
}