#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Day 12 - Part 1
int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::vector<std::vector<int>> heightmap = std::vector<std::vector<int>>();
	int startx = 0, starty = 0;
	int endx = 0, endy = 0;
	int row = 0, col = 0;
	int minim = 0;
	while (std::getline(file, line)) {
		heightmap.push_back(std::vector<int>());
		for (col = 0; col < line.size(); ++col) {
			if (line[col] == 'S') {
				heightmap.back().push_back('a' - 'a');
				startx = row;
				starty = col;
			} else if (line[col] == 'E') {
				heightmap.back().push_back('z' - 'a');
				endx = row;
				endy = col;
			} else heightmap.back().push_back(line[col] - 'a');
		}
		++row;
	}

	file.close();

	std::vector<std::vector<int>> visited = heightmap;
	std::vector<std::vector<int>> steps = heightmap;
	for (row = 0; row < visited.size(); ++row) {
		for (col = 0; col < visited[row].size(); ++col) {
			visited[row][col] = 0;
			steps[row][col] = INT_MAX;
		}
	}

	row = startx;
	col = starty;
	steps[row][col] = 0;
	while (true) {
		if (row > 0) {
			if (!visited[row - 1][col]) {
				if (heightmap[row - 1][col] - heightmap[row][col] <= 1) {
					steps[row - 1][col] = std::min(steps[row - 1][col], steps[row][col] + 1);
				}
			}
		}

		if (row < heightmap.size() - 1) {
			if (!visited[row + 1][col]) {
				if (heightmap[row + 1][col] - heightmap[row][col] <= 1) {
					steps[row + 1][col] = std::min(steps[row + 1][col], steps[row][col] + 1);
				}
			}
		}

		if (col > 0) {
			if (!visited[row][col - 1]) {
				if (heightmap[row][col - 1] - heightmap[row][col] <= 1) {
					steps[row][col - 1] = std::min(steps[row][col - 1], steps[row][col] + 1);
				}
			}
		}

		if (col < heightmap[row].size() - 1) {
			if (!visited[row][col + 1]) {
				if (heightmap[row][col + 1] - heightmap[row][col] <= 1) {
					steps[row][col + 1] = std::min(steps[row][col + 1], steps[row][col] + 1);
				}
			}
		}
		visited[row][col] = 1;
		if (row == endx && col == endy) break;

		minim = INT_MAX;
		for (int r = 0; r < steps.size(); ++r) {
			for (int c = 0; c < steps[r].size(); ++c) {
				if (!visited[r][c]) {
					if (steps[r][c] < minim) {
						row = r;
						col = c;
						minim = steps[r][c];
					}
				}
			}
		}
	}

	answer = steps[endx][endy];

	return 0;
}