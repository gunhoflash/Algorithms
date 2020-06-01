#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
	int h, len, answer = 0;
	
	len = citations.size();
	sort(citations.begin(), citations.end());

	for (h = 1; h <= len; h++) {
		if (citations[len - h] < h) break;
		else answer = h;
	}
	
	return answer;
}