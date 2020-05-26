#include<stdio.h>
int merge_temp[299999];

void merge_sort(int list[], int length)
{
	int left, right, i;

	if (length < 2) return;

	merge_sort(list, length / 2);
	merge_sort(list + length / 2, length - length / 2);

	i = 0;
	left = 0;
	right = length / 2;
	while (left < length / 2 && right < length)
		merge_temp[i++] = (list[left] < list[right]) ? list[left++] : list[right++];
	while (left < length / 2)
		merge_temp[i++] = list[left++];
	while (right < length)
		merge_temp[i++] = list[right++];

	while (--i >= 0)
		list[i] = merge_temp[i];
}

int main()
{
	int i, N, K, prev, next, cost;
	int gap[299999];

	// get data and save gaps which are the height differences between each student pair
	scanf("%d%d", &N, &K);
	scanf("%d", &prev);
	for (i = 0; i < N - 1; i++)
	{
		scanf("%d", &next);
		gap[i] = next - prev;
		prev = next;
	}

	// sort gap
	merge_sort(gap, N - 1);

	K = N - K;
	i = 0;
	cost = 0;

	// add cost
	while (K > 0)
	{
		K--;
		cost += gap[i++];
	}

	// print the total cost
	printf("%d", cost);
}