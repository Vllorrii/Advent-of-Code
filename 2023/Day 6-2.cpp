#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
	long long answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;

	long long time, dist, tmin, tmax;
	file.ignore(5);
	std::getline(file, line);
	line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
	time = std::stoll(line);
	file.ignore(9);
	std::getline(file, line);
	line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
	dist = std::stoll(line);

	file.close();

	tmin = (long long)floorl(0.5l * time - 0.5l * sqrtl((long double)time * time - 4.0l * dist)) + 1l;
	tmax = (long long)ceill(0.5l * time + 0.5l * sqrtl((long double)time * time - 4.0l * dist)) - 1l;
	answer = (tmax - tmin + 1);

	return 0;
}