#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

struct Directory {
	Directory() :
		parentdir(0),
		dirname(""),
		subdirs(std::vector<Directory*>()) { }
	~Directory() {
		for (std::vector<Directory*>::iterator it = subdirs.begin(); it < subdirs.end(); ++it) {
			if (*it) {
				delete (*it);
				*it = 0;
			}
		}
	}

	Directory* parentdir;
	std::string dirname;
	std::vector<Directory*> subdirs;
	std::vector<std::string> filename;
	std::vector<int> filesize;
};

int dirsizesum(Directory* dir, int* total) {
	int result = 0;
	int temp;
	if (!dir) return 0;
	for (std::vector<Directory*>::iterator it = dir->subdirs.begin(); it < dir->subdirs.end(); ++it) {
		temp = dirsizesum((*it), total);
		if (temp < 100000) {
			*total += temp;
		}
		result += temp;
	}
	for (std::vector<int>::iterator it = dir->filesize.begin(); it < dir->filesize.end(); ++it) {
		result += (*it);
	}

	return result;
}

// Day 7 - Part 1
int main() {
	int answer = 0;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	Directory root;
	Directory* currentdir = &root;
	Directory* newdir = 0;
	std::getline(file, line);
	while (file.good()) {
		if (line[0] == '$') {
			ssline = std::stringstream(line.substr(2U));
			ssline >> line;
			if (line == "ls") {
				while (std::getline(file, line)) {
					if (line[0] == '$') break;

					ssline = std::stringstream(line);
					ssline >> line;
					if (line == "dir") {
						ssline >> line;
						newdir = new Directory;
						newdir->parentdir = currentdir;
						newdir->dirname = line;
						currentdir->subdirs.push_back(newdir);
					} else {
						currentdir->filesize.push_back(std::stoi(line));
						ssline >> line;
						currentdir->filename.push_back(line);
					}
				}
			} else if (line == "cd") {
				ssline >> line;
				if (line == "/") {
					currentdir = &root;
				} else if (line == "..") {
					currentdir = currentdir->parentdir;
				} else {
					for (std::vector<Directory*>::iterator it = currentdir->subdirs.begin(); it < currentdir->subdirs.end(); ++it) {
						if ((*it)->dirname == line) {
							currentdir = (*it);
							break;
						}
					}
				}
				std::getline(file, line);
			}
		}
	}
	newdir = 0;
	currentdir = 0;

	file.close();

	dirsizesum(&root, &answer);

	return 0;
}