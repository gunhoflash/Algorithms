#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct University {
	char type; // 'M' or 'W'
	int group;
};

struct Road {
	int from;
	int to;
	int cost;
};

bool compare_road(const Road &a, const Road &b) {
	return a.cost > b.cost;
}

int find_group(int i, vector<University> &universities) {
	if (universities[i].group == i) {
		return i;
	}

	return find_group(universities[i].group, universities);
}

void merge_group(int a, int b, vector<University> &universities) {
	universities[find_group(a, universities)].group = find_group(b, universities);
}

int main(void) {
	int
		i,
		N, // the number of universities
		M, // the number of roads
		u, v, d,
		n_selected_roads, // the number of selected roads
		total_road_cost; // the answer to print

	vector<University>
		universities; // index 0 never being used

	vector<Road>
		roads;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of universities and roads
	cin >> N >> M;
	universities.resize(N + 1);

	// set each univ.'s type and group
	for (i = 1; i <= N; i++) {
		cin >> universities[i].type;
		universities[i].group = i;
	}

	// get all roads
	for (i = 0; i < M; i++) {
		cin >> u >> v >> d;

		// ignore a road connecting universities that have same type
		if (universities[u].type == universities[v].type) continue;

		roads.push_back({ u, v, d });
	}

	// sort all road by cost
	sort(roads.begin(), roads.end(), compare_road);

	// select {N - 1} roads
	total_road_cost = 0;
	n_selected_roads = 0;
	while (n_selected_roads < N - 1) {
		// handle exception: no more road to select
		if (roads.empty())
			break;

		// pop a road
		u = roads.back().from;
		v = roads.back().to;
		d = roads.back().cost;
		roads.pop_back();

		// select the road and unite universities
		if (find_group(u, universities) != find_group(v, universities)) {
			merge_group(u, v, universities);
			total_road_cost += d;
			n_selected_roads++;
		}
	}

	// print the answer
	cout << (n_selected_roads == N - 1 ? total_road_cost : -1);

	return 0;
}