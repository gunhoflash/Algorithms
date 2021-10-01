// 부동소수점과 테스트케이스의 우연 덕분에 정답 처리된 비효율적인 코드
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct ImmigrationOfficer {
	long long next_end_time;
	long long immigration_time;
};

bool compare_officer(const ImmigrationOfficer &a, const ImmigrationOfficer &b) {
	return a.next_end_time > b.next_end_time;
}

long long solution(int n, vector<int> times) {
	long long max_end_time = 0;
	int n_times = times.size();
	int sum_bulk = 0;
	long double sum_rate = 0;

	vector<ImmigrationOfficer> heap;

	// init the heap
	for (int i = 0; i < n_times; i++) {
		sum_rate += 1.0 / times[i];
	}
	for (int i = 0; i < n_times; i++) {
		long long immigration_time = times[i];
		int bulk = max((int)(n * ((1.0 / immigration_time) / sum_rate)) - 1, 0);
		sum_bulk += bulk;

		long long next_end_time = (bulk + 1) * immigration_time;
		max_end_time = max(max_end_time, next_end_time - immigration_time);

		heap.emplace_back(ImmigrationOfficer{next_end_time, immigration_time});
	}
	make_heap(heap.begin(), heap.end(), compare_officer);

	// do the job
	n -= sum_bulk;
	while (n > 0) {
		// pop the officer
		ImmigrationOfficer &officer = heap.front();
		long long next_end_time = officer.next_end_time;
		long long immigration_time = officer.immigration_time;
		pop_heap(heap.begin(), heap.end(), compare_officer);
		heap.pop_back();

		int bulk = (max(max_end_time, next_end_time) - (next_end_time - immigration_time)) / immigration_time;
		next_end_time += bulk * immigration_time;
		max_end_time = max(max_end_time, next_end_time - immigration_time);
		n -= bulk;

		// push the officer
		heap.emplace_back(ImmigrationOfficer{next_end_time, immigration_time});
		push_heap(heap.begin(), heap.end(), compare_officer);
	}

	// return the result
	return max_end_time;
}
