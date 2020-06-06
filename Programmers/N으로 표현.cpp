#include <vector>

#define MAX_NUMBER 32000
#define MAX_COUNT 8

using namespace std;

int ar[MAX_NUMBER + 1];
vector<vector<int>> ar_n(MAX_COUNT + 1, vector<int>(0));

// update ar when lower count found
void update_ar(int n, int count) {
	if (n > MAX_NUMBER) return;
	if (ar[n] <= count) return;

	ar[n] = count;
	ar_n[count].push_back(n);
}

void calculate_2_ar(int n1, int n2) {
	int i, j, a, b, c,
		count = n1 + n2,
		len1 = ar_n[n1].size(),
		len2 = ar_n[n2].size();

	for (i = 0; i < len1; i++) {
		a = ar_n[n1][i];
		for (j = 0; j < len2; j++) {
			b = ar_n[n2][j];
			
			// b > c
			if (b > a) {
				c = a;
			} else {
				c = b;
				b = a;
			}
			if (c == 0) continue;

			update_ar(b + c, count);
			update_ar(b - c, count);
			update_ar(b * c, count);
			update_ar(b / c, count);
		}
	}
}

int solution(int N, int number) {
	int i, j;

	// init ar
	ar[0] = 0;
	for (i = 1; i < MAX_NUMBER + 1; i++) {
		ar[i] = MAX_COUNT + 1;
	}

	// update N, NN, NNN, ...
	i = 1;
	j = N;
	while (i <= MAX_COUNT) {
		update_ar(j, i);
		j = j * 10 + N;
		i++;
	}

	// calculate each count starting from 2
	for (i = 2; i < MAX_COUNT + 1; i++) {
		for (j = 1; j <= i / 2; j++) {
			calculate_2_ar(j, i - j);

			// fast return
			if (ar[number] <= MAX_COUNT) return ar[number];
		}
	}

	return -1;
}