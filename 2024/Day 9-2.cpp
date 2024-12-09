#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct FileBlock {
	int pos;
	int id;
	int length;
};

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::getline(file, line);
	std::vector<FileBlock> fileblocks = std::vector<FileBlock>();
	int pos = 0;
	for (size_t i = 0; i < line.size(); ++i) {
		if (i % 2 == 0) {
			fileblocks.push_back({ pos, (int)i / 2, (int)(line[i] - '0') });
		} else if (line[i] - '0' > 0) {
			fileblocks.push_back({ pos, -1, (int)(line[i] - '0') });
		}
		pos += (int)(line[i] - '0');
	}

	file.close();

	for (int i = fileblocks.size() - 1; i > 0; --i) {
		if (fileblocks[i].id == -1) continue;
		for (int j = 0; j < i; ++j) {
			if (fileblocks[j].id != -1) continue;
			if (fileblocks[i].pos <= fileblocks[j].pos) break;

			if (fileblocks[j].length == fileblocks[i].length) {
				fileblocks[j].id = fileblocks[i].id;
				fileblocks[i].id = -1;
				break;
			} else if (fileblocks[j].length > fileblocks[i].length) {
				fileblocks.insert(fileblocks.begin() + j,
					{ fileblocks[j].pos, fileblocks[i].id, fileblocks[i].length });
				++i;
				fileblocks[j + 1].pos = fileblocks[j].pos + fileblocks[j].length;
				fileblocks[j + 1].length = fileblocks[j + 1].length - fileblocks[j].length;

				fileblocks[i].id = -1;
				break;
			}
		}
	}

	for (size_t i = 0; i < fileblocks.size(); ++i) {
		if (fileblocks[i].id == -1) continue;
		for (size_t pos = fileblocks[i].pos; pos < fileblocks[i].pos + fileblocks[i].length; ++pos) {
			answer += pos * fileblocks[i].id;
		}
	}

	return 0;
}