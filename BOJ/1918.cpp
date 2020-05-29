#include <iostream>
#include <string>
#include <stack>

using namespace std;

string f(string A, string O, string B) {
	return A + B + O;
}

void check(stack<string> *alphabets, stack<string> *operators) {
	bool checked;
	string cs, a, o, b;

	while (true) {
		checked = false;
		cs = alphabets->top();
		alphabets->pop();
		if (!operators->empty() && !alphabets->empty()) {
			o = operators->top();
			if (o == "*" || o == "/") {
				operators->pop();
				b = alphabets->top(); alphabets->pop();
				alphabets->push(f(b, o, cs));
				checked = true;
			}
		}
		if (!checked) {
			alphabets->push(cs);
			return;
		}
	}
}

int main() {
	stack<string> alphabets;
	stack<string> operators;

	string cs, input, a, o, b;
	int i, len;
	char c;

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
					alphabets.pop(); operators.pop();
				}
				cs = alphabets.top() + cs; alphabets.pop();
				alphabets.push(cs);
				operators.pop();
				check(&alphabets, &operators);
				break;

			default:
				alphabets.push(cs);
				check(&alphabets, &operators);
				break;
		}
	}

	cout << alphabets.top();
}