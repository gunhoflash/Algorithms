#include <iostream>
#include <vector>

using namespace std;

#define HIT            1
#define TWO_BASE_HIT   2
#define THREE_BASE_HIT 3
#define HOME_RUN       4
#define OUT            0

#define max(a, b) (a > b ? a : b)

vector<vector<int>> player_results;
vector<int> order(9);
vector<bool> selected(9, false);

int get_score() {
	int
		score,
		inning,
		player,
		player_result,
		out_count;

	vector<int> base(3, 0); // runners in each base

	// prepare game
	score = 0;
	player = 0;

	// start inning 1
	inning = 0;
	while (inning < player_results.size()) {

		// start new inning
		out_count = 0;
		base[2] = base[1] = base[0] = 0;

		while (out_count < 3) {
			player_result = player_results[inning][order[player]];

			// add score and run
			switch (player_result) {
				case HIT:
					score += base[2];
					base[2] = base[1];
					base[1] = base[0];
					base[0] = 1;
					break;
				case TWO_BASE_HIT:
					score += base[2] + base[1];
					base[2] = base[0];
					base[1] = 1;
					base[0] = 0;
					break;
				case THREE_BASE_HIT:
					score += base[2] + base[1] + base[0];
					base[2] = 1;
					base[1] = base[0] = 0;
					break;
				case HOME_RUN:
					score += base[2] + base[1] + base[0] + 1;
					base[2] = base[1] = base[0] = 0;
					break;
				case OUT:
					out_count++;
					break;
			}

			player = (player + 1) % 9;
		}

		inning++;
	}

	return score;
}

int get_max_score(int index) {
	int
		i, // indexer
		score, max_score;

	// index 3 is reserved
	if (index == 3) {
		return get_max_score(4);
	}

	// end of selection
	if (index == 9) {
		return get_score();
	}

	// select order[index]
	max_score = 0;
	for (i = 0; i < 9; i++) {
		if (!selected[i]) {
			selected[i] = true;
			order[index] = i;
			score = get_max_score(index + 1);
			max_score = max(max_score, score);
			selected[i] = false;
		}
	}

	return max_score;
}

int main(void) {
	int
		i, j, // indexers
		N;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of innings
	cin >> N;

	// init {player_results}
	player_results.resize(N, vector<int>(9));
	for (i = 0; i < N; i++) {
		for (j = 0; j < 9; j++) {
			cin >> player_results[i][j];
		}
	}

	order[3] = 0;
	selected[0] = true;

	cout << get_max_score(0);

	return 0;
}