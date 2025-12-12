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
 * Programmatic approach
 * you always will take the same number of steps down and to the right
 * if its a m x n graph, you will take m steps down, and n steps to the right,
 * no matter what path you take.
 *
 * the question is calling 2x2 grid a graph of 3x3 points.
 * so naive approach, we could just backtrack with all the paths.
 *
 * A better approach is to use DP to do it.
 *
 * A possible improvement to this dynamic programming method is
 * to only use 1 half of the matrix because it is symmetrical across
 * the diagonal.
 *
 */
u_ll get_lattice_paths_dp(u_int m, u_int n) {

	if (m == 0 || n == 0) {
		return 0;
	}

	std::vector<std::vector<u_ll>> dp(m + 1, std::vector<u_ll>(n + 1, 0));
	// so you can skip the first row & col and dont have to do a check each time
	for (size_t row = 0; row <= m; ++row) {
		dp[row][0] = 1;
	}
	for (size_t col = 0; col <= n; ++col) {
		dp[0][col] = 1;
	}

	for (size_t row = 1; row <= m; ++row) {
		for (size_t col = 1; col <= n; ++col) {
			dp[row][col] = dp[row][col - 1] + dp[row - 1][col];
		}
	}

	return dp[m][n];
}

/**
 * There are 20 "down" steps and 20 "right" steps.
 * So, a possible combination looks like DDRDRRRD...RDD..R
 *
 * Total combinations are 40!
 * For each particular combination, you could re-arrange each grouping 20! ways.
 * (bookeeper rule)
 *
 * thus ans = 40! / 20! * 20!
 */

u_ll factorial(const u_ll n) {
	u_ll result = 2;
	for (u_ll i = 3; i < n + 1; ++i) {
		result *= i;
	}
	return result;
}

u_ll get_num_lattice_paths_combinatorics(u_int m, u_int n) {
	return factorial(m + n) / (factorial(m) * factorial(n));
}

int solve(vector<string>& input) {
	u_ll result_dp = get_lattice_paths_dp(20, 20);
	u_ll result_comb = get_num_lattice_paths_combinatorics(20, 20);
	cout << "Number of lattice paths in a 20x20 grid (DP): " << result_dp << endl;
	cout << "Number of lattice paths in a 20x20 grid (Combinatorics): " << result_comb << endl;
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
