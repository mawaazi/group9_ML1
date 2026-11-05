
#include "machine_learning_1/closed_form.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {

    // Training input features.
    vector<vector<double>> X = {
        {1, 2},
        {2, 1},
        {3, 4},
        {4, 3},
        {5, 5}
    };

    // Actual output values.
    vector<double> y = {
        50, 55, 80, 85, 100
    };

    // Create a regression model.
    ClosedFormRegression model;

    // Train the model.
    model.fit(X, y);

    // Retrieve the coefficients.
    vector<double> coefficients = model.get_coefficients();

    cout << "Regression coefficients:" << endl;

    for (size_t i = 0; i < coefficients.size(); ++i) {
        cout << "b" << i << " = " << coefficients[i] << endl;
    }

    // Predict the output for a new observation.
    vector<double> newStudent = {6, 4};

    double prediction = model.predict(newStudent);

    cout << "\nPredicted examination score: "
         << prediction << endl;

    return 0;
}

