#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> map = std::vector<std::vector<int>>();
std::vector<std::vector<bool>> peaks = std::vector<std::vector<bool>>();
int drow[4] = { 0, 1,  0, -1};
int dcol[4] = { 1, 0, -1,  0 };

int score(int currrow, int currcol) {
	int result = 0, nextrow, nextcol;
	for (int dir = 0; dir < 4; ++dir) {
		nextrow = currrow + drow[dir];
		nextcol = currcol + dcol[dir];
		if (nextrow >= 0 && nextrow < map.size()
			&& nextcol >= 0 && nextcol < map[0].size()) {
			if (map[nextrow][nextcol] == map[currrow][currcol] + 1) {
				if (map[nextrow][nextcol] == 9) {
					if (!peaks[nextrow][nextcol]) {
						peaks[nextrow][nextcol] = true;
						++result;
					}
				} else {
					result += score(nextrow, nextcol);
				}
			}
		}
	}
	return result;
}

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	while (std::getline(file, line)) {
		map.push_back(std::vector<int>());
		for (size_t i = 0; i < line.size(); ++i) map.back().push_back(line[i] - '0');
	}

	file.close();

	for (int row = 0; row < map.size(); ++row) {
		for (int col = 0; col < map[0].size(); ++col) {
			if (map[row][col] == 0) {
				peaks = std::vector<std::vector<bool>>(map.size(), std::vector<bool>(map[0].size(), false));
				answer += score(row, col);
			}
		}
	}

	return 0;
}