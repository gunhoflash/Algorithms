#include <algorithm>
#include <vector>

using namespace std;

int solution(vector<int> scoville, int K) {
	int food1, food2, answer = 0;

	make_heap(scoville.begin(), scoville.end(), greater<int>());

	while (true) {
		if (scoville.size() == 0) {
			// no way
			answer = -1;
			break;
		} else if (scoville.front() >= K) {
			// done
			break;
		} else if (scoville.size() == 1) {
			// no way
			answer = -1;
			break;
		} else {
			// mix foods
			pop_heap(scoville.begin(), scoville.end(), greater<int>());
			food1 = scoville.back();
			scoville.pop_back();
			pop_heap(scoville.begin(), scoville.end(), greater<int>());
			food2 = scoville.back();
			scoville.pop_back();

			scoville.push_back(food1 + food2 * 2);
			push_heap(scoville.begin(), scoville.end(), greater<int>());
			answer++;
		}
	}

	return answer;
}