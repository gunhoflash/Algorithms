#define UPPER_LIMIT 0b10000000000
#define LOWER_LIMIT 1

#include <iostream>
#include <map>
#include <vector>

using namespace std;

inline int to_binary(int n) {
	int p = 1, binary = 0;
	while (n) {
		if (n % 10) binary += p;
		p <<= 1;
		n /= 10;
	}
	return binary;
}

inline bool is_exist(map<int, int> &map, int value) {
	return map.find(value) != map.end();
}

inline void clear_swap(vector<int> &from, vector<int> &to) {
	to.clear();
	to.insert(to.end(), from.begin(), from.end());
	from.clear();
}

inline void check_and_assign(int next, int n_operation, map<int, int> &min_n_operation, vector<int> &next_visiting) {
	if (next <= UPPER_LIMIT && next >= LOWER_LIMIT && !is_exist(min_n_operation, next)) {
		min_n_operation.insert({ next, n_operation });
		next_visiting.push_back(next);
	}
}


int main(void) {
	int
		L, K,
		n_operation;

	map<int, int> min_n_operation;
	vector<int> now_visiting, next_visiting;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// convert binary-like to binary
	cin >> L >> K;
	L = to_binary(L);
	K = to_binary(K);

	// init
	n_operation = 0;
	min_n_operation.insert({ L, 0 });
	now_visiting.push_back(L);

	while (true) {
		if (is_exist(min_n_operation, K)) break;

		n_operation++;
		for (auto now : now_visiting) {
			// operation 1
			bool msb_found = false;
			for (int i = 10; i >= 0; i--) {
				if (msb_found)
					check_and_assign(now ^ (1 << i), n_operation, min_n_operation, next_visiting);
				else
					msb_found |= (1 << i) & now;
			}

			// operation 2, 3
			check_and_assign(now + 1, n_operation, min_n_operation, next_visiting);
			check_and_assign(now - 1, n_operation, min_n_operation, next_visiting);
		}

		// swap vectors
		clear_swap(next_visiting, now_visiting);
	}

	// print the answer
	cout << min_n_operation.find(K)->second;

	return 0;
}