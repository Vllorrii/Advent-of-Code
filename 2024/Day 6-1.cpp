#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#define SIZE 130

int drow[4] = { -1, 0, 1,  0 };
int dcol[4] = { 0, 1, 0, -1 };

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	char map[SIZE][SIZE] = {};
	size_t row = 0, currrow = 0, currcol = 0;
	while (std::getline(file, line)) {
		for (size_t col = 0; col < line.size(); ++col) {
			map[row][col] = line[col];
			if (map[row][col] == '^') {
				currrow = row;
				currcol = col;
			}
		}
		++row;
	}

	file.close();

	int dir = 0;
	while (currrow >= 0 && currrow < SIZE
		&& currcol >= 0 && currcol < SIZE) {
		if (map[currrow][currcol] == '#') {
			currrow -= drow[dir];
			currcol -= dcol[dir];
			dir = (dir + 1) % 4;
		}
		map[currrow][currcol] = 'X';
		currrow += drow[dir];
		currcol += dcol[dir];
	}

	for (size_t row = 0; row < SIZE; ++row) {
		for (size_t col = 0; col < SIZE; ++col) {
			if (map[row][col] == 'X') ++answer;
		}
	}

	return 0;
}