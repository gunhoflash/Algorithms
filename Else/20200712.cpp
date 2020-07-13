/*

#문제 설명

0 ~ 9 까지 정수를 가진 배열 numbers가 주어집니다.
배열 numbers가 매개변수로 주어질 때, numbers에 있는
자연수에 부호(+, -)를 붙여 전체 합이 0으로 되는 가지
수를 return 하도록 solution 함수를 완성해주세요.

#제한사항

- 배열 numbers의 원소 개수는 100개 이하의 자연수입니다.
- 배열 안에 있는 정수는 0 이상 9 이하입니다.
- 정답이 커질 수 있으므로 마지막 5자리만 return 해주세요.

#입출력 예
numbers: [1, 1, 1, 1]
result: 6
numbers: [8, 3, 5, 7, 3, 4]
result: 6

*/

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

#define MOD 100000

void generate_next_numbers(int n, map<int, int> before, map<int, int> &after) {
	map<int, int>::iterator it_after;
	int key, value;
	for (auto p : before) {
		key = p.first;
		value = p.second;

		// key + n
		it_after = after.find(key + n);
		if (it_after == after.end()) {
			// new key
			after.insert({ key + n, value });
		} else {
			// exist key
			it_after->second = (it_after->second + value) % MOD;
		}

		// key - n
		if (key - n >= 0) {
			it_after = after.find(key - n);
			if (it_after == after.end()) {
				// new key
				after.insert({ key - n, value });
			} else {
				// exist key
				it_after->second = (it_after->second + value) % MOD;
			}
		}
	}
}

int solution(vector<int> numbers) {
	vector<map<int, int>> possibles(2, map<int, int>());
	map<int, int>::iterator it_after;

	int i, size, i_before, answer, number_of_0 = 0;

	// sort by descending order and delete all 0
	sort(numbers.begin(), numbers.end(), greater<int>());
	while (!numbers.empty() && numbers.back() == 0) {
		numbers.pop_back();
		number_of_0++;
	}

	// init variables
	i_before = 0;
	size = numbers.size();

	// take the first number
	possibles[0][numbers[0]] = 1;

	for (i = 1; i < size; i++) {
		// config 'after'
		generate_next_numbers(numbers[i], possibles[i_before], possibles[1 - i_before]);

		// double zero
		it_after = possibles[1 - i_before].find(0);
		if (it_after != possibles[1 - i_before].end()) {
			it_after->second = (it_after->second * 2) % MOD;
		}

		// clear 'before'
		possibles[i_before].clear();

		// switch
		i_before = 1 - i_before;
	}

	it_after = possibles[i_before].find(0);
	if (it_after == possibles[i_before].end()) {
		// zero not found
		return 0;
	} else {
		// zero found
		answer = it_after->second % MOD;
		while (number_of_0--) answer = (answer * 2) % MOD;
		return answer;
	}
}

/*
	test the function: solution
*/
int main(void) {
	cout << 6 << " == " << solution({ 1, 1, 1, 1 }) << endl;
	cout << 6 << " == " << solution({ 8, 3, 5, 7, 3, 4 }) << endl;
	cout << 2 << " == " << solution({ 1, 1, 2, 4, 8 }) << endl;

	cout <<     2 << " == " << solution({ 0 }) << endl;
	cout <<     4 << " == " << solution({ 0, 0 }) << endl;
	cout <<     8 << " == " << solution({ 0, 0, 0 }) << endl;
	cout <<    32 << " == " << solution({ 0, 0, 0, 0, 0 }) << endl;
	cout << 65536 << " == " << solution({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }) << endl;
	cout << 31072 << " == " << solution({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }) << endl;
	cout << 41824 << " == " << solution({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }) << endl;
	cout << 42624 << " == " << solution({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }) << endl;

	cout << 56276 << " == " << solution({ 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8, 1, 1, 2, 4, 8 }) << endl;

	cout <<    20 << " == " << solution({ 1, 1, 1, 1, 1, 1 }) << endl;
	cout <<    70 << " == " << solution({ 1, 1, 1, 1, 1, 1, 1, 1 }) << endl;
	cout <<   252 << " == " << solution({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }) << endl;
	cout <<     0 << " == " << solution({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 }) << endl;
	cout <<   924 << " == " << solution({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }) << endl;
	cout << 84756 << " == " << solution({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }) << endl;
	cout << 97256 << " == " << solution({ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }) << endl;
	return 0;
}