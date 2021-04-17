#include <iostream>
#include <map>
#include <vector>

#define is_exist(map, value) (map.find(value) != map.end())

using namespace std;

int to_binary(int n) {
	int p = 1, binary = 0;
	while (n) {
		if (n % 10) binary += p;
		p <<= 1;
		n /= 10;
	}

	return binary;
}

int main(void) {
	int
		L, K,
		n_operation,
		upper_limit = 1 << 10,
		lower_limit = 1;

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
				if (msb_found) {
					int next = now ^ (1 << i);
					if (next > upper_limit || next < lower_limit) continue;
					if (!is_exist(min_n_operation, next)) {
						// new value found
						min_n_operation.insert({ next, n_operation });
						next_visiting.push_back(next);
					}
				} else msb_found |= ((1 << i) & now);
			}

			// operation 2
			{
				int next = now + 1;
				if (next > upper_limit || next < lower_limit) continue;
				if (!is_exist(min_n_operation, next)) {
					// new value found
					min_n_operation.insert({ next, n_operation });
					next_visiting.push_back(next);
				}
			}

			// operation 3
			{
				int next = now - 1;
				if (next > upper_limit || next < lower_limit) continue;
				if (!is_exist(min_n_operation, next)) {
					// new value found
					min_n_operation.insert({ next, n_operation });
					next_visiting.push_back(next);
				}
			}
		}


		// swap vectors
		now_visiting.clear();
		now_visiting.insert(now_visiting.end(), next_visiting.begin(), next_visiting.end());
		next_visiting.clear();
	}

	// print the answer
	cout << min_n_operation.find(K)->second;

	return 0;
}