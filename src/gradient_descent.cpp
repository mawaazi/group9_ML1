#include "../include/machine_learning_1/gradient_descent.hpp" 
#include <vector>
#include <stdexcept>

using namespace std;

namespace LinearRegression{

    vector<double> computeGradientDescent(
        const vector<vector<double>>& x,
        const vector<double>& y,
        vector<double> weights,
        double learningRate,
        int iterations
    )
    
    {
        size_t m = x.size(); // Number of data samples

        if (m == 0) {
            return weights;
        }

        if (y.size() != m) {
            throw invalid_argument(
                "The number of samples in x must match the number of values in y."
            );
        }

        if (weights.empty()) {
            throw invalid_argument(
                "The weights vector cannot be empty."
            );
        }

        if (learningRate <= 0) {
            throw invalid_argument(
                "Learning rate must be greater than zero."
            );
        }

        if (iterations <= 0) {
            throw invalid_argument(
                "Number of iterations must be greater than zero."
            );
        }

        size_t n = weights.size();

              size_t numberOfFeatures = n - 1;

        
        for (size_t i = 0; i < m; ++i) {
            if (x[i].size() != numberOfFeatures) {
                throw invalid_argument(
                    "Number of features in x does not match the number of weights."
                );
            }
        }

        for (int it = 0; it < iterations; ++it) {

            vector<double> predictions(m, 0.0);
            vector<double> gradients(n, 0.0);

            // Calculate predictions
            //
            // y_pred = beta_0 + beta_1*x1 + beta_2*x2 + ...
            for (size_t i = 0; i < m; ++i) {

                double prediction = weights[0]; // Intercept

                for (size_t j = 1; j < n; ++j) {
                    prediction += x[i][j - 1] * weights[j];
                }

                predictions[i] = prediction;
            }

            // Calculate gradients
            for (size_t j = 0; j < n; ++j) {

                double gradientSum = 0.0;

                for (size_t i = 0; i < m; ++i) {

                    double error = predictions[i] - y[i];

                    // j = 0 is the intercept.
                    // j > 0 corresponds to feature j - 1.
                    double featureVal;

                    if (j == 0) {
                        featureVal = 1.0;
                    }
                    else {
                        featureVal = x[i][j - 1];
                    }

                    gradientSum += error * featureVal;
                }

                gradients[j] = (2.0 / m) * gradientSum;
            }

            // Update weights
            for (size_t j = 0; j < n; ++j) {
                weights[j] -= learningRate * gradients[j];
            }
        }

        return weights;
    }
}
