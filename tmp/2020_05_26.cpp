#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Request
{
	int d;
	int m;
};

struct cmpDdesc
{
	bool operator()(Request a, Request b)
	{
		return a.d < b.d;
	}
};
struct cmpMdesc
{
	bool operator()(Request a, Request b)
	{
		return a.m < b.m;
	}
};

int main()
{
	priority_queue<Request, vector<Request>, cmpDdesc> queue_remained;
	priority_queue<Request, vector<Request>, cmpMdesc> queue_candidate;
	int N, d, m, max_day = 0;

	cin >> N;
	while (N--)
	{
		cin >> m >> d;
		max_day = max_day > d ? max_day : d;
		queue_remained.push({ d, m });
	}

	m = 0;
	while (max_day > 0)
	{
		// from queue_remained to queue_candidate
		while (!queue_remained.empty())
		{
			d = queue_remained.top().d;
			if (d == max_day)
			{
				queue_candidate.push(queue_remained.top());
				queue_remained.pop();
			}
			else break;
		}

		// pop one
		if (!queue_candidate.empty())
		{
			m += queue_candidate.top().m;
			queue_candidate.pop();
		}
		max_day--;
	}

	cout << m << endl;
}