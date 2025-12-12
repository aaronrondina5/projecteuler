#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

using ll = ll;

/**
 * Similar to largest grid product, cacheing fails us when we hit zeroes.
 * But lets try to cache anyway, and do the back calculation only if we hit a zero.
 *
 * Time O(n) in the best case O(n x segment_length) in worst case
 *
 * Space O(1)
 */
ll largest_product_in_series_greedy(const string& series, int segment_length) {
	int n = series.size();
	if (n < segment_length || segment_length == 0) {
		return 0;
	}

	ll result = 0;
	ll current_product = 1;

	for (size_t i = 0; i < n; ++i) {
		int value = series[i] - '0';
		current_product *= value;

		if (i > segment_length - 1) {
			int excluded_value = series[i - segment_length] - '0';
			if (excluded_value == 0) {
				// go back and recomput the values
				current_product = 1;
				for (size_t j = i - segment_length + 1; j <= i; ++j) {
					current_product *= (series[j] - '0');
				}
			} else {
				// we need to divide
				current_product /= excluded_value;
			}
		}

		if (i >= segment_length - 1) {
			result = std::max(result, current_product);
		}
	}

	return result;
}

int solve(vector<string>& input) {
	ll result = largest_product_in_series_greedy(input[0], 13);
	cout << "Result: " << result << endl;
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
