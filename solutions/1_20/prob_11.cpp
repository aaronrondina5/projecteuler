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
 *
 * Initially thought about caching the products, but this breaks down with the 0s, because we
 * lose the record.
 *
 * like if we go from a sequence of 0, 1, 2, 3 our cache is at 0. Then
 * we move on to the next and we need to know 1,2,3 * next but we only have 0 in the cache.
 *
 * Could be an optimization still. And only do the back calculation if you hit a zero.
 * But probably too much for this.
 *
 *
 *
 * Time O(m x n x segment_length)
 * Space O(1)
 */
ll get_largest_grid_product(vector<vector<ll>>& grid, size_t segment_length) {
	if (segment_length == 0) {
		return 0;
	}

	size_t rows = grid.size();
	size_t cols = grid[0].size();

	ll result = LONG_MIN;

	for (size_t row = 0; row < rows; ++row) {
		for (size_t col = 0; col < cols; ++col) {
			// if horizontal segment long enough, compute and compare
			// We can only compare at this point, because of the possibility of negative values.
			// for example, say a we have segment_length = 4 and our 3 values are a max. Sounds good
			// right? but if the next value is negative, then we really dont have a max.
			if (col >= segment_length - 1) {
				ll horizontal_product = grid[row][col];
				for (size_t i = 1; i < segment_length; ++i) {
					horizontal_product *= grid[row][col - i];
				}
				result = max(horizontal_product, result);
			}

			// if vertical segment long enough, compute and compare
			if (row >= segment_length - 1) {
				ll vertical_product = grid[row][col];
				for (size_t i = 1; i < segment_length; ++i) {
					vertical_product *= grid[row - i][col];
				}
				result = max(vertical_product, result);
			}

			// if diagonal segment long enough, compute and compare
			if (row >= segment_length - 1 && col >= segment_length - 1) {
				ll diagonal_product = grid[row][col];
				for (size_t i = 1; i < segment_length; ++i) {
					diagonal_product *= grid[row - i][col - i];
				}
				result = max(diagonal_product, result);
			}

			// if anti-diagonal segment long enough, compute and compare
			if (row >= segment_length - 1 && cols - col >= segment_length) {
				ll antidiagonal_product = grid[row][col];
				for (size_t i = 1; i < segment_length; ++i) {
					antidiagonal_product *= grid[row - i][col + i];
				}
				result = max(antidiagonal_product, result);
			}
		}
	}

	return result;
}

int solve(vector<string>& input) {
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
