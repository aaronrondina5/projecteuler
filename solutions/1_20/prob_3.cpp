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

/**
 * idea is to start a low prime numbers and move up
 * if you divide prime factor as many times as you can, then you dont have to
 * worry about hitting non-primes later
 * ie, you would never be able to divide by 9 if you had already divided all
 * the 3s out of the number
 *
 * you don't have to go higher than the sqrt(input) because that cant possibly
 * be a factor
 */
u_ll largest_factor_decent(u_ll value) {
	// initialize to the value in case you cannot get any prime divisions
	u_ll largest = value;
	u_ll current = value;

	for (u_ll x = 2; x <= static_cast<u_ll>(std::sqrt(current)) + 1; ++x) {
		if (current % x == 0) {
			largest = x;
		}
		while (current % x == 0) {
			current /= x;
		}
	}

	return largest;
}

int solve(vector<string>& input) {
	u_ll val = stoull(input[0]);

	u_ll result0 = largest_factor_decent(val);
	cout << "largest_factor_decent=" << result0 << "\n";

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
