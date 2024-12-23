#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

#define SIZE 71
#define THRESH 1024

int drow[] = { 0, -1,  0, 1 };
int dcol[] = { 1,  0, -1, 0 };

struct Vertex {
	std::vector<std::pair<int, Vertex*>> edges;
	int score;
	Vertex() : score(INT_MAX) { }
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
	std::vector<std::pair<int, int>> coords;
	std::pair<int, int> coord;
	while (std::getline(file, line)) {
		sscanf_s(line.c_str(), "%d,%d", &coord.second, &coord.first);
		coords.push_back(coord);
	}

	file.close();

	std::vector<std::vector<char>> map = std::vector<std::vector<char>>(SIZE, std::vector<char>(SIZE, '.'));
	for (int i = 0; i < THRESH; ++i) map[coords[i].first][coords[i].second] = '#';

	std::vector<std::vector<Vertex>> mapv = std::vector<std::vector<Vertex>>(SIZE, std::vector<Vertex>(SIZE));
	std::vector<Vertex*> graph;
	Vertex *start = &mapv[0][0], *end = &mapv[SIZE - 1][SIZE - 1];
	
	for (size_t row = 0; row < SIZE; ++row) {
		for (size_t col = 0; col < SIZE; ++col) {
			if (map[row][col] == '#') continue;
			graph.push_back(&mapv[row][col]);
			for (int dir = 0; dir < 4; ++dir) {
				if (row + drow[dir] < 0 || row + drow[dir] >= SIZE || col + dcol[dir] < 0 || col + dcol[dir] >= SIZE) continue;
				graph.back()->edges.push_back({ 1, &mapv[row + drow[dir]][col + dcol[dir]] });
			}
		}
	}

	start->score = 0;
	Dijkstra(graph, start, 0);
	answer = end->score;

	return 0;
}