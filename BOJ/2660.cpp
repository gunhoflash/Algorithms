#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define NO_DEPTH -1
#define MAX_SCORE 50

using namespace std;

int main(void) {
	int
		i, // indexers
		member1, member2,
		n_member, // the number of members
		max_relationship_depth,
		min_score;

	vector<vector<bool>>
		is_friend;

	vector<int>
		relationship_depth,
		candidates;

	queue<int>
		visiting_queue;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get the number of members
	cin >> n_member;
	is_friend.resize(n_member + 1, vector<bool>(n_member + 1, false));
	relationship_depth.resize(n_member + 1);

	// set relationships
	while (true) {
		cin >> member1 >> member2;

		if (member1 == -1) break;

		is_friend[member1][member2] = true;
		is_friend[member2][member1] = true;
	}

	// check score of each member
	min_score = MAX_SCORE;
	for (i = 1; i <= n_member; i++) {
		// init
		relationship_depth.assign(n_member + 1, NO_DEPTH);

		// start from member-{i}
		relationship_depth[i] = 0;
		max_relationship_depth = 0;
		visiting_queue.push(i);
		while (!visiting_queue.empty()) {
			// pop one
			member1 = visiting_queue.front();
			visiting_queue.pop();

			max_relationship_depth = max(max_relationship_depth, relationship_depth[member1]);
			if (max_relationship_depth > min_score) {
				// early stop
				break;
			}

			// visit friends
			for (member2 = 1; member2 <= n_member; member2++) {
				if (is_friend[member1][member2] && relationship_depth[member2] == NO_DEPTH) {
					relationship_depth[member2] = relationship_depth[member1] + 1;
					visiting_queue.push(member2);
				}
			}
		}
		
		// clear queue
		while (!visiting_queue.empty()) visiting_queue.pop();

		// update {min_score}
		if (max_relationship_depth < min_score) {
			// new score
			min_score = max_relationship_depth;
			candidates.clear();
			candidates.push_back(i);
		} else if (max_relationship_depth == min_score) {
			// same score
			candidates.push_back(i);
		}
	}

	// print the answer
	cout << min_score << ' ' << candidates.size() << '\n';
	for (auto candidate : candidates) {
		cout << candidate << ' ';
	}

	return 0;
}