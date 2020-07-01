#include <string>
#include <vector>

#define min(a, b) (a > b ? b : a)
#define max(a, b) (a > b ? a : b)

using namespace std;

/*
	Return the number of operations to set a character from 'A'.
	Examples:
		get_count_char('A') = 0
		get_count_char('D') = 3
		get_count_char('M') = 12
		get_count_char('N') = 13
		get_count_char('O') = 12
		p 11
		q 10
		r 9
		s 8
		t 7
		u 6
		v 5
		w 4
		x 3
		y 2
		get_count_char('Z') = 1
*/
int get_count_char(char c) {
	if (c <= 'N')
		return c - 'A';
	else
		return 'Z' - c + 1;
}

int solution(string name) {
	int answer, i, count, gap, max_gap, max_gap_start, str_len = name.length();
	vector<pair<int, int>> counts;

	// count for each character
	max_gap = 0;
	for (i = 0; i < str_len; i++) {
		count = get_count_char(name[i]);
		if (count > 0) {
			counts.push_back(make_pair(i, count));
			if (counts.size() > 0) {
				gap = i - counts[counts.size() - 2].first;
				if (gap > max_gap) {
					max_gap = gap;
					max_gap_start = i - gap;
				}
			}
		}
	}

	if (counts.size() == 0) {
        // no character changing needed, all is 'A'
		answer = 0;
	} else if (counts.size() == 1) {
        // only one character is not 'A'
		answer = min(counts.front().first, str_len - counts.front().first);
	} else {
        // some characters are not 'A'

		// go left
		if (counts.front().first > 0)
			answer = str_len - counts.front().first;
		else
			answer = str_len - counts[1].first;

		// go right
		answer = min(answer, counts.back().first);

		// go min gap
		answer = min(answer, str_len - max_gap + min(max_gap_start, str_len - (max_gap_start + max_gap)));
	}

    // sum counts for all each character
	for (i = 0; i < counts.size(); i++) {
		answer += counts[i].second;
	}

	return answer;
}
