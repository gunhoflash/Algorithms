#include<stdio.h>

int main()
{
	int nanjangs[9] = { 0 };
	int i, j, over_sum;

	// get heights and calculate the over
	over_sum = 0;
	for (i = 0; i < 9; i++)
	{
		scanf("%d", nanjangs + i);
		over_sum += nanjangs[i];
	}
	over_sum -= 100;

	// find 2 fake nanjangs and set their heights as 0
	for (i = 0; i < 9; i++)
	{
		if (nanjangs[i] >= over_sum) continue;
		for (j = i + 1; j < 9; j++)
		{
			if (nanjangs[i] + nanjangs[j] == over_sum)
			{
				nanjangs[i] = nanjangs[j] = over_sum = 0;
				break;
			}
		}
	}

	// bubble sort ;)
	for (i = 8; i > 0; i--)
		for (j = 0; j < i; j++)
		{
			if (nanjangs[j] > nanjangs[j + 1])
			{
				over_sum = nanjangs[j];
				nanjangs[j] = nanjangs[j + 1];
				nanjangs[j + 1] = over_sum;
			}
		}

	// print heights
	for (i = 2; i < 9; i++)
		printf("%d\n", nanjangs[i]);
}