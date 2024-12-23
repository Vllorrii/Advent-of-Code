#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <set>

#define SIZE 50

bool canmoveup(char map[SIZE][2 * SIZE], int currrow, std::set<int> currcol, int drow) {
	std::set<int> nextcol;
	for (std::set<int>::iterator it = currcol.begin(); it != currcol.end(); ++it) {
		if (map[currrow + drow][*it] == '#') return false;
		if (map[currrow + drow][*it] == '[') {
			nextcol.insert(*it);
			nextcol.insert((*it) + 1);
		}
		if (map[currrow + drow][*it] == ']') {
			nextcol.insert(*it);
			nextcol.insert((*it) - 1);
		}
	}

	if (nextcol.size() != 0) if (!canmoveup(map, currrow + drow, nextcol, drow)) return false;	

	for (std::set<int>::iterator it = currcol.begin(); it != currcol.end(); ++it) {
		map[currrow + drow][*it] = map[currrow][*it];
		map[currrow][*it] = '.';
	}
	return true;
}

void moveside(char map[SIZE][2 * SIZE], int* currrow, int* currcol, int dcol) {
	int c;
	for (c = *currcol + dcol; map[*currrow][c] != '.' && map[*currrow][c] != '#'; c += dcol);
	if (map[*currrow][c] == '#') return;
	for (; c != *currcol; c -= dcol) map[*currrow][c] = map[*currrow][c - dcol];
	*currcol += dcol;
	map[*currrow][*currcol] = '.';
}

void move(char map[SIZE][2 * SIZE], int* currrow, int* currcol, char move) {
	int drow = 0, dcol = 0;

	switch (move) {
	case '>': drow = 0;  dcol = 1; break;
	case '^': drow = -1; dcol = 0; break;
	case '<': drow = 0;  dcol = -1; break;
	case 'v': drow = 1;  dcol = 0; break;
	}

	if (dcol == 0) {
		if (canmoveup(map, *currrow, std::set<int>({ *currcol }), drow)) *currrow += drow;
	} else moveside(map, currrow, currcol, dcol);
}

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	char map[SIZE][SIZE * 2], c1, c2;
	std::string moves;
	int row = 0, currrow = 0, currcol = 0;
	while (std::getline(file, line)) {
		if (line.empty()) break;
		for (size_t i = 0; i < line.size(); ++i) {
			switch (line[i]) {
			case '#': c1 = '#'; c2 = '#'; break;
			case 'O': c1 = '['; c2 = ']'; break;
			case '@':
				currrow = row;
				currcol = 2 * i;
			case '.':
				c1 = '.'; c2 = '.'; break;
			}
			map[row][2 * i] = c1;
			map[row][2 * i + 1] = c2;
		}
		++row;
	}
	while (std::getline(file, line)) moves.append(line);

	file.close();

	for (size_t i = 0; i < moves.size(); ++i) move(map, &currrow, &currcol, moves[i]);

	for (size_t row = 0; row < SIZE; ++row) {
		for (size_t col = 0; col < 2 * SIZE; ++col) {
			if (map[row][col] == '[') {
				answer += 100ll * row + col;
			}
		}
	}

	file.close();

	return 0;
}