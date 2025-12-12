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
 * Using bottom up dp.
 * Do not do top down recursion for fib; your time will be O(2 ^ n) and space
 * will be O(n) for max depth of recursion stack.
 *
 * Just check the mod % 2 == 0 and sum?
 * Could also just add every 3rd value (e + o = o, o + o = e) 2, 3, 5, 8, 13,
 * 21, 34
 */
u_ll dynamic_programming(u_ll max) {
	u_ll result = 0;
	u_ll i = 1;
	u_ll j = 1;

	while (j < max) {
		if (j % 2 == 0) {
			result += j;
		}
		u_ll temp = j;
		j = i + j;
		i = temp;
	}
	return result;
}

/**
 * Do the algebra to get the F(n) to be some sum of every 3rd term
 * b/c: e + o = o, o + o = e, so evens are every 3rd term
 *
 * Say F(3) is an even (2 for example, if F(1) = 1, F(2) = 1)
 * then F(6) is next even, then F(9), etc
 *
 * F(2) = F(1) + F(0)
 * F(3) = F(1) + F(2)
 * F(4) = F(3) + F(2)
 * F(5) = F(4) + F(3)
 * F(6) = F(5) + F(4)
 *
 * Back substitute terms into 6
 * F(6) = F(4) + F(3) + F(4)
 * F(6) = F(3) + F(2) + F(3) + F(3) + F(2)
 * F(6) = 3 * F(3) + 2 * F(2)
 * F(6) = 3F(3) + 2 ( F(1) + F(0) )
 *
 * F(1) in terms of 3, 0
 * F(1) = F(2) - F(0)
 * F(1) = F(3) - F(1) - F(0)
 * 2F(1) = F(3) - F(0)
 *
 * F(6) = 3F(3) + 2F(1) + 2F(0)
 * F(6) = 3F(3) + F(3) - F(0) + 2F(0)
 * F(6) = 4F(3) + F(0)
 *
 * OR F(n) = 4F(n-3) + F(n-6) !!!
 */
u_ll dynamic_programming_fast(u_ll max) {

	u_ll result = 0;
	u_ll f_n_minus_6 = 0;
	u_ll f_n_minus_3 = 2;

	while (f_n_minus_3 < max) {
		result += f_n_minus_3;

		u_ll temp = f_n_minus_3;
		f_n_minus_3 = 4 * f_n_minus_3 + f_n_minus_6;
		f_n_minus_6 = temp;
	}

	return result;
}

int solve(vector<string>& input) {
	u_ll val = stoull(input[0]);

	u_ll result0 = dynamic_programming(val);
	cout << "dynamic_programming=" << result0 << "\n";

	u_ll result1 = dynamic_programming_fast(val);
	cout << "dynamic_programming_fast=" << result1 << "\n";
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
