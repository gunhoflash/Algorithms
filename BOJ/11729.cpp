#include <iostream>

using namespace std;

void hanoi(int n, int from, int through, int to)
{
	if (n == 1)
		cout << from << ' ' << to << '\n';
	else
	{
		hanoi(n - 1, from, to, through);
		hanoi(1, from, through, to);
		hanoi(n - 1, through, from, to);
	}
}

int main()
{
	int N;

	cin >> N;
	cout << (1 << N) - 1 << '\n';

	hanoi(N, 1, 2, 3);

	return 0;
}