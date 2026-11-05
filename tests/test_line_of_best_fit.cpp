#include "machine_learning_1/best_fit.hpp"
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>

using namespace std;

// Helper function for floating-point comparison
bool is_close(double a, double b, double epsilon = 1e-5) {
    return std::abs(a - b) < epsilon;
}

int main() {
    cout << "Running Line of Best Fit tests..." << endl;

    // 1. Arrange: Set up known data
    // TEST 1: Standard Calculation
    vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    vector<double> y = {2.0, 4.0, 5.0, 4.0, 5.0}; // Perfect linear relationship: y = 2x

    LineParameters result = calculateBestFit(x, y);

    assert(is_close(result.slope, 0.6)); // Expected slope
    assert(is_close(result.intercept, 2.2)); // Expected intercept
    cout << " - Calculation test passed." << endl;

    //TEST 2: Exception Handling - Size Mismatch
    vector<double> y_short = {2.0, 4.0}; // Mismatched size
    bool threw_invalid_arg = false;
    try {
        calculateBestFit(x, y_short);
    } catch (const invalid_argument& e) {
        threw_invalid_arg = true;
        cout << " - Caught expected invalid_argument exception: " << e.what() << endl;
    }
    assert(threw_invalid_arg && "Failed to throw invalid_argument for mismatched sizes.");
    cout << " - Size mismatch test passed." << endl;

    // TEST 3: Exception Handling - Zero Denominator

    vector<double> x_same = {2.0, 2.0, 2.0}; // All x values are the same
    vector<double> y_diff = {1.0, 2.0, 3.0}; // Different y values
    bool threw_runtime = false;
    try {
        calculateBestFit(x_same, y_diff);
    } catch (const runtime_error& e) {
        threw_runtime = true;
        cout << " - Caught expected runtime_error exception: " << e.what() << endl;
    }
    assert(threw_runtime && "Failed to throw runtime_error for zero denominator.");
    cout << " - Zero denominator test passed." << endl;

    cout << "All tests passed successfully!" << endl;
    return 0;

}