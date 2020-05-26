#include<stdio.h>
/*
	1자리: 10개
	2자리: 55개: 10 + 9 + 8 + 7 + 6 + ... + 2 + 1
	3자리: 220개: 55 + 45 + 36 + ... + 3 + 1
	4자리: 220 + ..

	N자리: (N-1자리) + (N-1자리 - N-2자리) + (N-1자리 - N-2자리 - N-3자리) + ...
	= 10 * (N-1자리) - 9 * (N-2자리) - 8 * ... - 2 * (N-9자리) - (N-10자리)
*/
int main()
{
	int N[1000][9] = { 0 };
	int i, j, temp_sum, n;
	int *prev, *now;

	for (i = 0; i < 9; i++)
	{
		N[0][i] = 1;
		N[1][i] = 10 - i;
	}

	for (i = 2; i < 1000; i++)
	{
		temp_sum = 1;
		prev = N[i - 1];
		now = N[i];
		for (j = 8; j >= 0; j--)
		{
			temp_sum += prev[j] % 10007;
			now[j] = temp_sum;
		}
	}

	scanf("%d", &n);

	temp_sum = 1;
	for (j = 0; j < 9; j++)
	{
		temp_sum += N[n - 1][j];
	}
	printf("%d", temp_sum % 10007);
}