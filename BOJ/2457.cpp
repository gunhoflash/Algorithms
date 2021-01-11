#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Flower {
	int bloom; // month * 100 + day
	int fade; // month * 100 + day
};

// for priority queue
bool operator<(const Flower &a, const Flower &b) {
	return a.fade < b.fade;
}

// for sort
bool compare_flower_bloom(const Flower &a, const Flower &b) {
	return a.bloom < b.bloom;
}

int main(void) {
	int
		i, // indexer
		N, // the number of flowers
		n_flower_selected, // the number of selected flowers
		month, day, month_day;

	vector<Flower>
		flowers;

	priority_queue<Flower>
		selectable_flowers;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get all flowers
	cin >> N;
	flowers.resize(N);
	for (i = 0; i < N; i++) {
		cin >> month >> day;
		flowers[i].bloom = month * 100 + day;
		cin >> month >> day;
		flowers[i].fade = month * 100 + day;
	}

	// sort flowers by bloom
	sort(flowers.begin(), flowers.end(), compare_flower_bloom);

	// select flowers
	i = 0;
	month_day = 301;
	n_flower_selected = 0;
	while (month_day < 1200) {
		// check all flowers which is in bloom today
		while (i < N && flowers[i].bloom <= month_day) {
			if (flowers[i].fade > month_day) {
				selectable_flowers.push(flowers[i]);
			}
			i++;
		}

		// handle exception: no flower to select
		if (selectable_flowers.empty()) {
			n_flower_selected = 0;
			break;
		}

		// take the last-fadinf flower
		month_day = selectable_flowers.top().fade;
		selectable_flowers.pop();
		n_flower_selected++;
	}

	// print the answer
	cout << n_flower_selected;

	return 0;
}