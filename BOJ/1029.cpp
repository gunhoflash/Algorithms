#include <iostream>
#include <vector>
#include <map>

using namespace std;

/*
	lower-price[n_buyer]

	key(int):
		               / owner / buyer
		0000 0000 0000 / 0000  / 0000 0000 0000 0000

	value(char):
		price
		0000 0000

	artist start from 0 to {N - 1}
*/

int main(void) {
	int
		i, j, now, next, // indexers
		N, // the number of artists
		max_n_buyer, // answer
		owner,
		buyer_bitmask,
		new_bitmask; // new_owner | new_buyer_bitmask

	char
		price,
		new_price;

	vector<vector<char>>
		sell_price;

	map<int, char>
		lower_price[2];

	map<int, char>::iterator
		it_lower_price;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of artists
	cin >> N;

	// set all sell prices
	sell_price.resize(N, vector<char>(N));
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			cin >> price;
			sell_price[i][j] = price;
		}
	}

	now = 0;
	next = 1;
	max_n_buyer = 0;
	lower_price[now].insert({ 1, 0 });
	while (!lower_price[now].empty()) {
		max_n_buyer++;

		// do something
		for (auto pair : lower_price[now]) {
			owner = pair.first >> 16;
			buyer_bitmask = pair.first & 0xFFFF;
			price = pair.second;

			// sell to others
			for (i = 0; i < N; i++) {
				// cannot sell with lower price
				new_price = sell_price[owner][i];
				if (new_price < price) continue;

				// cannot buy twice or more
				if ((buyer_bitmask >> i) & 1) continue;

				new_bitmask = (i << 16) | buyer_bitmask | (1 << i);

				// check whether same state exist
				it_lower_price = lower_price[next].find(new_bitmask);
				if (it_lower_price == lower_price[next].end()) {
					// new state
					lower_price[next].insert({ new_bitmask, new_price });
				} else if (it_lower_price->second > new_price) {
					// state exist but we make lower price
					it_lower_price->second = new_price;
				}
			}
		}

		// clear now
		lower_price[now].clear();

		// switch now and next
		now = now ? 0 : 1;
		next = next ? 0 : 1;
	}

	// print the answer
	cout << max_n_buyer;

	return 0;
}