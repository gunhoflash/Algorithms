#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	vector<int> answer;

	vector<int> deploy;
	int i, d, f, len = progresses.size();

	deploy.push_back(0);
	for (i = 0; i < len; i++) {
		d = (100 - progresses[i] + speeds[i] - 1) / speeds[i];
		deploy.push_back(
			d < deploy[i] ? deploy[i] : d
		);
	}

	d = deploy[1];
	f = 0;
	for (i = 1; i <= len; i++) {
		if (deploy[i] != d) {
			d = deploy[i];
			answer.push_back(f);
			f = 1;
		} else f++;
	}
	answer.push_back(f);

	return answer;
}