int solution(int n) {
	int answer = 0;
	int k, s;

	k = 1;
	s = 0;
	while (true) {
		if (n <= s) break;
		if ((n - s) % k == 0) {
			answer++;
		}
		s += k;
		k++;
	}

	return answer;
}