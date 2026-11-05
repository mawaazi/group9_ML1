#include <iostream>
#include <vector>
#include <cmath>
#include "../include/machine_learning_1/gradient_descent.hpp"
using namespace std;

int main() {
    // Dataset: y = 2+ 3x1 + 4x2
    
    vector<vector<double>> x = {
        {1.0, 1.0},
        {2.0, 1.0},
        {1.0, 2.0},
        {2.0, 2.0},
        {3.0, 1.0}
    };
    
    // Target values y
    vector<double> y = {9.0, 12.0, 13.0, 16.0, 15.0};

    // Initial starting weights [bias, x1 weight, x2 weight]
    vector<double> initial_weights = {0.0, 0.0, 0.0};

    // Hyperparameters
    double learningRate = 0.01;
    int iterations = 5000;

    cout << "Running Gradient Descent tests..." << std::endl;

    // Run the Batch Gradient Descent 
    vector<double> final_weights = LinearRegression::computeGradientDescent(
        x, y, initial_weights, learningRate, iterations
    );

    //Expected weights
    vector<double> expected_weights = {2.0, 3.0, 4.0};

    //Check results
    int passed=0;
    int failed=0;

    if (final_weights.size() != expected_weights.size()){
        cout << "Multiple regression: FAIL\n";
        failed++;
    }else{
        bool correct = true;

        for (size_t i = 0; i < final_weights.size(); ++i){
            if (fabs(final_weights[i] - expected_weights[i]) > 0.1){
                correct = false;
                break;
            }
        }
        if (correct){
            cout << "Multiple regression: PASS\n";
            passed++;

        }else{
            cout << "Multiple regression: FAIL\n";
            failed++;
        }
    }

    // Print the results
    std::cout << "Final Weights:" << std::endl;
    for (size_t i = 0; i < final_weights.size(); ++i) {
        std::cout << "Weight " << i << ": " << final_weights[i] << std::endl;
    }
    std::cout << "---------------------------------------------------\n";
    std::cout << "Passed: " << passed << " | Failed: " << failed << endl;

    return (failed==0) ? 0:1;
}