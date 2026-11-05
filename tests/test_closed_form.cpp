
#include "machine_learning_1/closed_form.hpp"

#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

using namespace std;

bool approximatelyEqual(double a, double b) {
    return abs(a - b) < 1e-6;
}

int main() {

    ClosedFormRegression model;

    // Test data based on y = 10 + 2x.
    vector<vector<double>> X = {
        {1},
        {2},
        {3},
        {4}
    };

    vector<double> y = {
        12, 14, 16, 18
    };

    // Test 1: Check coefficient calculation.
    try {
        model.fit(X, y);

        vector<double> coefficients = model.get_coefficients();

        if (approximatelyEqual(coefficients[0], 10) &&
            approximatelyEqual(coefficients[1], 2)) {
            cout << "Test 1 passed: Coefficients calculated correctly.\n";
        } else {
            cout << "Test 1 failed: Incorrect coefficients.\n";
            return 1;
        }

    } catch (const exception& e) {
        cout << "Test 1 failed: " << e.what() << endl;
        return 1;
    }

    // Test 2: Check prediction.
    try {
        double prediction = model.predict({5});

        if (approximatelyEqual(prediction, 20)) {
            cout << "Test 2 passed: Prediction is correct.\n";
        } else {
            cout << "Test 2 failed: Incorrect prediction.\n";
            return 1;
        }

    } catch (const exception& e) {
        cout << "Test 2 failed: " << e.what() << endl;
        return 1;
    }

    // Test 3: Check invalid feature dimensions.
    try {
        model.predict({5, 6});

        cout << "Test 3 failed: Invalid features were accepted.\n";
        return 1;

    } catch (const invalid_argument&) {
        cout << "Test 3 passed: Invalid features rejected.\n";
    }

    // Test 4: Check empty training data.
    try {
        model.fit({}, {});

        cout << "Test 4 failed: Empty data was accepted.\n";
        return 1;

    } catch (const invalid_argument&) {
        cout << "Test 4 passed: Empty training data rejected.\n";
    }

    cout << "\nAll tests passed!" << endl;

    return 0;
}

