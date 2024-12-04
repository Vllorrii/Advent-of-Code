#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#define SIZE 140

int dirs[2][8] = {
	{ 1, 1, 0, -1, -1, -1,  0,  1},
	{ 0, 1, 1,  1,  0, -1, -1, -1}
};
const char* word = "XMAS";

int main() {
	long long answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	char matrix[SIZE][SIZE] = {};
	int i = 0;
	while (std::getline(file, line)) {
		memcpy(matrix[i++], line.c_str(), line.size());
	}
	
	file.close();

	for (size_t row = 0; row < SIZE; ++row) {
		for (size_t col = 0; col < SIZE; ++col) {
			if (matrix[row][col] == word[0]) {
				for (int dir = 0; dir < 8; ++dir) {
					if (row + 3 * dirs[1][dir] >= 0 && row + 3 * dirs[1][dir] < SIZE
						&& col + 3 * dirs[0][dir] >= 0 && col + 3 * dirs[0][dir] < SIZE) {
						for (i = 0; i < strlen(word); ++i) {
							if (matrix[row + i * dirs[1][dir]][col + i * dirs[0][dir]] != word[i]) {
								break;
							}
						}
						if (i == strlen(word)) ++answer;
					}
				}
			}
		}
	}

	return 0;
}