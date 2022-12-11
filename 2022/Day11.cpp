#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

const int NUM_ROUNDS = 20; // Part 1
// const int NUM_ROUNDS = 20; // Part 2

struct Operation {
	Operation() : fac(1LL) {};
	~Operation() {};
	long long fac;
	virtual long long execute(long long in) { return in; };
};
struct Add      : Operation { Add(long long f)      { fac = f; }; long long execute(long long in) override { return in + fac; }; };
struct Multiply : Operation { Multiply(long long f) { fac = f; }; long long execute(long long in) override { return in * fac; }; };
struct Square   : Operation { Square(long long f)   { fac = f; }; long long execute(long long in) override { return in * in;  }; };
struct Modulo   : Operation { Modulo(long long f)   { fac = f; }; long long execute(long long in) override { return in % fac; }; };

struct Monkey {
	Monkey() : succ(0), fail(0), op(0), test(0), inspections(0) {};
	~Monkey() { delete op; delete test; };

	std::vector<long long> items;
	Operation* op;
	Operation* test;
	int succ;
	int fail;
	long long inspections;

	bool operator > (const Monkey& m) const { return (inspections > m.inspections); };
};

// Day 11 - Part 1 and 2
int main() {
	long long answer = 0LL;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	std::vector<Monkey*> monkeys = std::vector<Monkey*>();
	Monkey* monk = 0;
	char opchar;
	std::string facstr;

	std::getline(file, line); // Monkey
	while (file.good()) {
		monk = new Monkey;
		std::getline(file, line); // Starting items
		ssline = std::stringstream(line.substr(18));
		while (std::getline(ssline, line, ',')) {
			monk->items.push_back(std::stoll(line));
		}

		std::getline(file, line); // Operation
		opchar = line[23];
		facstr = line.substr(25);
		if (opchar == '+') monk->op = new Add(std::stoll(facstr));
		if (opchar == '*') {
			if (facstr == "old") monk->op = new Square(1LL);
			else monk->op = new Multiply(std::stoll(facstr));
		}

		std::getline(file, line); // Test
		monk->test = new Modulo(std::stoll(line.substr(21)));

		std::getline(file, line); // If true
		monk->succ = std::stoi(line.substr(29));
		std::getline(file, line); // If false
		monk->fail = std::stoi(line.substr(30));

		monkeys.push_back(monk);
		std::getline(file, line);
		std::getline(file, line); // Monkey
	}

	file.close();

	long long lcm_test = 1LL;
	for (std::vector<Monkey*>::iterator it = monkeys.begin(); it < monkeys.end(); ++it) { lcm_test *= (*it)->test->fac; }

	for (int round = 0; round < NUM_ROUNDS; ++round) {
		for (std::vector<Monkey*>::iterator it = monkeys.begin(); it < monkeys.end(); ++it) {
			for (std::vector<long long>::iterator itemit = (*it)->items.begin(); itemit < (*it)->items.end(); ++itemit) {
				(*itemit) = (*it)->op->execute((*itemit));
				(*itemit) = (long long)std::floorl((long double)(*itemit) / 3.0L); // Part 1
				//(*itemit) %= lcm_test; // Part 2
				if ((*it)->test->execute((*itemit)) == 0) monkeys[(*it)->succ]->items.push_back((*itemit));
				else monkeys[(*it)->fail]->items.push_back((*itemit));
				(*it)->inspections += 1LL;
			}
			(*it)->items.clear();
		}
	}

	std::sort(monkeys.begin(), monkeys.end(), [](const Monkey* m1, const Monkey* m2) { return m1->inspections > m2->inspections; });
	answer = monkeys[0]->inspections * monkeys[1]->inspections;

	for (std::vector<Monkey*>::iterator it = monkeys.begin(); it < monkeys.end(); ++it) {
		delete (*it);
		*it = 0;
	}

	return 0;
}