#include <iostream>
#include <map>
#include <set>

using namespace std;

int main(void) {
	int N, M;
	map<string, set<string>> group_to_member;
	map<string, string> member_to_group;

	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> M;
	while (N--) {
		int n_member;
		string group_name, member_name;
		set<string> group_mambers;

		// get group info
		cin >> group_name >> n_member;

		// get all members
		while (n_member--) {
			cin >> member_name;
			group_mambers.insert(member_name);
			member_to_group.insert({ member_name, group_name });
		}

		// save the group
		group_to_member.insert({ group_name, group_mambers });
	}

	while (M--) {
		int type_of_question;
		string name;
		cin >> name >> type_of_question;

		if (type_of_question == 0) {
			// print all members
			for (string member_name : group_to_member[name]) {
				cout << member_name << '\n';
			}
		} else {
			// print group name
			cout << member_to_group[name] << '\n';
		}
	}

	return 0;
}