#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

const int NUM_KNOTS = 2; // Part 1
// const int NUM_KNOTS = 10; // Part 2

struct Point {
	int x;
	int y;

	Point operator+(Point b) {
		return { x + b.x, y + b.y };
	}
};

bool point_sort(Point const& a, Point const& b) {
	if (a.x == b.x) return a.y < b.y;
	return a.x < b.x;
}

bool point_equal(Point const& a, Point const& b) {
	return a.x == b.x && a.y == b.y;
}

void move_knot(Point* head, Point* tail) {
	int dirx = head->x - tail->x;
	int diry = head->y - tail->y;
	int dx = (dirx > 0) ? 1 : -1;
	int dy = (diry > 0) ? 1 : -1;
	if (std::abs(dirx * diry) >= 2) {
		tail->x += dx;
		tail->y += dy;
	} else if (dirx == 0 && std::abs(diry) == 2) {
		tail->y += dy;
	} else if (diry == 0 && std::abs(dirx) == 2) {
		tail->x += dx;
	}
}

// Day 9 - Part 1 and 2
int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	Point instruction = {};
	std::vector<Point> knots = std::vector<Point>(NUM_KNOTS, { 0, 0 });
	std::vector<Point> tailpos = std::vector<Point>();
	while (std::getline(file, line)) {
		for (int step = 0; step < std::stoi(line.substr(2)); ++step) {
			if (line[0] == 'R')	knots[0].x += 1;
			if (line[0] == 'L')	knots[0].x -= 1;
			if (line[0] == 'U')	knots[0].y += 1;
			if (line[0] == 'D')	knots[0].y -= 1;
			for (std::vector<Point>::iterator it = knots.begin() + 1; it < knots.end(); ++it)
				move_knot((it - 1)._Ptr, it._Ptr);
			tailpos.push_back(knots.back());
		}
	}

	file.close();

	std::sort(tailpos.begin(), tailpos.end(), &point_sort);
	std::vector<Point>::iterator it = std::unique(tailpos.begin(), tailpos.end(), &point_equal);
	tailpos.erase(it, tailpos.end());

	answer = tailpos.size();

	return 0;
}