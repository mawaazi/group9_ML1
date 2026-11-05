#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <stdexcept>
#include "machine_learning_1/prediction_interval.hpp"

using namespace std;
// Helper function for floating-point comparison
bool is_close(double a, double b, double epsilon = 1e-5) {
    return std::abs(a - b) < epsilon;
}

int main(){
    cout << "Running Prediction Interval tests..." << endl;

    // TEST 1: Standard Calculation
    vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    vector<double> y = {2.0, 4.0, 5.0, 4.0, 5.0}; // Perfect linear relationship: y = 2x
    double new_x = 0.6; // From previous best fit calculation
    double slope = 0.6;
    double intercept = 2.2;
    double t_value = 3.182; // Approximate t-value for 95% confidence with 3 degrees of freedom
    
    PredictionBounds result = calculatePredictionInterval(
        new_x,
        x,
        y,
        slope,
        intercept,
        t_value
    );

    // Assert the bounds are logical (lower is less than upper)
    assert(result.lower_bound < result.upper_bound);

    // Assert the predicted y is calculated correctly: y = mx + c = (0.6 * 6.0) + 2.2 = 5.8
    assert(is_close(result.predicted_y, 5.8));

    // Check if margins are symmetrical
    double lower_margin = result.predicted_y - result.lower_bound;
    double upper_margin = result.upper_bound - result.predicted_y;
    assert(is_close(lower_margin, upper_margin));

    cout << " - Calculation test passed." << endl;

    // TEST 2: Exception Handling - Vector Size & Mismatch

    vector<double> x_short = {1.0, 2.0};
    vector<double> y_short = {2.0, 4.0};
    vector<double> y_mismatch = {2.0, 4.0, 5.0}; // Mismatched size

    bool threw_invalid_arg_size = false;
    try {
        calculatePredictionInterval(new_x, x_short, y_short, slope, intercept, t_value);
    } catch (const invalid_argument& e) {
        threw_invalid_arg_size = true;
        cout << " - Caught expected invalid_argument exception for size: " << e.what() << endl;
    }
    assert(threw_invalid_arg_size && "Failed to throw invalid_argument for n <= 2.");

    bool threw_invalid_arg_mismatch = false;
    try
    {
    calculatePredictionInterval(new_x, x, y_mismatch, slope, intercept, t_value);
    } catch (const invalid_argument& e) {
        threw_invalid_arg_mismatch = true;
        cout << " - Caught expected invalid_argument exception for mismatch: " << e.what() << endl;
    }
    assert(threw_invalid_arg_mismatch && "Failed to throw invalid_argument for mismatched vector sizes.");

    cout << "- Size and mismatch exception tests passed." << endl;
    
    // TEST 3: Exception Handling - Zero Variance (ss_xx == 0)

    vector<double> x_same = {3.0, 3.0, 3.0}; // All x values are the same
    vector<double> y_diff = {1.0, 2.0, 3.0}; // Different y values

    bool threw_runtime = false;
    try {
        calculatePredictionInterval(new_x, x_same, y_diff, slope, intercept, t_value);
    } catch (const runtime_error& e) {
        threw_runtime = true;
        cout << " - Caught expected runtime_error exception for zero variance: " << e.what() << endl;
    }
    assert(threw_runtime && "Failed to throw runtime_error for zero variance in x_data.");
    cout << " - Zero variance test passed." << endl;

    cout << "All tests passed successfully!" << endl;
    return 0;
}