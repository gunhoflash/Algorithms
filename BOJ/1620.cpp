#include <iostream>
#include <map>
#include <string>

using namespace std;

int main(void) {
	int N, M, i;
	string name, number;
	map<string, string> name_to_number;
	map<string, string> number_to_name;
	map<string, string>::iterator it;

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> N >> M;

	// make the pokemon book
	for (i = 0; i < N; i++) {
		cin >> name;
		number = to_string(i + 1);
		name_to_number[name] = number;
		number_to_name[number] = name;
	}

	// answer the questions
	while (M--) {
		cin >> name;
		it = name_to_number.find(name);
		if (it != name_to_number.end()) {
			cout << it->second << endl;
		} else {
			cout << number_to_name[name] << endl;
		}
	}

	return 0;
}