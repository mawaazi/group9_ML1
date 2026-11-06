#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "machine_learning_1/best_fit.hpp"

using namespace std;

int main() {
   
    // STEP 1: Sample data
    // x = hours studied, y = test score (out of 10)
    
    vector<double> hours = {1.0, 2.0, 3.0, 4.0, 5.0};
    vector<double> score = {2.0, 4.0, 5.0, 4.0, 5.0};

    cout << " STEP 1: The data " << endl;
    for (size_t i = 0; i < hours.size(); ++i) {
        cout << "  Student " << i + 1 << ": studied " << hours[i]
             << " hour(s), scored " << score[i] << endl;
    }


    // STEP 2: Work out the sums the formula needs (for explanation).
    // calculateBestFit() does exactly this internally.
    
    double n = hours.size();
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x2 = 0.0;
    for (size_t i = 0; i < hours.size(); ++i) {
        sum_x  += hours[i];
        sum_y  += score[i];
        sum_xy += hours[i] * score[i];
        sum_x2 += hours[i] * hours[i];
    }

    cout << endl << " STEP 2: The sums " << endl;
    cout << "  n = " << n << ", sum x = " << sum_x << ", sum y = " << sum_y << endl;
    cout << "  sum xy = " << sum_xy << ", sum x^2 = " << sum_x2 << endl;

    
    // STEP 3: Call the library function
    
    LineParameters line = calculateBestFit(hours, score);

    cout << endl << " STEP 3: The best-fit line " << endl;
    cout << fixed << setprecision(2);
    cout << "  slope     m = " << line.slope << endl;
    cout << "  intercept c = " << line.intercept << endl;
    cout << "  Line: y = " << line.slope << " x + " << line.intercept << endl;

    
    // STEP 4: Check the answer against the hand calculation
    // m = (5*66 - 15*20) / (5*55 - 15*15) = 30 / 50 = 0.6
    // c = (20 - 0.6*15) / 5 = 2.2
    
    cout << endl << " STEP 4: Checking against the hand calculation " << endl;
    bool slope_ok = std::fabs(line.slope - 0.6) < 1e-9;
    bool intercept_ok = std::fabs(line.intercept - 2.2) < 1e-9;
    cout << "  Slope 0.6 matches:     " << (slope_ok ? "YES" : "NO") << endl;
    cout << "  Intercept 2.2 matches: " << (intercept_ok ? "YES" : "NO") << endl;

    
    // STEP 5: Use the line to predict a score
    
    double hours_to_predict = 6.0;
    double predicted = line.slope * hours_to_predict + line.intercept;
    cout << endl << " STEP 5: Using the line " << endl;
    cout << "  Predicted score after " << hours_to_predict << " hours: "
         << predicted << endl;

   
    // STEP 6: What happens with bad input? The function throws.
    
    cout << endl << " STEP 6: Bad input is rejected " << endl;

    vector<double> short_score = {2.0, 4.0};   // only 2 scores for 5 hours
    try {
        calculateBestFit(hours, short_score);
        cout << "  (unexpected: no exception)" << endl;
    } catch (const invalid_argument& e) {
        cout << "  Caught invalid_argument: " << e.what() << endl;
    }

    vector<double> same_hours = {3.0, 3.0, 3.0};  // every x is identical
    vector<double> any_scores = {1.0, 2.0, 3.0};
    try {
        calculateBestFit(same_hours, any_scores);
        cout << "  (unexpected: no exception)" << endl;
    } catch (const runtime_error& e) {
        cout << "  Caught runtime_error: " << e.what() << endl;
    }

    cout << endl << "Demo finished." << endl;
    return 0;
}