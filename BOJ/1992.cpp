#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<char>> video;

string zip_video(int r, int c, int size) {
	int i, j;
	char first_data;

	first_data = video[r][c];
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (video[r + i][c + j] != first_data) {
				// not all same
				size /= 2;
				return "("
				+ zip_video(r,        c,        size)
				+ zip_video(r,        c + size, size)
				+ zip_video(r + size, c,        size)
				+ zip_video(r + size, c + size, size)
				+ ")";
			}
		}
	}

	// all same
	return string(1, first_data);
}

int main(void) {
	char data;
	int
		i, j, // indexers
		N; // size of paper

	// get data: N
	cin >> N;
	video.resize(N, vector<char>(N));

	// get video data
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			cin >> video[i][j];
		}
	}
	// classify
	cout << zip_video(0, 0, N);

	return 0;
}