#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool make_sum(vector<int> weight, int start, int last, int sum)
{
	int w;

	// handle exception
	if (start > last) return false;

	w = weight[start];

	if (w > sum)
	{
		return make_sum(weight, start + 1, last, sum);
	}
	else if (w < sum)
	{
		return make_sum(weight, start + 1, last, sum - w) || make_sum(weight, start + 1, last, sum);
	}
	else
	{
		return true;
	}
}

int solution(vector<int> weight)
{
	int i, len, answer = 0;

	// sort desc. order
	sort(weight.begin(), weight.end(), greater<int>());

	len = weight.size();
	while (true)
	{
		answer++;
		for (i = 0; i < len; i++)
		{
			if (weight[i] > answer) continue;
			else break;
		}

		// make sum with weight[i] ~ weight[last]
		if (!make_sum(weight, i, len - 1, answer))
		{
			// impossible
			return answer;
		}
	}
}