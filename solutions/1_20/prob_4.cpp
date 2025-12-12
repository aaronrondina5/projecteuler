#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

using u_ll = unsigned long long;
using u_int = unsigned int;

u_ll reverse(const u_ll val) {
	u_ll res = 0;
	u_ll x = val;
	while (x > 0) {
		res = (res * 10) + (x % 10);
		x /= 10;
	}
	return res;
}

bool is_palindromic_number(const u_ll val) {
	if (val < 0) {
		return false;
	}
	return val == reverse(val);
}

/**
 * thought about how to not do the following for a while
 * this seems okay - we aren't duplicating checks by making sure y <= x
 * was thinking of some way of using priority queues to make sure we always
 * get the highest product next, but it would probably be overkill
 */
u_ll largest_palindromic_with_loop() {
	u_ll res = -1;
	for (u_ll x = 999; x > 99; --x) {
		// Start at x to avoid duplicating checks
		for (u_ll y = x; y > 99; --y) {
			if (is_palindromic_number(x * y)) {
				res = max(res, x * y);
			}
		}
	}
	return res;
}

int solve(vector<string>& input) {
	u_ll result = largest_palindromic_with_loop();
	cout << "largest_palindromic_with_loop=" << result << "\n";
	return 0;
}

void get_input_as_vector(vector<string>& input) {
	string line;
	while (getline(cin, line)) {
		input.push_back(line);
	}
}

int main() {
	vector<string> input;
	get_input_as_vector(input);

	if (0 != solve(input)) {
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
