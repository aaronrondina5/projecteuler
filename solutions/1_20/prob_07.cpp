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
 * Plan is to build up our sieve so we dont have to consider candidates
 * that are multiples of primes.
 * so as we get closer to n, we wont be doing a second n pass each time.
 *
 * The trick is that we dont know how to size our vector initially.
 * So just pick an estimate, then resize if needed.
 */
u_ll large_prime_with_sieve(u_ll n) {
	u_ll try_size = 10 * n;

	std::vector<bool> is_prime(try_size, true);

	u_ll i = 2;
	u_ll prime_count = 0;
	while (i <= try_size) {
		if (i == try_size) {
			try_size *= 10;
			is_prime.assign(try_size, true);
			i = 2;
			prime_count = 0;
		} else {
			if (is_prime[i]) {
				/**
				 * Build sieve and check if answer
				 */

				++prime_count;
				if (prime_count == n) {
					return i;
				}

				/**
				 * remove all multiples of i from contention
				 */
				u_ll j = i + i;
				while (j < try_size) {
					is_prime[j] = false;
					j = j + i;
				}
			}

			++i;
		}
	}

	return -1;
}

int solve(vector<string>& input) {
	u_ll result = large_prime_with_sieve(stoull(input[0]));
	cout << "large_prime_with_sieve=" << result << "\n";
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
