#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> prices) {
	vector<int> answer;

	int i, j, price, len, last;

	len = prices.size();
	last = len - 1;
	answer.reserve(len);

	// do from the first
	for (i = 0; i < last; i++) {
		price = prices[i];

		// find index of smaller one after index i
		j = i + 1;
		while (j != last && prices[j] >= price) j++;
		answer.push_back(j - i);
	}

	// the last answer is always 0
	answer.push_back(0);

	return answer;
}