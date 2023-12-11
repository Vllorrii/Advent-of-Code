#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

struct Hand {
	int cards[5];
	int bid;
};

int rankHand(Hand h) {
	std::vector<int> count = std::vector<int>(13, 0);
	for (int i = 0; i < 5; ++i) count[h.cards[i]] += 1;
	count.erase(std::remove(count.begin(), count.end(), 0), count.end());
	std::sort(count.rbegin(), count.rend());
	if (count[0] == 5) return 7;
	if (count[0] == 4) return 6;
	if (count[0] == 3) {
		if (count[1] == 2) return 5;
		return 4;
	}
	if (count[0] == 2) {
		if (count[1] == 2) return 3;
		return 2;
	}
	return 1;
}

bool compareHands(Hand const& a, Hand const& b) {
	int ranka = rankHand(a);
	int rankb = rankHand(b);
	if (ranka == rankb) {
		for (int i = 0; i < 5; ++i) {
			if (a.cards[i] < b.cards[i]) return true;
			else if (a.cards[i] > b.cards[i]) return false;
		}
		return false;
	}
	return ranka < rankb;
}

int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	std::vector<Hand> allHands;
	Hand h;
	while (std::getline(file, line)) {
		memset(&h, 0, sizeof Hand);
		for (int i = 0; i < 5; ++i) {
			if (isdigit(line[i])) h.cards[i] = line[i] - '0' - 2;
			else switch (line[i]) {
			case 'T': h.cards[i] = 8;  break;
			case 'J': h.cards[i] = 9;  break;
			case 'Q': h.cards[i] = 10; break;
			case 'K': h.cards[i] = 11; break;
			default:  h.cards[i] = 12;
			}
		}
		h.bid = std::stoi(line.substr(6));
		allHands.push_back(h);
	}
	file.close();

	std::sort(allHands.begin(), allHands.end(), &compareHands);
	for (int i = 0; i < allHands.size(); ++i) {
		answer += allHands[i].bid * (i + 1);
	}

	return 0;
}