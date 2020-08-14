#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Job {
	int total_time;
	int sum_prev_jobs;
	int max_waiting_time;
	vector<int> next_jobs;
};

int main(void) {

	vector<Job> jobs;
	queue<int> job_ready_queue;

	int
		i, j, k, // indexer
		size, // size of a vector
		N, // the number of jobs
		n_prevs, prev, sum_prev,
		max_total_time;

	// get data
	cin >> N;
	jobs.resize(N + 1, Job()); // index 0 is nothing
	for (i = 1; i <= N; i++) {
		cin >> jobs[i].total_time;

		cin >> n_prevs;
		sum_prev = 0;
		if (n_prevs == 0) {
			job_ready_queue.push(i);
		} else {
			while (n_prevs--) {
				cin >> prev;
				jobs[prev].next_jobs.push_back(i);
				sum_prev += prev;
			}
		}
		jobs[i].sum_prev_jobs = sum_prev;

		jobs[i].max_waiting_time = 0;
	}

	max_total_time = 0;
	while (!job_ready_queue.empty()) {
		// pop one
		i = job_ready_queue.front();
		job_ready_queue.pop();

		// update total time to fulfill
		jobs[i].total_time += jobs[i].max_waiting_time;

		size = jobs[i].next_jobs.size();
		if (size == 0) {
			// no more next jobs
			// this job can have the longest waiting time
			if (max_total_time < jobs[i].total_time) {
				max_total_time = jobs[i].total_time;
			}
		} else {
			// check for next jobs
			for (j = 0; j < size; j++) {
				k = jobs[i].next_jobs[j];
				jobs[k].sum_prev_jobs -= i;

				// this job now can be done
				if (jobs[k].sum_prev_jobs == 0) {
					job_ready_queue.push(k);
				}

				// update maximum waiting time
				if (jobs[k].max_waiting_time < jobs[i].total_time) {
					jobs[k].max_waiting_time = jobs[i].total_time;
				}
			}
		}
	}

	cout << max_total_time;
	return 0;
}