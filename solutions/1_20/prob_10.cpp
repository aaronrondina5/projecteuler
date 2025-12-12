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

// Sieve of Eratosthenes approach to sum all primes below limit
u_ll sum_primes_sieve_and_sum(u_ll limit) {
	std::vector<bool> is_prime(limit, true);

	u_ll result = 0;
	for (u_ll i = 2; i < limit; ++i) {
		if (is_prime[i]) {
			result += i;

			for (u_ll j = i + i; j < limit; j += i) {
				is_prime[j] = false;
			}
		}
	}

	return result;
}

int solve(vector<string>& input) {
	u_ll limit = stoull(input[0]);
	u_ll result = sum_primes_sieve_and_sum(limit);
	cout << "Sum of all primes below " << limit << " is " << result << endl;
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
