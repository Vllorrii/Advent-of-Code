#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define WIDTH    101
#define HEIGHT   103

int drow[9] = { -1, -1, -1,  0, 0, 0,  1, 1, 1 };
int dcol[9] = { -1,  0,  1, -1, 0, 1, -1, 0, 1 };

typedef struct {
	long long pos[2];
	long long vel[2];
} Robot;

inline size_t mod(long long a, long long b) {
	long long r = a % b;
	return r < 0 ? r + b : r;
}

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::vector<Robot> robots;
	int state[HEIGHT][WIDTH] = {};
	while (std::getline(file, line)) {
		Robot robot = {};
		sscanf_s(line.c_str(), "p=%lld,%lld v=%lld,%lld", &robot.pos[1], &robot.pos[0], &robot.vel[1], &robot.vel[0]);
		robots.push_back(robot);
		state[robot.pos[0]][robot.pos[1]] += 1;
	}

	file.close();

	size_t score, maxscore = 0, checkrow, checkcol;
	char c;
	for (size_t t = 0ll; ; ++t) {
		score = 0;
		for (size_t r = 0; r < robots.size(); ++r) {
			for (int dir = 0; dir < 9; ++dir) {
				checkrow = robots[r].pos[0] + drow[dir];
				checkcol = robots[r].pos[1] + dcol[dir];
				if (checkrow >= 0 && checkrow < HEIGHT && checkcol >= 0 && checkcol < WIDTH) {
					score += state[checkrow][checkcol];
				}
			}
			score--;
		}

		if (score > maxscore) {
			maxscore = score;
			for (size_t row = 0; row < HEIGHT; ++row) {
				for (size_t col = 0; col < WIDTH; ++col) {
					if (state[row][col] > 0) std::cout << state[row][col];
					else std::cout << '.';
				}
				std::cout << std::endl;
			}
			std::cout << "Christmas tree? ";
			std::cin >> c;
			if (c == 'y') {
				answer = t;
				break;
			}
		}

		memset(state, 0, sizeof(state));
		for (size_t r = 0; r < robots.size(); ++r) {
			robots[r].pos[0] = mod(robots[r].pos[0] + robots[r].vel[0], HEIGHT);
			robots[r].pos[1] = mod(robots[r].pos[1] + robots[r].vel[1], WIDTH);
			state[robots[r].pos[0]][robots[r].pos[1]] += 1;
		}
	}

	return 0;
}