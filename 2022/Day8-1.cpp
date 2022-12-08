#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Day 8 - Part 1
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

	std::vector<std::vector<int>> grid_heighest_l2r = grid;
	std::vector<std::vector<int>> grid_heighest_r2l = grid;
	std::vector<std::vector<int>> grid_heighest_u2d = grid;
	std::vector<std::vector<int>> grid_heighest_d2u = grid;
	int num_rows = grid.size();
	int num_cols = grid[0].size();
	answer = num_rows * num_cols;
	int num_diags = num_rows + num_cols - 1;
	for (int diag = 0; diag < num_diags; ++diag) {
		for (int n = 0; n <= std::min(diag, num_diags - diag - 1); ++n) {
			row = std::min(diag, num_rows - 1) - n;
			col = std::max(0, diag - num_rows + 1) + n;

			if (row > 0 && row < num_rows - 1)
				if (grid[row][col] < grid_heighest_u2d[row - 1][col]) grid_heighest_u2d[row][col] = grid_heighest_u2d[row - 1][col];
			if (col > 0 && col < num_cols - 1)
				if (grid[row][col] < grid_heighest_l2r[row][col - 1]) grid_heighest_l2r[row][col] = grid_heighest_l2r[row][col - 1];
		}
	}

	bool visible = false;
	for (int diag = num_diags - 1; diag >= 0; --diag) {
		for (int n = 0; n <= std::min(diag, num_diags - diag - 1); ++n) {
			row = std::min(diag, num_rows - 1) - n;
			col = std::max(0, diag - num_rows + 1) + n;

			if (row == 0) {
				visible = false;
			}

			if (row > 0 && row < num_rows - 1)
				if (grid[row][col] < grid_heighest_d2u[row + 1][col]) grid_heighest_d2u[row][col] = grid_heighest_d2u[row + 1][col];
			if (col > 0 && col < num_cols - 1)
				if (grid[row][col] < grid_heighest_r2l[row][col + 1]) grid_heighest_r2l[row][col] = grid_heighest_r2l[row][col + 1];
			
			visible = false;
			if (row == 0 || row == num_rows - 1 || col == 0 || col == num_cols - 1) visible = true;
			if (row > 0)
				if (grid[row][col] > grid_heighest_u2d[row - 1][col]) visible = true;
			if (row < num_rows - 1)
				if (grid[row][col] > grid_heighest_d2u[row + 1][col]) visible = true;
			if (col > 0)
				if (grid[row][col] > grid_heighest_l2r[row][col - 1]) visible = true;
			if (col < num_cols - 1)
				if (grid[row][col] > grid_heighest_r2l[row][col + 1]) visible = true;
			if (!visible) {
				--answer;
			}
		}
	}

	return 0;
}