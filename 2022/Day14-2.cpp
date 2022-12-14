#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

// Day 14 - Part 2
int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline, sscoord;
	std::vector<std::vector<std::pair<int, int>>> coords = std::vector<std::vector<std::pair<int, int>>>();
	int xmin = 500, xmax = 500, ymin = 0, ymax = 0;
	int x, y;
	int linen = 0;
	while (std::getline(file, line)) {
		coords.push_back(std::vector<std::pair<int, int>>());
		ssline = std::stringstream(line);
		while (std::getline(ssline, line, ' ')) {
			sscoord = std::stringstream(line);
			std::getline(sscoord, line, ',');
			x = std::stoi(line);
			std::getline(sscoord, line);
			y = std::stoi(line);
			xmin = std::min(xmin, x);
			xmax = std::max(xmax, x);
			ymin = std::min(ymin, y);
			ymax = std::max(ymax, y);
			coords[linen].push_back({ x, y });
			ssline.ignore(3);
		}
		++linen;
	}

	file.close();

	int offset = ymax;
	const int WIDTH = xmax - xmin + 1 + 2 * offset;
	const int HEIGHT = ymax - ymin + 2;
	const int SAND_X = 500 - xmin + offset;
	const int SAND_Y = 0;
	std::vector<std::vector<char>> cave = std::vector<std::vector<char>>(WIDTH, std::vector<char>(HEIGHT, '.'));
	for (int i = 0; i < coords.size(); ++i) {
		for (int j = 0; j < coords[i].size() - 1; ++j) {
			xmax = coords[i][j + 1].first - coords[i][j].first;
			xmax += (xmax > 0 ? 1 : -1);
			ymax = coords[i][j + 1].second - coords[i][j].second;
			ymax += (ymax > 0 ? 1 : -1);
			if (xmax != 0)
				for (x = 0; x != xmax; x += (xmax > 0 ? 1 : -1))
					cave[coords[i][j].first - xmin + offset + x][coords[i][j].second - ymin] = '#';

			if (ymax != 0)
				for (y = 0; y != ymax; y += (ymax > 0 ? 1 : -1))
					cave[coords[i][j].first - xmin + offset][coords[i][j].second - ymin + y] = '#';
		}
	}

	int sandx, sandy;
	while (true) {
		sandx = SAND_X;
		sandy = SAND_Y;
		while (true) {
			if (sandy + 1 >= cave[0].size()) {
				cave[sandx][sandy] = 'o';
				++answer;
				break;
			}
			if (cave[sandx][sandy + 1] == '.') ++sandy;
			else if (cave[sandx - 1][sandy + 1] == '.') {
				--sandx;
				++sandy;
			} else if (cave[sandx + 1][sandy + 1] == '.') {
				++sandx;
				++sandy;
			} else {
				cave[sandx][sandy] = 'o';
				++answer;
				break;
			}
		}

		if (sandx == SAND_X && sandy == SAND_Y) break;
	}

	return 0;
}