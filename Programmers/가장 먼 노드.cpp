#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INTMAX 2147483647

int solution(int n, vector<vector<int>> edge) {
	int
	i, size,
	node1, node2, distance, distance_max,
	answer = 0;
	vector<int> distances;
	vector<vector<int>> neighbors;
	queue<int> to_visit;

	// init visit
	distances.resize(n + 1, INTMAX);
	neighbors.resize(n + 1, {});

	// init neighbors
	size = edge.size();
	for (i = 0; i < size; i++) {
		node1 = edge[i][0];
		node2 = edge[i][1];

		neighbors[node1].push_back(node2);
		neighbors[node2].push_back(node1);
	}

	to_visit.push(1);
	distances[1] = 0;
	distance_max = 0;

	// BFS
	while (!to_visit.empty()) {
		// visit here!
		node1 = to_visit.front();
		to_visit.pop();
		distance = distances[node1] + 1;

		// check neighbors to visit
		size = neighbors[node1].size();
		for (i = 0; i < size; i++) {
			node2 = neighbors[node1][i];
			if (distances[node2] == INTMAX) {
				// new visit
				distances[node2] = distance;
				to_visit.push(node2);
				if (distance_max < distance) {
					distance_max = distance;
					answer = 1;
				} else {
					answer++;
				}
			}
		}
	}

	return answer;
}