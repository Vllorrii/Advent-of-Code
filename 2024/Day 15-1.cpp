#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define SIZE 50

void move(char map[SIZE][SIZE], int* currrow, int* currcol, char move) {
	int drow = 0, nextrow;
	int dcol = 0, nextcol;
	switch (move) {
	case '>': drow = 0; dcol = 1; break;
	case '^': drow = -1; dcol = 0; break;
	case '<': drow = 0; dcol = -1; break;
	case 'v': drow = 1; dcol = 0; break;
	}
	nextrow = *currrow + drow;
	nextcol = *currcol + dcol;

	if (map[nextrow][nextcol] == '#') return;
	if (map[nextrow][nextcol] == '.') {
		*currrow = nextrow;
		*currcol = nextcol;
		return;
	}

	int r = 0, c = 0;
	for (r = nextrow, c = nextcol; map[r][c] != '.' && map[r][c] != '#'; r += drow, c += dcol);
	if (map[r][c] == '#') return;
	map[r][c] = 'O';
	*currrow = nextrow;
	*currcol = nextcol;
	map[*currrow][*currcol] = '.';
}

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	char map[SIZE][SIZE], c;
	std::string moves;
	int row = 0, currrow = 0, currcol = 0;
	while (std::getline(file, line)) {
		if (line.empty()) break;
		for (size_t i = 0; i < line.size(); ++i) {
			map[row][i] = line[i];
			if (line[i] == '@') {
				currrow = row;
				currcol = i;
				map[row][i] = '.';
			}
		}
		++row;
	}
	while (std::getline(file, line)) moves.append(line);

	file.close();

	for (size_t i = 0; i < moves.size(); ++i) move(map, &currrow, &currcol, moves[i]);

	for (size_t row = 0; row < SIZE; ++row) {
		for (size_t col = 0; col < SIZE; ++col) {
			if (map[row][col] == 'O') {
				answer += 100ll * row + col;
			}
		}
	}

	file.close();

	return 0;
}