#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

#define SIZE 71

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
	std::stringstream answer;

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
	std::vector<std::vector<Vertex>> mapv = std::vector<std::vector<Vertex>>(SIZE, std::vector<Vertex>(SIZE));
	std::vector<Vertex*> graph;
	Vertex* start = &mapv[0][0], * end = &mapv[SIZE - 1][SIZE - 1];

	int i;
	for (i = 0; i < 1024; ++i) map[coords[i].first][coords[i].second] = '#';
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

	for (; i < coords.size(); ++i) {
		map[coords[i].first][coords[i].second] = '#';
		for (int e = 0; e < mapv[coords[i].first][coords[i].second].edges.size(); ++e) {
			mapv[coords[i].first][coords[i].second].edges[e].second = nullptr;
		}

		for (int v = 0; v < graph.size(); ++v) graph[v]->score = INT_MAX;
		start->score = 0;
		Dijkstra(graph, start, 0);
		if (end->score == INT_MAX) break;
	}

	answer << coords[i].second << "," << coords[i].first;

	return 0;
}