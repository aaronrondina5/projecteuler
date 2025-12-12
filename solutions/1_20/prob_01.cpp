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
 * Better solution
 *
 * 3, 6, 9, 12...
 * 5, 10, 15, 20...
 *
 * So then you have a straightforward sequence 1,2,3,4... etc to which you need
 * to find the sum. That sum can be thought of as (1 + n) + (2 + n - 1) + (3 + n
 * - 2) etc
 *
 * Okay, so then we get the end of the sequence by floor(input / 3) or
 * floor(input / 5) and get the sum using the method above and multiply by the
 * corresponding factor
 *
 * Then, you must subtract the "duplicate" additions - because there are common
 * multiples at every 15th (LCM) value.
 *
 * Time O(1)
 * Space O(1)
 */
u_ll sum_consecutive(const u_ll lo, const u_ll hi_inclusive) {
	if (lo > hi_inclusive) {
		return 0;
	}
	return static_cast<u_ll>((static_cast<u_ll>(hi_inclusive + lo) / 2.0) *
							 (hi_inclusive - lo + 1));
}

u_ll sum_of_multiples_of_factor(const u_ll factor, const u_ll end_inclusive) {
	return factor * sum_consecutive(0, end_inclusive / factor);
}

u_ll sum_multiples_of_three_five_math(u_ll end_inclusive) {
	return sum_of_multiples_of_factor(3, end_inclusive) +
		   sum_of_multiples_of_factor(5, end_inclusive) -
		   sum_of_multiples_of_factor(15, end_inclusive);
}

/**
 * Straightforward solution
 *
 * loop and mod
 *
 * Time: O(n) where n is max
 * Size: O(1)
 */
u_ll sum_multiples_of_three_five_iter(u_ll end_inclusive) {
	u_ll result = 0;
	for (int i = 0; i <= end_inclusive; ++i) {
		if (i % 3 == 0 || i % 5 == 0) {
			result += i;
		}
	}
	return result;
}

int solve(vector<string>& input) {
	u_ll val = stoull(input[0]);

	u_ll result0 = sum_multiples_of_three_five_iter(val);
	cout << "sum_multiples_of_three_five_iter=" << result0 << "\n";

	u_ll result1 = sum_multiples_of_three_five_math(val);
	cout << "sum_multiples_of_three_five_math=" << result1 << "\n";

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
