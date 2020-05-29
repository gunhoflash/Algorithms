#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

int solution(vector<int> weight)
{
	map<int, int> possibles;
	int i, t, w, found_max;

	// sort desc. order
	sort(weight.begin(), weight.end());

	i = 0;
	found_max = 1;
	for (auto itr = weight.begin(); itr != weight.end(); itr++)
	{
		w = *itr;

		for (auto it = possibles.begin(); it != possibles.end(); it++)
		{
			t = it->first + w;
			if (it->second != i)
			{
				if (possibles.find(t) == possibles.end())
				{
					possibles.insert({ t, i });
					found_max = (found_max < t ? t : found_max);
				}
			}
		}

		if (possibles.find(w) == possibles.end())
		{
			possibles.insert({ w, i });
			found_max = (found_max < w ? w : found_max);
		}
		i++;
	}

	for (t = 1; t < found_max; t++)
	{
		if (possibles.find(t) == possibles.end())
		{
			return t;
		}
	}
	return found_max + 1;
}