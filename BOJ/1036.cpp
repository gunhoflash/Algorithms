#include <algorithm>
#include <iostream>
#include <vector>

#define MAX_N36_LENGTH 52

using namespace std;

typedef char Number;

struct N36 {
	Number value[MAX_N36_LENGTH] = { 0 };
};

bool compare_profit(const N36 &a, const N36 &b) {
	for (int i = 0; i < MAX_N36_LENGTH; i++) {
		if (a.value[i] == b.value[i]) continue;
		return a.value[i] > b.value[i];
	}
	return false;
}

Number char_to_number(char n) {
	return (n < 'A') ? (n - '0') : (n - 'A' + 10);
}

char number_to_char(Number n) {
	return (n < 10) ? (n + '0') : (n + 'A' - 10);
}

void init_N36_from_string(N36 &n, string &n36_string) {
	int len = n36_string.length();
	for (int i = 0; i < len; i++) {
		n.value[MAX_N36_LENGTH - len + i] = char_to_number(n36_string[i]);
	}
}

void print_N36(N36 &n) {
	bool is_first_char_found = false;
	for (int i = 0; i < MAX_N36_LENGTH; i++) {
		// skip heading 0
		if (!is_first_char_found) {
			if (n.value[i]) {
				is_first_char_found = true;
			} else {
				continue;
			}
		}

		cout << number_to_char(n.value[i]);
	}

	// handle exception: the number is 0
	if (!is_first_char_found) {
		cout << '0';
	}
}

void add_N36_to_N36(N36 &to, const N36 &from) {
	Number sum, upper = 0;
	for (int i = MAX_N36_LENGTH - 1; i >= 0; i--) {
		sum = to.value[i] + from.value[i] + upper;
		upper = sum / 36;
		to.value[i] = sum % 36;
	}
}

N36 calculate_profit_from_conversion(const N36 &n, Number target) {
	N36 profit;
	Number gap = 35 - target;

	bool is_first_char_found = false;
	for (int i = 0; i < MAX_N36_LENGTH; i++) {
		// skip heading 0
		if (!is_first_char_found) {
			if (n.value[i]) {
				is_first_char_found = true;
			} else {
				continue;
			}
		}

		if (n.value[i] == target) {
			// add gap
			profit.value[i] = gap;
		}
	}

	// handle exception: the number is 0
	if (!is_first_char_found && target == 0) {
		profit.value[MAX_N36_LENGTH - 1] = gap;
	}

	return profit;
}

int main(void) {
	int N, K;
	vector<N36> n36_list, profits;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get all numbers
	cin >> N;
	n36_list.resize(N);
	for (int i = 0; i < N; i++) {
		// get number as string
		string n36_string;
		cin >> n36_string;

		// convert string to N36
		init_N36_from_string(n36_list[i], n36_string);
	}

	// calculate all profits for each target
	profits.resize(36);
	for (Number target = 0; target < 36; target++) {
		for (int i = 0; i < N; i++) {
			add_N36_to_N36(profits[target], calculate_profit_from_conversion(n36_list[i], target));
		}
	}

	// sort profits
	sort(profits.begin(), profits.end(), compare_profit);

	// select most largest profits and calculate sum of profits
	cin >> K;
	N36 profit_sum;
	for (int i = 0; i < K; i++) {
		add_N36_to_N36(profit_sum, profits[i]);
	}

	// add all original numbers to the sum of profits
	for (int i = 0; i < N; i++) {
		add_N36_to_N36(profit_sum, n36_list[i]);
	}

	// print answer
	print_N36(profit_sum);

	return 0;
}
