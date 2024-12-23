#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Side {
	bool cov[4];
	Side() : cov() {}
};
std::vector<std::vector<char>> map;
std::vector<std::vector<bool>> cov;
std::vector<std::vector<Side>> sidecov;
int drow[] = { 0, -1,  0, 1 };
int dcol[] = { 1,  0, -1, 0 };

void measure(char plot, size_t currrow, size_t currcol, long long* area, long long* sides) {
	size_t nextrow, nextcol;
	cov[currrow][currcol] = true;
	bool newside;

	for (int dir = 0; dir < 4; ++dir) {
		nextrow = currrow + drow[dir];
		nextcol = currcol + dcol[dir];
		newside = false;
		// Border with other perk
		if (nextrow >= 0 && nextrow < map.size() && nextcol >= 0 && nextcol < map[0].size()) {
			if (map[nextrow][nextcol] != plot && !sidecov[currrow][currcol].cov[dir]) newside = true;
		}
		// Border with map edge
		else if (!sidecov[currrow][currcol].cov[dir]) newside = true;

		if (newside) {
			sidecov[currrow][currcol].cov[dir] = true;
			*sides += 1;

			for (int i = 1; i < 4; i += 2) {
				nextrow = currrow + drow[(dir + i) % 4];
				nextcol = currcol + dcol[(dir + i) % 4];
				while (nextrow >= 0 && nextrow < map.size() && nextcol >= 0 && nextcol < map[0].size()) {
					if (map[nextrow][nextcol] != plot) break;
					if (nextrow + drow[dir] >= 0 && nextrow + drow[dir] < map.size()
						&& nextcol + dcol[dir] >= 0 && nextcol + dcol[dir] < map[0].size()) {
						if (map[nextrow + drow[dir]][nextcol + dcol[dir]] == plot) break;
					}

					sidecov[nextrow][nextcol].cov[dir] = sidecov[currrow][currcol].cov[dir];
					sidecov[nextrow][nextcol].cov[dir] = sidecov[currrow][currcol].cov[dir];

					nextrow += drow[(dir + i) % 4];
					nextcol += dcol[(dir + i) % 4];
				}
			}
		}
	}

	for (int dir = 0; dir < 4; ++dir) {
		nextrow = currrow + drow[dir];
		nextcol = currcol + dcol[dir];
		if (nextrow >= 0 && nextrow < map.size() && nextcol >= 0 && nextcol < map[0].size()) {
			if (map[nextrow][nextcol] == plot) {
				if (!cov[nextrow][nextcol]) {
					measure(plot, nextrow, nextcol, area, sides);
				}
			}
		}
	}

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
	sidecov = std::vector<std::vector<Side>>(map.size(), std::vector<Side>(map[0].size(), Side()));

	file.close();

	long long area, sides;
	for (size_t row = 0; row < map.size(); ++row) {
		for (size_t col = 0; col < map[0].size(); ++col) {
			if (cov[row][col]) continue;

			area = 0;
			sides = 0;
			measure(map[row][col], row, col, &area, &sides);
			answer += area * sides;
		}
	}

	return 0;
}