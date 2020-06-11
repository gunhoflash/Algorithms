#include <vector>
#include <algorithm>

using namespace std;

bool cmp_jobs(vector<int> a, vector<int> b) {
	return a[0] > b[0];
}

bool cmp_heap(vector<int> a, vector<int> b) {
	return a[1] > b[1];
}

int solution(vector<vector<int>> jobs) {
	int time, n_jobs, n_handled, answer = 0;
	vector<int> temp_job;
	vector<vector<int>> waits;

	sort(jobs.begin(), jobs.end(), cmp_jobs);
	make_heap(waits.begin(), waits.end(), cmp_heap);

	time = 0;
	n_jobs = jobs.size();
	n_handled = 0;

	// loop until all jobs are handled
	while (n_handled < n_jobs) {

		// get job-requests
		while (!jobs.empty()) {
			temp_job = jobs.back();
			if (temp_job[0] <= time) {
				// push the job to heap
				waits.push_back(temp_job);
				push_heap(waits.begin(), waits.end(), cmp_heap);
				jobs.pop_back();
			} else break;
		}

		if (!waits.empty()) {
			// handle the shortest job
			pop_heap(waits.begin(), waits.end(), cmp_heap);
			temp_job = waits.back();
			waits.pop_back();
			answer += time - temp_job[0] + temp_job[1];
			time += temp_job[1];
			n_handled++;
		} else {
			// no jobs to be handled
			time++;
		}
	}

	return answer / n_jobs;
}