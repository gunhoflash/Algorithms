#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Field {
	int x;
	int y;
	Field *representative_field;
};

struct Pipe {
	int length;
	Field *from;
	Field *to;
};

bool compare_pipe(const Pipe &a, const Pipe &b) {
	return a.length < b.length;
}

int get_square_length(const Field &a, const Field &b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

Field *find_representative_field(Field *field) {
	Field *representative_field = field->representative_field;

	if (representative_field != field) {
		representative_field = find_representative_field(representative_field);
	}

	return representative_field;
}

bool try_union_representative_field(Field *a, Field *b) {
	Field *representative_field_a = find_representative_field(a);
	Field *representative_field_b = find_representative_field(b);

	if (representative_field_a != representative_field_b) {
		representative_field_b->representative_field = representative_field_a;
		return true;
	}

	return false;
}

int main(void) {
	int
		N, C,
		n_pipes, n_pipes_selected,
		total_cost;

	vector<Field> fields;
	vector<Pipe> pipes;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> C;

	// set all fields
	fields.resize(N);
	for (int i = 0; i < N; i++) {
		cin >> fields[i].x >> fields[i].y;
		fields[i].representative_field = &fields[i];
	}

	// set all pipes
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			// calculate length of pipe
			int length = get_square_length(fields[i], fields[j]);
			if (length < C) continue;

			// acceptable pipe
			pipes.push_back({ length, &fields[i], &fields[j] });
		}
	}

	// sort all pipes in order of length
	sort(pipes.begin(), pipes.end(), compare_pipe);

	// select pipes
	total_cost = 0;
	n_pipes = pipes.size();
	n_pipes_selected = 0;
	for (int i = 0; i < n_pipes; i++) {
		int length = pipes[i].length;

		if (try_union_representative_field(pipes[i].from, pipes[i].to)) {
			// pipe installed
			n_pipes_selected++;
			total_cost += length;
			if (n_pipes_selected == N - 1) break;
		}
	}

	// print the answer
	cout << (n_pipes_selected == N - 1 ? total_cost : -1);

	return 0;
}