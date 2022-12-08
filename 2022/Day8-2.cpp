#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Day 8 - Part 2
int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::vector<std::vector<int>> grid = std::vector<std::vector<int>>();
	int row = 0, col = 0;
	while (std::getline(file, line)) {
		grid.push_back(std::vector<int>());
		for (col = 0; col < line.size(); ++col) {
			grid[row].push_back(line[col] - '0');
		}
		++row;
	}

	file.close();

	int l, r, u, d;
	for (row = 1; row < grid.size() - 1; ++row) {
		for (col = 1; col < grid[0].size() - 1; ++col) {
			for (u = 1; row - u > 0; ++u)
				if (grid[row - u][col] >= grid[row][col]) break;
			for (d = 1; row + d < grid.size() - 1; ++d)
				if (grid[row + d][col] >= grid[row][col]) break;
			for (l = 1; col - l > 0; ++l)
				if (grid[row][col - l] >= grid[row][col]) break;
			for (r = 1; col + r < grid[0].size() - 1; ++r)
				if (grid[row][col + r] >= grid[row][col]) break;

			answer = std::max(answer, l * r * u * d);
		}
	}

	return 0;
}