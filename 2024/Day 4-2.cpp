#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#define SIZE 140

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

	for (size_t row = 1; row < SIZE - 1; ++row) {
		for (size_t col = 1; col < SIZE - 1; ++col) {
			if (matrix[row][col] == 'A') {
				if ((
						(matrix[row + 1][col + 1] == 'M' && matrix[row - 1][col - 1] == 'S')
						|| (matrix[row - 1][col - 1] == 'M' && matrix[row + 1][col + 1] == 'S')
					) && (
						(matrix[row + 1][col - 1] == 'M' && matrix[row - 1][col + 1] == 'S')
						|| (matrix[row - 1][col + 1] == 'M' && matrix[row + 1][col - 1] == 'S')
					)) ++answer;
			}
		}
	}

	return 0;
}