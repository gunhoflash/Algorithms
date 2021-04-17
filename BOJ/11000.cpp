#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Lecture {
	int start;
	int end;
};

bool compare_lecture(const Lecture &a, const Lecture &b) {
	return a.start < b.start;
}

int main(void) {
	int N;
	vector<Lecture> lectures;
	priority_queue<int, vector<int>, greater<int>> end_of_classrooms;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N;

	// init all lectures
	lectures.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> lectures[i].start >> lectures[i].end;
	}

	// sort in order of start
	sort(lectures.begin(), lectures.end(), compare_lecture);

	end_of_classrooms.push(0);
	for (int i = 0; i < N; i++) {
		if (lectures[i].start >= end_of_classrooms.top()) {
			end_of_classrooms.pop();
		}
		end_of_classrooms.push(lectures[i].end);
	}

	// print the number of classrooms
	cout << end_of_classrooms.size();

	return 0;
}