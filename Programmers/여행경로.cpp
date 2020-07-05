#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef vector<vector<int>> t_matrix;

// return whether the matrix is 0-matrix or not
bool is_0_matrix(t_matrix matrix) {
	int i, j, n = matrix.size(), m = matrix[0].size();

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			if (matrix[i][j] != 0) {
				return false;
			}
		}
	}

	return true;
}

vector<string> solution(vector<vector<string>> tickets) {
	vector<string> answer;
	t_matrix matrix; // [i][j]: from i to j
	vector<int> history; // histories: i to j
	vector<string> airport_names;
	map<string, int> airport_indexs;
	map<string, int>::iterator it_airport_indexs;

	int i, n_airport, n_ticket, n_history, now, now_search_from;

	// init airport_indexs
	n_ticket = tickets.size();
	for (i = 0; i < n_ticket; i++) {
		airport_indexs.insert(make_pair(tickets[i][0], 0));
		airport_indexs.insert(make_pair(tickets[i][1], 0));
	}

	// complete airport_names
	for (it_airport_indexs = airport_indexs.begin(); it_airport_indexs != airport_indexs.end(); it_airport_indexs++) {
		airport_names.push_back(it_airport_indexs->first);
	}
	sort(airport_names.begin(), airport_names.end());

	// complete airport_indexs
	n_airport = airport_names.size();
	for (i = 0; i < n_airport; i++) {
		airport_indexs.find(airport_names[i])->second = i;
	}

	// init matrix
	matrix.resize(n_airport, vector<int>(n_airport, 0));

	// config matrix
	for (i = 0; i < n_ticket; i++) {
		matrix[
			airport_indexs.find(tickets[i][0])->second
		][
			airport_indexs.find(tickets[i][1])->second
		]++;
	}

	// start from ICN
	now = airport_indexs.find("ICN")->second;
	now_search_from = 0;
	history.push_back(now);

	// start DFS from ICN
	while (true) {
		// pick next
		for (i = now_search_from; i < n_airport; i++) {
			if (matrix[now][i] > 0) {
				matrix[now][i]--;
				history.push_back(i);
				now = i;
				now_search_from = 0;
				break;
			}
		}

		// if next not found, check
		if (i >= n_airport) {
			// is all edge(ticket)s are used?
			if (is_0_matrix(matrix)) {
				// the end!
				break;
			} else {
				// false end! back
				while (true) {
					now_search_from = history.back();
					history.pop_back();
					now = history.back();
					matrix[now][now_search_from]++;

					for (i = now_search_from + 1; i < n_airport; i++) {
						if (matrix[now][i] > 0) {
							// restart here(now)
							now_search_from = i;
							break;
						}
					}

					// if another route found
					if (i < n_airport) {
						break;
					}
				}
			}
		}
	}

	// convert index to name
	n_history = history.size();
	for (i = 0; i < n_history; i++) {
		answer.push_back(airport_names[history[i]]);
	}

	return answer;
}