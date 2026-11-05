
#include "machine_learning_1/closed_form.hpp"

#include <stdexcept>
#include <cmath>
#include <algorithm>

using namespace std;

void ClosedFormRegression::fit(
    const vector<vector<double>>& X,
    const vector<double>& y
) {
    // Check for empty training data.
    if (X.empty() || y.empty()) {
        throw invalid_argument("Training data cannot be empty.");
    }

    // Check that X and y have equal numbers of observations.
    if (X.size() != y.size()) {
        throw invalid_argument("X and y must have equal sample sizes.");
    }

    size_t n = X.size();
    size_t features = X[0].size();
    size_t p = features + 1; // Include intercept.

    // Check that every observation has the same number of features.
    for (const auto& row : X) {
        if (row.size() != features) {
            throw invalid_argument("Inconsistent number of features.");
        }
    }

    if (n < p) {
        throw invalid_argument("Not enough observations.");
    }

    // Construct the design matrix with an intercept column.
    vector<vector<double>> A(n, vector<double>(p, 1.0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 1; j < p; ++j) {
            A[i][j] = X[i][j - 1];
        }
    }

    // Construct X transpose multiplied by X.
    vector<vector<double>> XtX(p, vector<double>(p, 0.0));

    // Construct X transpose multiplied by y.
    vector<double> Xty(p, 0.0);

    for (size_t i = 0; i < p; ++i) {
        for (size_t j = 0; j < p; ++j) {
            for (size_t k = 0; k < n; ++k) {
                XtX[i][j] += A[k][i] * A[k][j];
            }
        }

        for (size_t k = 0; k < n; ++k) {
            Xty[i] += A[k][i] * y[k];
        }
    }

    // Solve XtX * coefficients = Xty using Gaussian elimination.
    for (size_t i = 0; i < p; ++i) {

        // Find the row with the largest pivot.
        size_t pivot = i;

        for (size_t j = i + 1; j < p; ++j) {
            if (abs(XtX[j][i]) > abs(XtX[pivot][i])) {
                pivot = j;
            }
        }

        // Check for a singular matrix.
        if (abs(XtX[pivot][i]) < 1e-12) {
            throw invalid_argument(
                "Cannot solve regression: singular matrix."
            );
        }

        // Swap rows if necessary.
        swap(XtX[i], XtX[pivot]);
        swap(Xty[i], Xty[pivot]);

        // Normalize the pivot row.
        double divisor = XtX[i][i];

        for (size_t j = i; j < p; ++j) {
            XtX[i][j] /= divisor;
        }

        Xty[i] /= divisor;

        // Eliminate the other entries in this column.
        for (size_t j = 0; j < p; ++j) {
            if (j != i) {
                double factor = XtX[j][i];

                for (size_t k = i; k < p; ++k) {
                    XtX[j][k] -= factor * XtX[i][k];
                }

                Xty[j] -= factor * Xty[i];
            }
        }
    }

    // Store the calculated coefficients.
    coefficients = Xty;
}

double ClosedFormRegression::predict(
    const vector<double>& features
) const {

    if (coefficients.empty()) {
        throw invalid_argument("Model has not been fitted.");
    }

    if (features.size() != coefficients.size() - 1) {
        throw invalid_argument("Incorrect number of features.");
    }

    // Start with the intercept.
    double prediction = coefficients[0];

    // Add each feature's contribution.
    for (size_t i = 0; i < features.size(); ++i) {
        prediction += coefficients[i + 1] * features[i];
    }

    return prediction;
}

vector<double> ClosedFormRegression::get_coefficients() const {
    return coefficients;
}

