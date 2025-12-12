#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

using ll = long long;

/**
 * Need to check triplets. First need to get the viable triplets.
 * Could loop through 1 through 1001 and store the squared values
 * in a 1-indexed vector.
 *
 * Then, you need to compare all candidates in the squared-values vector
 *  to see if there are 2 values in the array that sum to the candidate.
 *
 * Since it is sorted, you can used a sliding window from 1 to candidate - 1
 * to see if you can add to this value
 */
void get_pythagorean_triple_programmatically(ll* result, ll sum_equals) {
	std::vector<ll> squares(sum_equals, 0);
	for (ll i = 1; i < sum_equals + 1; ++i) {
		squares[i] = i * i;
	}

	// loop through our possible values for c^2
	for (ll i = 3; i < sum_equals + 1; ++i) {
		// sliding window on the previous values to see if we get a match
		ll start_window = 1;
		ll end_window = i - 1;

		while (start_window < end_window) {
			if (squares[start_window] + squares[end_window] == squares[i]) {
				// found a pythagorean triplet
				if (start_window + end_window + i == sum_equals) {
					// found a result
					result[0] = start_window;
					result[1] = end_window;
					result[2] = i;

					return;
				}

				// continue the search
				start_window++;
				end_window++;
			} else {
				// decrement the window
				if (squares[start_window] + squares[end_window] > squares[i]) {
					// too large
					end_window--;
				} else {
					// too small
					start_window++;
				}
			}
		}
	}
}

int solve(vector<string>& input) {
	ll result[3] = {0, 0, 0};
	get_pythagorean_triple_programmatically(result, 1000);
	cout << "result: v1=" << result[0] << ", v2=" << result[1] << ", v3=" << result[2] << endl;
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
