#include <stack>
#include <string>

using namespace std;

int solution(string s)
{
	stack<char> st;
	int i, c, len;

	for (i = 0, len = s.length(); i < len; i++) {
		c = s[i];
		if (st.empty() == false && st.top() == c) {
			st.pop();
		} else {
			st.push(c);
		}
	}

	return st.empty() ? 1 : 0;
}