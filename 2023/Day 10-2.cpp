#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define SIZE 140

enum Side {
	NORTH, EAST, SOUTH, WEST, ERROR
};

Side dir(int dx, int dy) {
	if (dx ==  0 && dy ==  1) return SOUTH;
	if (dx ==  0 && dy == -1) return NORTH;
	if (dx ==  1 && dy ==  0) return EAST;
	if (dx == -1 && dy ==  0) return WEST;
	return ERROR;
}

int dx(Side side) {
	if (side == EAST) return 1;
	if (side == WEST) return -1;
	return 0;
}

int dy(Side side) {
	if (side == SOUTH) return 1;
	if (side == NORTH) return -1;
	return 0;
}

bool testExit(char type, Side exit) {
	if (type == '.') return false;
	switch (exit) {
	case NORTH: return type == '|' || type == 'J' || type == 'L';
	case EAST:  return type == '-' || type == 'F' || type == 'L';
	case SOUTH: return type == '|' || type == 'F' || type == '7';
	case WEST:  return type == '-' || type == 'J' || type == '7';
	}
	return false;
}

Side nextExit(char type, Side entry) {
	switch (type) {
	case '|': return entry == NORTH ? SOUTH : NORTH;
	case '-': return entry == WEST  ? EAST  : WEST;
	case 'L': return entry == NORTH ? EAST  : NORTH;
	case 'J': return entry == NORTH ? WEST  : NORTH;
	case '7': return entry == WEST  ? SOUTH : WEST;
	case 'F': return entry == EAST  ? SOUTH : EAST;
	}
	return ERROR;
}

unsigned char colorInOut(unsigned char c, unsigned char top) {
	switch (top) {
	case 0:
	case '|':
	case ('-' + 0x80):
	case 'L':
	case ('J' + 0x80):
	case ('7' + 0x80):
	case 'F':
		return c;
	case 0x80:
	case ('|' + 0x80):
	case '-':
	case ('L' + 0x80):
	case 'J':
	case '7':
	case ('F' + 0x80):
		return c + 0x80;
	}
	return c;
}

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line, instr;
	std::stringstream ssline;
	char network[SIZE][SIZE] = {};
	char inout[SIZE][SIZE] = {};
	int linen = 0;
	int startrow = 0, startcol = 0;
	while (std::getline(file, line)) {
		for (int i = 0; i < SIZE; ++i) {
			network[linen][i] = line[i];
			if (line[i] == 'S') {
				startrow = linen; startcol = i;
			}
		}
		++linen;
	}

	file.close();

	inout[startrow][startcol] = 'L';
	// Test each surrounding pipe for connections to the starting pipe
	int testrow, testcol;
	bool exittests[ERROR] = {};
	for (int i = 0; i < ERROR; ++i) {
		testcol = startcol + dx(Side(i));
		testrow = startrow + dy(Side(i));
		if (testcol >= 0 && testcol < SIZE && testrow >= 0 && testrow < SIZE) {
			if (testExit(network[testrow][testcol], dir(-dx(Side(i)), -dy(Side(i))))) {
				exittests[i] = true;
			}
		}
	}

	// Label the starting pipe correctly
	int currrow1, currrow2, currcol1, currcol2;
	Side side1, side2;
	if (exittests[NORTH]) {
		currrow1 = startrow - 1;
		currcol1 = startcol;
		side1 = SOUTH;
		if (exittests[SOUTH]) {
			network[startrow][startcol] = '|';
			currrow2 = startrow + 1;
			currcol2 = startcol;
			side2 = NORTH;
		} else if (exittests[EAST]) {
			network[startrow][startcol] = 'L';
			currrow2 = startrow;
			currcol2 = startcol + 1;
			side2 = WEST;
		} else {
			network[startrow][startcol] = 'J';
			currrow2 = startrow;
			currcol2 = startcol - 1;
			side2 = EAST;
		}
	} else if (exittests[EAST]) {
		currrow1 = startrow;
		currcol1 = startcol + 1;
		side1 = WEST;
		if (exittests[SOUTH]) {
			network[startrow][startcol] = 'F';
			currrow2 = startrow + 1;
			currcol2 = startcol;
			side2 = NORTH;
		} else {
			network[startrow][startcol] = '-';
			currrow2 = startrow;
			currcol2 = startcol - 1;
			side2 = EAST;
		}
	} else {
		network[startrow][startcol] = '7';
		currrow1 = startrow;
		currcol1 = startcol - 1;
		side1 = EAST;
		currrow2 = startrow + 1;
		currcol2 = startcol;
		side2 = NORTH;
	}

	inout[currrow1][currcol1] = network[currrow1][currcol1];
	inout[currrow2][currcol2] = network[currrow2][currcol2];
	while (!(currrow1 == currrow2 && currcol1 == currcol2)) {
		side1 = nextExit(network[currrow1][currcol1], side1);
		side2 = nextExit(network[currrow2][currcol2], side2);
		currcol1 += dx(side1);
		currrow1 += dy(side1);
		currcol2 += dx(side2);
		currrow2 += dy(side2);
		side1 = Side(((int)side1 + 2) % (int)ERROR);
		side2 = Side(((int)side2 + 2) % (int)ERROR);
		inout[currrow1][currcol1] = network[currrow1][currcol1];
		inout[currrow2][currcol2] = network[currrow2][currcol2];
	}

	int pipecount;
	for (int row = 0; row < SIZE; ++row) {
		pipecount = 0;
		for (int col = 0; col < SIZE; ++col) {
			switch (inout[row][col]) {
			case '|':
			case 'L':
			case 'J':
				++pipecount;
				break;
			case 0:
				if (pipecount % 2 == 1) {
					inout[row][col] = 'I';
					++answer;
				}
			}
		}
	}

	return 0;
}