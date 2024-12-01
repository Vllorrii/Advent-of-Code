#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main() {
	int pause;
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	std::vector<int> leftList, rightList;
	int num;
	while (std::getline(file, line)) {
		ssline = std::stringstream(line);
		ssline >> num;
		leftList.push_back(num);
		ssline >> num;
		rightList.push_back(num);
	}

	file.close();

	std::sort(leftList.begin(), leftList.end());
	std::sort(rightList.begin(), rightList.end());

	for (int i = 0; i < leftList.size(); ++i) {
		answer += std::abs(leftList[i] - rightList[i]);
	}

	return 0;
}