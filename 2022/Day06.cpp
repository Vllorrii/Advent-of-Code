#include <fstream>
#include <iostream>
#include <algorithm>

// Day 6 - Part 1 and 2
int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	const int MARKER_SIZE = 4; // Part 1
	//const int MARKER_SIZE = 14; // Part 2
	char sop[MARKER_SIZE];
	char sop_sort[MARKER_SIZE];
	char next;

	file.read(sop, MARKER_SIZE);
	answer = MARKER_SIZE;
	do {
		memcpy(sop_sort, sop, MARKER_SIZE);
		std::sort(sop_sort, sop_sort + MARKER_SIZE);
		if (std::adjacent_find(sop_sort, sop_sort + MARKER_SIZE) == (sop_sort + MARKER_SIZE)) break;

		file.get(next);
		sop[answer % MARKER_SIZE] = next;
		++answer;
	} while (next != '\n');

	file.close();

	return 0;
}