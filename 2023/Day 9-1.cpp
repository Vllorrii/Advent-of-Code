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
			for (col = 0; col < LENGTH - row; ++col) {
				histMat[row][col] = histMat[row - 1][col + 1] - histMat[row - 1][col];
				if (histMat[row][col] != 0) done = false;
			}
			if (done) break;
			++row;
		}

		for (row -= 1; row > 0; --row) {
			histMat[row][LENGTH - row] = histMat[row][LENGTH - row - 1] + histMat[row + 1][LENGTH - row - 1];
		}
		answer += (histMat[0][LENGTH - 1] + histMat[1][LENGTH - 1]);
	}

	file.close();

	return 0;
}