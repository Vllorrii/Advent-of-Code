#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#define SIZE 130

int drow[4] = { -1, 0, 1,  0 };
int dcol[4] = {  0, 1, 0, -1 };

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	char map[SIZE][SIZE] = {};
	size_t row = 0, startrow = 0, startcol = 0;
	while (std::getline(file, line)) {
		for (size_t col = 0; col < line.size(); ++col) {
			map[row][col] = line[col];
			if (map[row][col] == '^') {
				startrow = row;
				startcol = col;
			}
		}
		++row;
	}

	file.close();

	int dir;
	char newmap[SIZE][SIZE];
	bool dirsvis[SIZE][SIZE][4] = {};
	size_t currrow, currcol;
	bool loops;
	for (size_t row = 0; row < SIZE; ++row) {
		for (size_t col = 0; col < SIZE; ++col) {
			if (map[row][col] != '.') continue;

			memcpy(newmap, map, SIZE * SIZE);
			memset(dirsvis, 0, SIZE * SIZE * 4 * sizeof(dirsvis[0][0][0]));
			newmap[row][col] = '#';
			currrow = startrow;
			currcol = startcol;
			loops = false;
			dir = 0;

			dirsvis[currrow][currcol][dir] = true;
			currrow += drow[dir];
			currcol += dcol[dir];
			while (currrow >= 0 && currrow < SIZE
				&& currcol >= 0 && currcol < SIZE) {
				if (newmap[currrow][currcol] == '#') {
					currrow -= drow[dir];
					currcol -= dcol[dir];
					dirsvis[currrow][currcol][dir] = true;
					dir = (dir + 1) % 4;
				} else if (dirsvis[currrow][currcol][dir]) {
					loops = true;
					break;
				}
				dirsvis[currrow][currcol][dir] = true;
				currrow += drow[dir];
				currcol += dcol[dir];
			}

			if (loops) ++answer;
		}
	}

	return 0;
}