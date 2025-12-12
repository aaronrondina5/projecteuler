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
 * simply do the loop and take the difference
 * There seems to be a mathematical way to do this, but I don't know it
 */
u_ll sum_consecutive(const u_ll lo, const u_ll hi_inclusive) {
	if (lo > hi_inclusive) {
		return 0;
	}
	return static_cast<u_ll>((static_cast<u_ll>(hi_inclusive + lo) / 2.0) *
							 (hi_inclusive - lo + 1));
}
u_ll sum_square_difference_with_loop(u_ll limit_inclusive) {
	u_ll sum_squares = 0;
	for (u_ll i = 1; i <= limit_inclusive; ++i) {
		sum_squares += (i * i);
	}
	u_ll sum_consec = sum_consecutive(1, limit_inclusive);
	return sum_consec * sum_consec - sum_squares;
}

int solve(vector<string>& input) {
	u_ll result = sum_square_difference_with_loop(stoull(input[0]));
	cout << "sum_square_difference_with_loop=" << result << "\n";
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
