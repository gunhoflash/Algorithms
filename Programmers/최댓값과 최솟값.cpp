#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;

string solution(string s) {
	vector<string> s_vector;
	string token;
	stringstream ss(s);
	int t, max = INT_MIN, min = INT_MAX;

	while (ss >> token) {
		t = atoi(token.c_str());

		if (t > max) max = t;
		if (t < min) min = t;
	}
	return to_string(max) + " " + to_string(min);
}