#include <algorithm>
#include <iostream>

using namespace std;

#define for_nm(n, m, N, M) for (int n = 0; n < N; n++) for (int m = 0; m < M; m++) 

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m, N, M;
	cin >> N >> M;

	int arr[N][M];
	for_nm(n, m, N, M) {
		char c;
		cin >> c;
		arr[n][m] = c - '0';
	}

	// find maximum size of square that all corner values are same
	int max_size = 0;
	for_nm(n, m, N, M) {
		int size = 1;
		int v = arr[n][m];
		while (n + size < N && m + size < M) {
			if (arr[n][m + size] == v && arr[n + size][m] == v && arr[n + size][m + size] == v) {
				max_size = max(max_size, size);
			}
			size++;
		}
	}

	cout << (max_size + 1) * (max_size + 1);
}
