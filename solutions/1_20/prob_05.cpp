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
 * So you would start at res=1
 * then move to 2, res *= 2
 * then 3, res *= 3
 * then 4, you only need 1 2, because you have a factor of 2 already
 * How to figure this out?
 *  you essentially need to know the prime factorization, and have a running
 * total of number of primes that are needed to build the number so if we keep
 * an array of length 20 for numbers 1 thru 20, then continue to update this as
 * you move along
 */
u_ll smallest_multiple_with_factorization_loop(const u_ll end) {

	u_ll end_value = end;

	// Initialize a value count holder array
	std::vector<u_ll> factor_count_holder(end_value + 1,
										  0); // +1 for 1-based indexing

	for (u_ll i = 2; i <= end_value; ++i) {
		u_ll factor = i;

		// Loop through the prime factors and count how many are needed
		u_ll prime = 2;
		while (factor > 1) {
			if (factor % prime == 0) {
				// Valid prime factor - count total
				u_ll prime_count = 0;
				while (factor % prime == 0) {
					prime_count++;
					factor /= prime;
				}

				// Update the value_count_holder for this prime if needed (1 indexed)
				factor_count_holder[prime] = max(factor_count_holder[prime], prime_count);
			}
			prime++;
		}
	}

	// Now we have an array of number of each prime value
	// Loop through and multiply
	u_ll res = 1;
	for (size_t factor = 2; factor < factor_count_holder.size(); ++factor) {
		if (factor_count_holder[factor] > 0) {
			res *= static_cast<u_ll>(std::pow(factor, factor_count_holder[factor]));
		}
	}
	return res;
}

int solve(vector<string>& input) {
	u_ll result = smallest_multiple_with_factorization_loop(stoull(input[0]));
	cout << "smallest_multiple_with_factorization_loop=" << result << endl;
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
