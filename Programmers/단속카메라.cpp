#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool cmp_route(const vector<int> &a, const vector<int> &b) {
	return a[0] > b[0];
}

int solution(vector<vector<int>> routes) {
	int route_in, route_out, route_out_bound, answer = 0;

	// sort routes according to first value 
	sort(routes.begin(), routes.end(), cmp_route);

	// read routes
	route_out_bound = 30001;
	while (!routes.empty()) {
		route_in = routes.back()[0];
		route_out = routes.back()[1];
		routes.pop_back();

        // same camera available
		if (route_in <= route_out_bound) {
			route_out_bound = route_out_bound > route_out ? route_out : route_out_bound;
		} else {
            // need another camera
			answer++;
			route_out_bound = route_out;
		}
	}

	answer++;

	return answer;
}