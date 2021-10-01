#include <string>
#include <vector>

#define PUDDLE -1

using namespace std;

int solution(int M, int N, vector<vector<int>> puddles) {
	vector<vector<int>> matrix(M + 1, vector<int>(N + 1, 0));
	
	// init matrix
	matrix[0][1] = 1;
	for (vector<int> &puddle : puddles) {
		matrix[puddle[0]][puddle[1]] = PUDDLE;
	}
	
	// calculate matrix
	for (int m = 1; m <= M; m++) {
		for (int n = 1; n <= N; n++) {
			matrix[m][n] = matrix[m][n] == PUDDLE ? 0 : (matrix[m - 1][n] + matrix[m][n - 1]) % 1000000007;
		}
	}
	
	return matrix[M][N];
}