// 참고: 예제 케이스는 통과하지만 결국 틀린 코드임
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int i, j, N, remained, element, sum;
	vector<int> numbers;

	cin >> N;

	sum = 0;
	for (i = 0; i < N; i++) {
		cin >> element;
		if (element == 0) {
			N--;
			i--;
		} else {
			sum += element % 3;
			numbers.push_back(element);
		}
	}

	if (sum == 0) {
		cout << "YES";
		return 0;
	} else if (sum % 3 != 0) {
		cout << "NO";
		return 0;
	}

	// sort numbers
	sort(numbers.begin(), numbers.end());

	for (i = 0; i < N; i++) {
		remained = numbers[i] % 3;
		if (remained == 0) continue;

		j = i + 1;
		if (j >= N) {
			cout << "NO";
			return 0;
		}

		if (remained == 1) {
			// remainder = 1
			while (j < N && numbers[j] < 2) j++;
			if (j >= N) {
				cout << "NO";
				return 0;
			}
			numbers[j] -= 2;
		} else {
			// remainder = 2
			while (j < N && numbers[j] < 1) j++;
			if (j >= N) {
				cout << "NO";
				return 0;
			}
			numbers[j]--;
		}
	}

	cout << "YES";
	return 0;
}