#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> numbers = {
	"1", "2", "3", "4", "5", "6", "7", "8", "9",
	"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
};
int values[] = {
	1, 2, 3, 4, 5, 6, 7, 8, 9,
	1, 2, 3, 4, 5, 6, 7, 8, 9
};

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	size_t i, j, firsti, lasti;
	int firstdigit, lastdigit;
	while (std::getline(file, line)) {
		firsti = line.size();
		lasti = 0;
		firstdigit = 0;
		lastdigit = 0;
		for (i = 0u; i < numbers.size(); ++i) {
			if ((j = line.find(numbers[i])) != std::string::npos) {
				if (j <= firsti) {
					firstdigit = i % 9 + 1;
					firsti = j;
				}
			}
			if ((j = line.rfind(numbers[i])) != std::string::npos) {
				if (j >= lasti) {
					lastdigit = i % 9 + 1;
					lasti = j;
				}
			}
		}

		answer += firstdigit * 10 + lastdigit;
	}

	file.close();

	return 0;
}