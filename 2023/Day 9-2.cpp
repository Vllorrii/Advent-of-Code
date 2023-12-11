#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define LENGTH 21

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line, instr;
	std::stringstream ssline;
	int histMat[LENGTH][LENGTH];
	int row, col;
	bool done;
	while (std::getline(file, line)) {
		ssline = std::stringstream(line);
		memset(histMat, 0, sizeof histMat);
		row = 0;
		col = 0;
		while (std::getline(ssline, line, ' ')) {
			histMat[row][col] = std::stoi(line);
			++col;
		}

		row = 1;
		while (row < LENGTH) {
			done = true;
			for (col = row; col < LENGTH; ++col) {
				histMat[row][col] = histMat[row - 1][col] - histMat[row - 1][col - 1];
				if (histMat[row][col] != 0) done = false;
			}
			if (done) break;
			++row;
		}

		for (row -= 1; row > 0; --row) {
			histMat[row][row - 1] = histMat[row][row] - histMat[row + 1][row];
		}
		answer += (histMat[0][0] - histMat[1][0]);
	}

	file.close();

	return 0;
}