#include <iostream>

using namespace std;

#define RECURSIVE_MAX 7
#define STUDENT_SIZE 5
#define MIN_S 4

char students[STUDENT_SIZE + 1][STUDENT_SIZE + 1] = { 0 };
char students_archived[STUDENT_SIZE + 1][STUDENT_SIZE + 1] = { 0 };
int global_ns = 0;

int get_number_of_cases(int r, int c, int ns, int recursive) {
	int i, j, answer;

	if (students[r][c] > RECURSIVE_MAX * 2) {
		if (students[r][c] == 'S') ns++;
		students[r][c] = recursive;
	}

	answer = 0;
	if (recursive == RECURSIVE_MAX) {
		// end of searching
		if (ns >= MIN_S)
			answer = 1;
	} else if (RECURSIVE_MAX - recursive >= MIN_S - ns) {
		// need more searching
		for (i = 1; i <= STUDENT_SIZE; i++) {
			for (j = 1; j <= STUDENT_SIZE; j++) {
				if (students[i][j] > RECURSIVE_MAX * 2) {
					if ((students[i - 1][j] != 0 && students[i - 1][j] <= recursive) ||
						(students[i + 1][j] != 0 && students[i + 1][j] <= recursive) ||
						(students[i][j - 1] != 0 && students[i][j - 1] <= recursive) ||
						(students[i][j + 1] != 0 && students[i][j + 1] <= recursive)) {
						if (students[i][j] == 'S') ns++;
						students[i][j] = recursive;
						answer += get_number_of_cases(i, j, ns, recursive + 1);
						students[i][j] += RECURSIVE_MAX;
						if (students_archived[i][j] == 'S') ns--;
					}
				}
			}
		}
	}

	// rollback
	for (i = 1; i <= STUDENT_SIZE; i++) {
		for (j = 1; j <= STUDENT_SIZE; j++) {
			if (students[i][j] == recursive || students[i][j] == RECURSIVE_MAX + recursive) {
				students[i][j] = students_archived[i][j];
			}
		}
	}

	return answer;
}

int main(void) {
	int i, j, answer;
	char c;

	// get student data
	for (i = 1; i <= STUDENT_SIZE; i++) {
		for (j = 1; j <= STUDENT_SIZE; j++) {
			do {
				cin >> c;
			} while (c != 'Y' && c != 'S');
			if (c == 'S') global_ns++;
			students[i][j] = students_archived[i][j] = c;
		}
	}

	// count answer
	answer = 0;
	for (i = 1; i <= STUDENT_SIZE; i++) {
		for (j = 1; j <= STUDENT_SIZE; j++) {

			// start only from 'S'
			if (students[i][j] != 'S') continue;

			// search from [i][j]
			answer += get_number_of_cases(i, j, 0, 1);

			// delete [i][j]
			students[i][j] = 0;

			// check early-stoppable
			global_ns--;
			if (global_ns < MIN_S) break;
		}
		if (global_ns < MIN_S) break;
	}

	cout << answer;

	return 0;
}