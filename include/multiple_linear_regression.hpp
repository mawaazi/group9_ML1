#pragma once
#include <vector>

using namespace std;

class MultipleLinearRegression {
    private:
        vector<double> weights; // Stores beta coefficients (beta_1, beta_2, etc.)
    double bias;                 // Intercept term (beta_0)
    double learningRate;         // Step size for gradient descent
    int maxIterations;           // Training epochs

public:
    // Constructor with default hyperparameters
    MultipleLinearRegression(double lr = 0.01, int iters = 1000);

    // Core training method: Takes feature matrix X and target vector y
    void fit(const vector<vector<double>>& X_train, const vector<double>& y_train);

    // Prediction method: Takes a test feature matrix and returns predicted values
    vector<double> predict(const vector<vector<double>>& X_test) const;

    // Getter to view learned weights for debugging
    vector<double> getWeights() const;
};