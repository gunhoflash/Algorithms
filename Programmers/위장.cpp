#include <map>
#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<string>> clothes) {
	map<string, int> n_clothes_types;
	map<string, int>::iterator it_n_clothes_types;
	string clothes_type;
	int i, answer, size;

	// read all clothes and count the number of each type
	size = clothes.size();
	for (i = 0; i < size; i++) {
		// check type of clothes
		clothes_type = clothes[i][1];
		if (n_clothes_types.find(clothes_type) == n_clothes_types.end()) {
			// new type
			n_clothes_types.insert(make_pair(clothes_type, 1));
		} else {
			// not a new type
			n_clothes_types.find(clothes_type)->second++;
		}
	}

	// populate number of clothes for each type
    answer = 1;
	for (it_n_clothes_types = n_clothes_types.begin(); it_n_clothes_types != n_clothes_types.end(); it_n_clothes_types++) {
		answer *= it_n_clothes_types->second + 1;
	}

	return answer - 1;
}