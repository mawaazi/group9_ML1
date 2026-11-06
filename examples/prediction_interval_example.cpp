#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "machine_learning_1/best_fit.hpp"
#include "machine_learning_1/prediction_interval.hpp"

using namespace std;

int main() {
    
    // STEP 1: Same sample data as the line-of-best-fit example
    // x = hours studied, y = test score (out of 10)
   
    vector<double> hours = {1.0, 2.0, 3.0, 4.0, 5.0};
    vector<double> score = {2.0, 4.0, 5.0, 4.0, 5.0};

    cout << " STEP 1: The data " << endl;
    cout << "  5 students, hours studied 1 to 5" << endl;

    
    // STEP 2: Get the best-fit line first.
    // The prediction interval needs the slope and intercept as inputs.
    
    LineParameters line = calculateBestFit(hours, score);

    cout << endl << " STEP 2: The best-fit line " << endl;
    cout << fixed << setprecision(4);
    cout << "  y = " << line.slope << " x + " << line.intercept << endl;

   
    // STEP 3: Choose the t-value.
    // 95% confidence, n - 2 = 5 - 2 = 3 degrees of freedom -> t = 3.182
    // (taken from a t-table; C++ has no built-in lookup)
   
    double t_value = 3.182;

    cout << endl << " STEP 3: Confidence setting " << endl;
    cout << "  95% confidence, degrees of freedom = 3, t = " << t_value << endl;

    
    // STEP 4: Predict INSIDE the data range (x = 3 hours)
    // The interval should be narrower here.
    
    double inside_x = 3.0;
    PredictionBounds inside = calculatePredictionInterval(
        inside_x, hours, score, line.slope, line.intercept, t_value);

    cout << endl << " STEP 4: Predict at x = " << inside_x << " (inside the data) " << endl;
    cout << "  Predicted score: " << inside.predicted_y << endl;
    cout << "  Range:           " << inside.lower_bound << " to " << inside.upper_bound << endl;
    cout << "  Width:           " << (inside.upper_bound - inside.lower_bound) << endl;

    
    // STEP 5: Predict OUTSIDE the data range (x = 6 hours)
    // The interval should be wider, because we are extrapolating.
    // Hand check: predicted 5.8, margin about 4.124, range about 1.676 to 9.924
    
    double outside_x = 6.0;
    PredictionBounds outside = calculatePredictionInterval(
        outside_x, hours, score, line.slope, line.intercept, t_value);

    cout << endl << " STEP 5: Predict at x = " << outside_x << " (outside the data) " << endl;
    cout << "  Predicted score: " << outside.predicted_y << endl;
    cout << "  Range:           " << outside.lower_bound << " to " << outside.upper_bound << endl;
    cout << "  Width:           " << (outside.upper_bound - outside.lower_bound) << endl;

   
    // STEP 6: Check the answer against the hand calculation
  
    cout << endl << " STEP 6: Checking against the hand calculation " << endl;
    bool pred_ok  = std::fabs(outside.predicted_y - 5.8) < 1e-6;
    bool lower_ok = std::fabs(outside.lower_bound - 1.6757) < 1e-3;
    bool upper_ok = std::fabs(outside.upper_bound - 9.9243) < 1e-3;
    cout << "  Predicted 5.8 matches:       " << (pred_ok ? "YES" : "NO") << endl;
    cout << "  Lower bound 1.6757 matches:  " << (lower_ok ? "YES" : "NO") << endl;
    cout << "  Upper bound 9.9243 matches:  " << (upper_ok ? "YES" : "NO") << endl;
    cout << "  Wider outside the data:      "
         << ((outside.upper_bound - outside.lower_bound) >
             (inside.upper_bound - inside.lower_bound) ? "YES" : "NO") << endl;

    
    // STEP 7: Bad input is rejected
   
    cout << endl << " STEP 7: Bad input is rejected " << endl;

    vector<double> two_points_x = {1.0, 2.0};
    vector<double> two_points_y = {2.0, 4.0};
    try {
        calculatePredictionInterval(outside_x, two_points_x, two_points_y,
                                    line.slope, line.intercept, t_value);
        cout << "  (unexpected: no exception)" << endl;
    } catch (const invalid_argument& e) {
        cout << "  Caught invalid_argument: " << e.what() << endl;
    }

    vector<double> same_hours = {3.0, 3.0, 3.0, 3.0};
    vector<double> any_scores = {1.0, 2.0, 3.0, 4.0};
    try {
        calculatePredictionInterval(outside_x, same_hours, any_scores,
                                    line.slope, line.intercept, t_value);
        cout << "  (unexpected: no exception)" << endl;
    } catch (const runtime_error& e) {
        cout << "  Caught runtime_error: " << e.what() << endl;
    }

    cout << endl << "Demo finished." << endl;
    return 0;
}
