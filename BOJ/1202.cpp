// My life is shining like a VVS
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

struct VVS {
	int weight;
	int value;
};

// higher value and lower weight first
bool compare_vvs(const VVS &a, const VVS &b) {
	if (a.value != b.value) {
		return a.value > b.value;
	}
	return a.weight < b.weight;
}

int main(void) {
	int
		i, // indexer
		N, // the number of vvs
		K, // the number of bags
		M, // weight of a vvs
		V, // value of a vvs
		C; // capacity of a bag

	long long
		value_sum;

	vector<VVS>
		vvs; // { value, weight }

	multiset<int>
		bags;

	multiset<int>::iterator
		it_bags;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of vvs and bags
	cin >> N >> K;

	// get all vvs
	vvs.resize(N);
	for (i = 0; i < N; i++) {
		cin >> vvs[i].weight >> vvs[i].value;
	}

	// sort all vvs
	sort(vvs.begin(), vvs.end(), compare_vvs);

	// get all bags
	for (i = 0; i < K; i++) {
		cin >> C;
		bags.insert(C);
	}

	// take vvs
	value_sum = 0;
	for (i = 0; i < N; i++) {
		C = vvs[i].weight;
		it_bags = bags.lower_bound(C);
		if (it_bags != bags.end()) {
			value_sum += vvs[i].value;
			bags.erase(it_bags);
		}
	}

	// print the answer
	cout << value_sum;

	return 0;
}