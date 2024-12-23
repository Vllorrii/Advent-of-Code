#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

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
	std::stringstream ssline;
	std::vector<std::vector<Vertex>> forwardtrack, backwardtrack;
	std::vector<Vertex*> forwardgraph, backwardgraph;
	Vertex *start = 0, *forwardend = 0, *backwardend = 0;
	std::vector<std::vector<char>> map;
	while (std::getline(file, line)) {
		map.push_back(std::vector<char>());
		map.back().assign(line.begin(), line.end());
	}

	file.close();

	forwardtrack = std::vector<std::vector<Vertex>>(map.size(), std::vector<Vertex>(map[0].size()));
	backwardtrack = std::vector<std::vector<Vertex>>(map.size(), std::vector<Vertex>(map[0].size()));;
	for (size_t row = 0; row < map.size(); ++row) {
		for (size_t col = 0; col < map[0].size(); ++col) {
			if (map[row][col] == '#') continue;
			if (map[row][col] == 'S') start = &forwardtrack[row][col];
			if (map[row][col] == 'E') { forwardend = &forwardtrack[row][col]; backwardend = &backwardtrack[row][col]; }
			forwardgraph.push_back(&forwardtrack[row][col]);
			backwardgraph.push_back(&backwardtrack[row][col]);
			for (int dir = 0; dir < 4; ++dir) {
				if (row + drow[dir] >= map.size() || col + dcol[dir] >= map[0].size()) continue;
				if (map[row + drow[dir]][col + dcol[dir]] == '#') continue;
				forwardgraph.back()->edges.push_back({ 1, &forwardtrack[row + drow[dir]][col + dcol[dir]] });
				backwardgraph.back()->edges.push_back({ 1, &backwardtrack[row + drow[dir]][col + dcol[dir]] });
			}
		}
	}

	start->score = 0;
	backwardend->score = 0;
	Dijkstra(forwardgraph, start, nullptr);
	Dijkstra(backwardgraph, backwardend, nullptr);
	long long score, basescore = forwardend->score;
	
	size_t rowto, colto;
	std::vector<long long> savings;
	for (size_t row = 0; row < map.size(); ++row) {
		for (size_t col = 0; col < map[0].size(); ++col) {
			if (map[row][col] == '#') continue;
			for (int dir = 0; dir < 4; ++dir) {
				rowto = row + 2 * drow[dir];
				colto = col + 2 * dcol[dir];
				if (rowto < map.size() && colto < map[0].size()) {
					if (map[row + drow[dir]][col + dcol[dir]] == '#' && map[rowto][colto] != '#') {
						score = forwardtrack[row][col].score + 2 + backwardtrack[rowto][colto].score;
						if (score < basescore) {
							savings.push_back(basescore - score);
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < savings.size(); ++i) if (savings[i] >= 100) ++answer;

	return 0;
}