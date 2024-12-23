#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

inline long long determinant(long long matrix[2][2]) {
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	long long matrix[2][2] = {};
	long long coords[2] = {};
	long long det, a, b;
	while (std::getline(file, line)) {
		sscanf_s(line.c_str(), "Button A: X+%lld, Y+%lld", &matrix[0][0], &matrix[1][0]);
		std::getline(file, line);
		sscanf_s(line.c_str(), "Button B: X+%lld, Y+%lld", &matrix[0][1], &matrix[1][1]);
		std::getline(file, line);
		sscanf_s(line.c_str(), "Prize: X=%lld, Y=%lld", &coords[0], &coords[1]);
		std::getline(file, line);

		if ((det = determinant(matrix)) != 0) {
			a = matrix[1][1] * coords[0] - matrix[0][1] * coords[1];
			b = matrix[0][0] * coords[1] - matrix[1][0] * coords[0];

			if (a % det == 0 && b % det == 0) answer += 3 * a / det + b / det;
		}
	}

	file.close();

	return 0;
}