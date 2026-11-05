#ifndef GRADIENT_DESCENT_HPP
#define GRADIENT_DESCENT_HPP

#include <vector>
using namespace std;

namespace LinearRegression {
    // Function declaration for standard gradient descent
    vector<double> computeGradientDescent(
        const vector<std::vector<double>>& x, 
        const vector<double>& y, 
        vector<double> weights, 
        double learningRate, 
        int iterations
    );
}

#endif