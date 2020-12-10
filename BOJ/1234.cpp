#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct RGB {
	int r;
	int g;
	int b;

	bool operator<(const RGB &rgb) const {
		if (this->r != rgb.r) return this->r < rgb.r;
		if (this->g != rgb.g) return this->g < rgb.g;
		return this->b < rgb.b;
	}
};

vector<vector<long long>> nCr;

void init_nCr() {
	int
		i, j; // indexers

	nCr.resize(11, vector<long long>(11));

	nCr[1][0] = 1;
	nCr[1][1] = 1;
	for (i = 2; i <= 10; i++) {
		nCr[i][0] = 1;
		for (j = 1; j <= 10; j++) {
			nCr[i][j] = nCr[i - 1][j - 1] + nCr[i - 1][j];
		}
	}
}

int main(void) {
	int
		i, // indexer
		N, // size of the tree (N <= 10)
		remained_r, remained_g, remained_b; // (0 << n << 100)

	long long
		n_case;

	vector<map<RGB, long long>>
		level_map; // index 0 never being used

	map<RGB, long long>
		*prev, *now;

	// get the number of colors
	cin >> N >> remained_r >> remained_g >> remained_b;

	// pre-calculate nCr
	init_nCr();

	// init {level_map}
	level_map.resize(N + 1);

	// do the level 0
	level_map[0].insert({{ remained_r, remained_g, remained_b }, 1 });

	// do the level from 1 to N
	for (i = 1; i <= N; i++) {
		prev = &(level_map[i - 1]);
		now  = &(level_map[i]);
		for (auto const &rgbn : *prev) {
			remained_r = rgbn.first.r;
			remained_g = rgbn.first.g;
			remained_b = rgbn.first.b;
			n_case     = rgbn.second;

			// do with only one color
			// the number of cases with 1 color: 1
			if (remained_r >= i) (*now)[{ remained_r - i, remained_g    , remained_b     }] += n_case;
			if (remained_g >= i) (*now)[{ remained_r    , remained_g - i, remained_b     }] += n_case;
			if (remained_b >= i) (*now)[{ remained_r    , remained_g    , remained_b - i }] += n_case;

			// do with two colors
			if (i >= 2 && i % 2 == 0) {
				// each color should more than or equal to { i / 2 }
				// the number of cases with two colors: { nCr[i][i / 2] }

				// red & green
				if (remained_r >= i / 2 && remained_g >= i / 2)
					(*now)[{ remained_r - i / 2, remained_g - i / 2, remained_b         }] += n_case * nCr[i][i / 2];

				// red & blue
				if (remained_r >= i / 2 && remained_b >= i / 2)
					(*now)[{ remained_r - i / 2, remained_g        , remained_b - i / 2 }] += n_case * nCr[i][i / 2];
				
				// green & blue
				if (remained_g >= i / 2 && remained_b >= i / 2)
					(*now)[{ remained_r        , remained_g - i / 2, remained_b - i / 2 }] += n_case * nCr[i][i / 2];
			}

			// do with three colors
			if (i >= 3 && i % 3 == 0) {
				// each color should more than or equal to { i / 3 }
				// the number of cases with three colors: { nCr[i][i / 3] * nCr[i - i / 3][i / 3] }

				if (remained_r >= i / 3 && remained_g >= i / 3 && remained_b >= i / 3)
					(*now)[{ remained_r -  i / 3, remained_g - i / 3, remained_b - i / 3 }] += n_case * nCr[i][i / 3] * nCr[i - i / 3][i / 3];
			}
		}
	}

	// count the number of cases at level N
	n_case = 0;
	for (auto const &rgbn : level_map[N]) {
		n_case += rgbn.second;
	}

	// print the answer
	cout << n_case;

	return 0;
}