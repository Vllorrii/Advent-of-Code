#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

int drow[] = { 0, -1,  0, 1 };
int dcol[] = { 1,  0, -1, 0 };

struct Vertex {
	std::vector<std::pair<int, Vertex*>> edges;
	int score;
};

int Dijkstra(std::vector<Vertex*> graph, Vertex* start, Vertex* end) {
	std::priority_queue<Vertex*, std::vector<Vertex*>, std::less<Vertex*>> pq;
	pq.push(start);
	while (!pq.empty()) {
		Vertex* curr = pq.top();
		pq.pop();
		for (size_t e = 0; e < curr->edges.size(); ++e) {
			if (curr->edges[e].second) {
				if (curr->edges[e].second->score > curr->score + curr->edges[e].first) {
					curr->edges[e].second->score = curr->score + curr->edges[e].first;
					pq.push(curr->edges[e].second);
				}
			}
		}
		if (curr == end) break;
	}

	if (end) return end->score;
	return 0;
}

int main() {
	long long answer = 0ll;

	std::ifstream file("input.txt", std::ios::in);

	std::string line;
	std::stringstream ssline;
	std::vector<std::vector<Vertex*>> maze[4];
	Vertex* start = 0, *end[4];
	size_t row = 0, col;
	while (std::getline(file, line)) {
		for (int i = 0; i < 4; ++i) maze[i].push_back(std::vector<Vertex*>());
		for (col = 0; col < line.size(); ++col) {
			if (line[col] == '#') {
				for (int i = 0; i < 4; ++i) {
					maze[i][row].push_back(nullptr);
				}
			} else {
				for (int i = 0; i < 4; ++i) {
					maze[i][row].push_back(new Vertex);
					maze[i][row][col]->score = INT_MAX;

					if (line[col] == 'E') end[i] = maze[i][row][col];
				}
				if (line[col] == 'S') {
					maze[0][row][col]->score = 0;
					start = maze[0][row][col];
				}
			}
		}
		++row;
	}

	file.close();

	std::vector<Vertex*> mazegraph;
	int cost;
	for (int dir = 0; dir < 4; ++dir) {
		for (size_t row = 0; row < maze[dir].size(); ++row) {
			for (size_t col = 0; col < maze[dir][row].size(); ++col) {
				if (!maze[dir][row][col]) continue;
				mazegraph.push_back(maze[dir][row][col]);
				mazegraph.back()->edges.push_back({ 1, maze[dir][row + drow[dir]][col + dcol[dir]] });
				for (int ddir = 1; ddir < 4; ++ddir) {
					cost = ddir == 2 ? 2000 : 1000;
					mazegraph.back()->edges.push_back({ cost, maze[(dir + ddir) % 4][row][col] });
				}
			}
		}
	}

	Dijkstra(mazegraph, start, nullptr);
	answer = INT_MAX;
	for (int i = 0; i < 4; ++i) answer = std::min(answer, (long long)end[i]->score);

	for (size_t i = 0; i < mazegraph.size(); ++i) free(mazegraph[i]);

	return 0;
}