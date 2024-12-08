#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define SIZE 50

inline int freqIndex(char c) {
	return isdigit(c) ? c - '0' : (isupper(c) ? c - 'A' + 10 : c - 'a' + 36);
}

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::vector<std::pair<int, int>> antennas[62] = {};
	bool antinode[SIZE][SIZE] = {};
	size_t row = 0, col;
	while (std::getline(file, line)) {
		for (col = 0; col < line.size(); ++col) {
			if (line[col] != '.') antennas[freqIndex(line[col])].push_back({ row, col });
		}
		++row;
	}

	file.close();

	for (size_t n = 0; n < 62; ++n) {
		for (size_t i = 0; i < antennas[n].size(); ++i) {
			for (size_t j = i + 1; j < antennas[n].size(); ++j) {
				for (row = antennas[n][i].first, col = antennas[n][i].second;
					row >= 0 && row < SIZE && col >= 0 && col < SIZE;
					row += antennas[n][i].first - antennas[n][j].first,
					col += antennas[n][i].second - antennas[n][j].second) {
					antinode[row][col] = true;
				}
				for (row = antennas[n][i].first, col = antennas[n][i].second;
					row >= 0 && row < SIZE && col >= 0 && col < SIZE;
					row -= antennas[n][i].first - antennas[n][j].first,
					col -= antennas[n][i].second - antennas[n][j].second) {
					antinode[row][col] = true;
				}
			}
		}
	}

	for (row = 0; row < SIZE; ++row) {
		for (col = 0; col < SIZE; ++col) {
			if (antinode[row][col]) ++answer;
		}
	}

	return 0;
}