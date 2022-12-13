#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>

int packet_comp(std::string p1, std::string p2) {
	int result, level;
	int i;
	std::vector<std::string> p1elem = std::vector<std::string>();
	std::vector<std::string> p2elem = std::vector<std::string>();

	if (p1[0] == '[' && p2[0] == '[') {
		level = 0;
		result = 0;
		for (i = 1; i < p1.size() - 1; ++i) {
			if (p1[i] == '[') ++level;
			else if (p1[i] == ']') --level;
			else if (p1[i] == ',' && level == 0) {
				p1elem.push_back(p1.substr(result + 1, i - result - 1));
				result = i;
			}
		}
		if (i > 1) p1elem.push_back(p1.substr(result + 1, i - result - 1));

		level = 0;
		result = 0;
		for (i = 1; i < p2.size() - 1; ++i) {
			if (p2[i] == '[') ++level;
			else if (p2[i] == ']') --level;
			else if (p2[i] == ',' && level == 0) {
				p2elem.push_back(p2.substr(result + 1, i - result - 1));
				result = i;
			}
		}
		if (i > 1) p2elem.push_back(p2.substr(result + 1, i - result - 1));

		level = std::min(p1elem.size(), p2elem.size());
		for (int i = 0; i < level; ++i) {
			result = packet_comp(p1elem[i], p2elem[i]);
			if (result != 0) return result;
		}
		result = std::max(std::min((int)p2elem.size() - (int)p1elem.size(), 1), -1);
		return result;
	}

	if (p1[0] != '[' && p2[0] == '[') {
		p1.insert(p1.begin(), '[');
		p1.push_back(']');
		return packet_comp(p1, p2);
	}

	if (p1[0] == '[' && p2[0] != '[') {
		p2.insert(p2.begin(), '[');
		p2.push_back(']');
		return packet_comp(p1, p2);
	}

	result = std::max(std::min(std::stoi(p2) - std::stoi(p1), 1), -1);
	return result;
}

// Day 13 - Part 1
int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string packet;
	int index;
	std::list<std::string> packets = std::list<std::string>();
	std::list<std::string>::iterator it;
	packets.push_back("[[2]]");
	packets.push_back("[[6]]");
	while (std::getline(file, packet)) {
		if (!packet.empty()) {
			for (it = packets.begin(); it != packets.end(); ++it) {
				answer = packet_comp(packet, *it);
				if (answer == 1) {
					packets.insert(it, packet);
					break;
				}
			}
			if (it == packets.end()) packets.push_back(packet);
		}
	}

	file.close();

	answer = 1;
	index = 1;
	for (it = packets.begin(); it != packets.end(); ++it) {
		if ((*it) == "[[2]]" || (*it) == "[[6]]") answer *= index;
		++index;
	}

	return 0;
}