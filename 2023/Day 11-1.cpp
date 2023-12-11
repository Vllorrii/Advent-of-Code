#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line, instr;
	std::stringstream ssline;
	std::vector<std::string> universe = std::vector<std::string>();
	std::vector<std::pair<int, int>> galaxies;
	std::vector<bool> emptyrows, emptycols;
	int row = 0, col;

	std::getline(file, line);
	emptycols = std::vector<bool>(line.size(), true);
	do {
		universe.push_back(line);
		emptyrows.push_back(true);
		for (col = 0; col < line.size(); ++col) {
			if (line[col] == '#') {
				galaxies.push_back({ row, col });
				emptyrows[row] = false;
				emptycols[col] = false;
			}
		}
		++row;
	} while (std::getline(file, line));

	file.close();

	int addrows, addcols;
	for (int i = 0; i < galaxies.size(); ++i) {
		for (int j = i + 1; j < galaxies.size(); ++j) {
			addrows = 0;
			addcols = 0;
			for (int rowpath = std::min(galaxies[i].first, galaxies[j].first) + 1;
				rowpath < std::max(galaxies[i].first, galaxies[j].first); ++rowpath) {
				if (emptyrows[rowpath]) ++addrows;
			}
			for (int colpath = std::min(galaxies[i].second, galaxies[j].second) + 1;
				colpath < std::max(galaxies[i].second, galaxies[j].second); ++colpath) {
				if (emptycols[colpath]) ++addcols;
			}
			answer += std::abs(galaxies[i].first - galaxies[j].first)
				+ std::abs(galaxies[i].second - galaxies[j].second)
				+ addrows + addcols;
		}
	}

	return 0;
}