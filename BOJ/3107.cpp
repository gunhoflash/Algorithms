#include <iostream>
#include <string>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	// get IPv6 address
	string IPv6_address;
	cin >> IPv6_address;

	// prepend 0
	IPv6_address = "0" + IPv6_address;

	// append 0: or :
	if (IPv6_address[IPv6_address.length() - 1] == ':')
		IPv6_address += "0";
	IPv6_address += ":";

	// count the number of shown/hidden groups
	int n_shown_groups = 0;
	bool is_group_found = false;
	for (char c : IPv6_address) {
		if (c == ':') {
			if (is_group_found) {
				n_shown_groups++;
			}
			is_group_found = false;
		} else {
			is_group_found = true;
		}
	}

	// revert all groups
	int len_address = IPv6_address.length();
	int n_hidden_groups = 8 - n_shown_groups;
	string full_IPv6_address = "";
	string group = "";
	for (int i = 0 ; i < len_address; i++) {
		char c = IPv6_address[i];

		if (c != ':') {
			group += c;
			continue;
		}

		if (group.length()) {
			// revert a group
			full_IPv6_address += ("0000" + group + ":").substr(group.length());
			group.clear();
		}

		// revert all hidden groups
		if (i < len_address - 1 && IPv6_address[i + 1] == ':') {
			while (n_hidden_groups > 0) {
				full_IPv6_address += "0000:";
				n_hidden_groups--;
			}
		}
	}

	// print full-length IPv6 address
	cout << full_IPv6_address.substr(0, 39);

	return 0;
}