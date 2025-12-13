#include <algorithm>
#include <chrono>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

using u_int = unsigned int;

constexpr char ZERO = '0';

// going to have to go column by column and keep track of carry
// cannot do convert to numeric obviously
// keep a cyclic array of the 10 digits
// output to string

u_int get_power(u_int value) {
	u_int result = 0;
	while (value > 9) {
		value /= 10;
	}
	return result;
}

u_int get_max_digits_of_multiple(const u_int n_digits_base, const u_int multiple) {
	// the power of the number of values will allow us to properly size our
	// result vector. say the power is 2 - ie 4 x 100.
	// we know that our result will be at most length= (num_digits + 2 + 1).
	// But, we can also cap our vector size, in case we want to go the cyclic array route.
	return n_digits_base + get_power(multiple) + 1;
}

void first_n_digits_of_sum(stringstream& result, const vector<string>& input, const u_int n_digits) {

	const u_int n_values = input.size();
	const u_int n_digits_per_value = input[0].size(); // assume all the same

	if (n_digits > get_max_digits_of_multiple(n_digits_per_value, n_values)) {
		throw runtime_error("Invalid num digits");
	}

	vector<u_int> result_digits(n_digits, ZERO);
	size_t cyclic_result_index = n_digits - 1;

	u_int carry = 0;
	for (int col = n_digits_per_value - 1; col > -1; --col) {
		u_int sum = carry;
		for (size_t row = 0; row < n_values; ++row) {
			sum += (input[row][col] - '0');
		}

		result_digits[cyclic_result_index] = sum % 10;
		carry = sum / 10;

		cyclic_result_index = cyclic_result_index == 0 ? n_digits - 1 : cyclic_result_index - 1;
	}

	while (carry > 0) {
		result_digits[cyclic_result_index] = carry % 10;
		carry /= 10;
		cyclic_result_index = cyclic_result_index == 0 ? n_digits - 1 : cyclic_result_index - 1;
	}

	// now move the result index back to where it was
	cyclic_result_index = cyclic_result_index == n_digits - 1 ? 0 : cyclic_result_index + 1;
	for (u_int i = 0; i < n_digits; ++i) {
		result << result_digits[cyclic_result_index];
		cyclic_result_index = cyclic_result_index == n_digits - 1 ? 0 : cyclic_result_index + 1;
	}
}

int solve(const vector<string>& input) {
	stringstream result;
	first_n_digits_of_sum(result, input, 10);
	cout << "result=" << result.str() << endl;
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
