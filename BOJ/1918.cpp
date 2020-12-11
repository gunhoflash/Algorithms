#include <iostream>
#include <string>
#include <stack>

using namespace std;

string f(const string &A, const string &O, const string &B) {
	return A + B + O;
}

void check(stack<string> &alphabets, stack<string> &operators) {
	bool checked;
	string cs, o, b;

	checked = true;
	while (checked) {
		checked = false;
		cs = alphabets.top();
		alphabets.pop();
		if (!operators.empty() && !alphabets.empty()) {
			o = operators.top();
			if (o == "*" || o == "/") {
				operators.pop();
				b = alphabets.top();
				alphabets.pop();
				alphabets.push(f(b, o, cs));
				checked = true;
			}
		}
	}

	alphabets.push(cs);
}

int main() {
	stack<string>
		alphabets,
		operators;

	string cs, input;
	int i, len;
	char c;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> input;
	input = "(" + input + ")";
	len = input.length();

	for (i = 0; i < len; i++) {
		cs = c = input[i];

		switch (c) {
			case '+':
			case '-':
			case '*':
			case '/':
			case '(':
				operators.push(cs);
				break;

			case ')':
				cs = "";
				while (operators.top() != "(") {
					cs = alphabets.top() + operators.top() + cs;
					alphabets.pop();
					operators.pop();
				}
				cs = alphabets.top() + cs; alphabets.pop();
				operators.pop();
			default:
				alphabets.push(cs);
				check(alphabets, operators);
				break;
		}
	}

	cout << alphabets.top();
}