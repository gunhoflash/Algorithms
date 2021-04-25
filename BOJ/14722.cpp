#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define STRAWBERRY 0
#define CHOCOLATE 1
#define BANANA 2

#define max3(a, b, c) max(a, max(b, c))

#define plus_or_0(n) (n ? n + 1 : 0)

#define maximize_acc(r, c, m, acc) \
	m[r][c].acc = max3(m[r][c].acc, m[r][c - 1].acc, m[r - 1][c].acc) \

#define update_acc(r, c, m, acc, acc_before) \
	m[r][c].acc = max3(m[r][c].acc, plus_or_0(m[r][c - 1].acc_before), plus_or_0(m[r - 1][c].acc_before)) \

struct MilkStation {
	int milk;

	// accumulation of milks after visiting here with need of specific milk
	int acc_strawberry = 0;
	int acc_chocolate = 0;
	int acc_banana = 0;
};

int main(void) {
	int N;

	vector<vector<MilkStation>> milk_city;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// init all milk stations
	cin >> N;
	milk_city.resize(N + 1, vector<MilkStation>(N + 1));
	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			cin >> milk_city[r][c].milk;
		}
	}

	for (int r = 1; r <= N; r++) {
		for (int c = 1; c <= N; c++) {
			switch (milk_city[r][c].milk) {
				case STRAWBERRY:
				update_acc(r, c, milk_city, acc_strawberry, acc_banana);
				milk_city[r][c].acc_strawberry = max(milk_city[r][c].acc_strawberry, 1);
				break;

				case CHOCOLATE:
				update_acc(r, c, milk_city, acc_chocolate, acc_strawberry);
				break;

				case BANANA:
				update_acc(r, c, milk_city, acc_banana, acc_chocolate);
				break;
			}

			maximize_acc(r, c, milk_city, acc_strawberry);
			maximize_acc(r, c, milk_city, acc_chocolate);
			maximize_acc(r, c, milk_city, acc_banana);
		}
	}

	cout << max3(milk_city[N][N].acc_banana, milk_city[N][N].acc_chocolate, milk_city[N][N].acc_strawberry);

	return 0;
}