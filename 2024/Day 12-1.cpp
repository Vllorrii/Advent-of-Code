#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::vector<char>> map;
std::vector<std::vector<bool>> cov;
int drow[] = { 0, -1,  0, 1 };
int dcol[] = { 1,  0, -1, 0 };

void measure(char plot, size_t currrow, size_t currcol, long long* area, long long* perimeter) {
	long long perim = 4;
	size_t nextrow, nextcol;
	cov[currrow][currcol] = true;
	for (int dir = 0; dir < 4; ++dir) {
		nextrow = currrow + drow[dir];
		nextcol = currcol + dcol[dir];
		if (nextrow >= 0 && nextrow < map.size() && nextcol >= 0 && nextcol < map[0].size()) {
			if (map[nextrow][nextcol] == plot) {
				--perim;
				if (!cov[nextrow][nextcol]) measure(plot, nextrow, nextcol, area, perimeter);
			}
		}
	}

	*perimeter += perim;
	*area += 1;
}

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	while (std::getline(file, line)) {
		map.push_back(std::vector<char>());
		for (size_t i = 0; i < line.size(); ++i) map.back().push_back(line[i]);
	}
	cov = std::vector<std::vector<bool>>(map.size(), std::vector<bool>(map[0].size(), false));

	file.close();

	long long area, perimeter;
	for (size_t row = 0; row < map.size(); ++row) {
		for (size_t col = 0; col < map[0].size(); ++col) {
			if (cov[row][col]) continue;

			area = 0;
			perimeter = 0;
			measure(map[row][col], row, col, &area, &perimeter);
			answer += area * perimeter;
		}
	}

	return 0;
}