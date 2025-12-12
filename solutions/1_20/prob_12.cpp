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

* First approach, just move up on triangular numbers,
* check the number of divisors and return first value

 * Better approach
 * we can use the fact that our nth triangular number is equal to
 * n * (n + 1) / 2 and reduce our divisors calculations
 *
 * Notice the interesting thing that a number n and n + 1 share no common divisors
 * besides 1. They are called coprimes. Think about it - if there were a common divisor greater
 * than 1, it would have to be n + 2 or higher.
 *
 * therefore, the divisors of triangular_number is the divisors of n multiplied by the divisors
 * of n + 1 and handling whichever number is even(divide that by 2 and fetch divisors).
 *
 * Small improvement to cache the divisors calculated n+1
 *
 */

u_ll get_number_divisors(const u_ll value) {
	u_ll square_root = static_cast<u_ll>(std::sqrt(value));
	u_ll number_divisors = 0;

	for (u_ll i = 1; i <= square_root; ++i) {
		if (value % i == 0) {
			number_divisors += 2;
		}
	}

	// if it was a perfect square, you need to subtract one of the divisors
	if (square_root * square_root == value) {
		--number_divisors;
	}

	return number_divisors;
}

u_ll get_highly_divisible_triangular(u_ll min_divisors) {
	std::vector<u_ll> divisors_cache{0, 1};

	u_ll n = 1;

	while (true) {
		divisors_cache.emplace_back(get_number_divisors(n + 1));

		u_ll divisors = 1;
		if (n % 2 == 0) {
			// n is even, lets divide its divisors by 2, then multiply for combinations of n + 1
			// divisors
			divisors = divisors_cache[n / 2] * divisors_cache[n + 1];
		} else {
			divisors = divisors_cache[n] * divisors_cache[(n + 1) / 2];
		}

		if (divisors > min_divisors) {
			return n * (n + 1) / 2;
		}

		++n;
	}

	return 0;
}

int solve(vector<string>& input) {
	u_ll result = get_highly_divisible_triangular(stoull(input[0]));
	cout << "The first triangular number with over " << input[0] << " divisors is " << result
		 << endl;
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
