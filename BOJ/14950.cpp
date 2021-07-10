#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
	int a;
	int b;
	int cost;
};

bool compare_edge(const Edge &a, const Edge &b) {
	return a.cost < b.cost;
}

int find_prev(int city, vector<int> &prev_city) {
	if (prev_city[city] == city) return city;
	return prev_city[city] = find_prev(prev_city[city], prev_city);
}

bool union_city(int a, int b, vector<int> &prev_city) {
	int
		prev_city_a = find_prev(a, prev_city),
		prev_city_b = find_prev(b, prev_city);

	if (prev_city_a == prev_city_b) return false;

	prev_city[prev_city_b] = prev_city_a;
	return true;
}

int main(void) {
	int
		N, M, t,
		n_conquered_cities = 1,
		answer = 0;
	vector<int> prev_city;
	vector<Edge> edges;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M >> t;

	// init prev_city
	prev_city.resize(N + 1);
	for (int i = 1; i <= N; i++) {
		prev_city[i] = i;
	}

	// init all edges and sort by cost
	edges.resize(M);
	for (int i = 0; i < M; i++) {
		cin >> edges[i].a >> edges[i].b >> edges[i].cost;
	}
	sort(edges.begin(), edges.end(), compare_edge);

	// conquer all cities
	for (int i = 0; i < M; i++) {
		if (n_conquered_cities == N) break;
		if (union_city(edges[i].a, edges[i].b, prev_city))  {
			answer += edges[i].cost;
			n_conquered_cities++;
		}
	}

	// print the answer
	answer += (N - 1) * (N - 2) / 2 * t;
	cout << answer;

	return 0;
}
