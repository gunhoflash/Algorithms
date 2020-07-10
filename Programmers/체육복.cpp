#include <algorithm>
#include <vector>

using namespace std;

int solution(int n, vector<int> lost, vector<int> reserve) {
	int i, n_success, n_lost, n_reserve, answer;

	int students_lost[31] = { 0 };
	int students_reserve[31] = { 0 };

	n_lost = lost.size();
	n_reserve = reserve.size();

	// init student lists
	for (i = 0; i < n_lost; i++) {
		students_lost[lost[i]] = 1;
	}
	for (i = 0; i < n_reserve; i++) {
		students_reserve[reserve[i]] = 1;
	}

	// delete what reserve but also lost
	for (i = 1; i <= n; i++) {
		if (students_lost[i] == 1 && students_reserve[i] == 1) {
			students_lost[i] = 0;
			students_reserve[i] = 0;
			n_lost--;
			n_reserve--;
		}
	}

	// repeat until it's likely to be possible 
	while (n_lost * n_reserve) {
		n_success = 0;

		// check all losts
		for (i = 1; i <= n; i++) {
			if (students_lost[i] == 0) continue;

			if (students_reserve[i - 1] != students_reserve[i + 1]) {
				students_reserve[i - 1] = students_reserve[i + 1] = 0;
				students_lost[i] = 0;
				n_lost--;
				n_reserve--;
				n_success++;
			}
		}

		// check all reserves
		for (i = 1; i <= n; i++) {
			if (students_reserve[i] == 0) continue;

			if (students_lost[i - 1] != students_lost[i + 1]) {
				students_lost[i - 1] = students_lost[i + 1] = 0;
				students_reserve[i] = 0;
				n_lost--;
				n_reserve--;
				n_success++;
			}
		}

		// if nothing changed, quit
		if (n_success == 0) break;
	}

	answer = n;
	for (i = 1; i <= n; i++) {
		answer -= students_lost[i];
	}

	return answer;
}