#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>

#define SIZE 8

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
	*currrow = nextrow;
	*currcol = nextcol;
	if (map[nextrow][nextcol] == '.') return;

	int r = 0, c = 0;
	for (r = nextrow, c = nextcol; r < 0 || r >= SIZE || c < 0 || c >= SIZE; r += drow, c += dcol) {
		if (map[r][c] == '.') break;
	}
	if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) return;
	map[r][c] == 'O';
	map[*currrow][*currcol] = '.';
}

int main() {
	int pause;
	long long answer = 0ll;

	std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

	std::ifstream file("D:\\Documents\\AdventOfCode\\input_test.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	char map[SIZE][SIZE], c;
	std::vector<char> moves;
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
	while ((c = file.get()) != EOF) moves.push_back(c);

	file.close();

	for (size_t i = 0; i < moves.size(); ++i) move(map, &currrow, &currcol, moves[i]);

	for (size_t row = 0; row < SIZE; ++row) {
		for (size_t col = 0; col < SIZE; ++col) {
			if (map[row][col] == 'O') {
				answer += 100ll * row + col;
			}
		}
	}

end:
	std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

	std::cout << "Answer: " << answer << std::endl;
	std::cout << "Compute: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << "ms" << std::endl;
	std::cin >> pause;
	return 0;
}