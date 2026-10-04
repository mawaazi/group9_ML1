#include "../include/machine_learning_1/ml_pipeline.hpp"

// It is safe to use the namespace here. It will not leak to other files.
using namespace std; 

// ==============================================================================
// TEAM IMPLEMENTATIONS - Teammates replace mock returns with real math here
// ==============================================================================

// ---------------------------------------------------------
// Member 1: Data & Utilities
// ---------------------------------------------------------
vector<vector<double>> loadCSV(const char* filepath) { 
    // TODO: Write logic to open CSV and parse into a 2D matrix
    return {}; // Mock return
}

void trainTestSplit(const vector<vector<double>>& data, double splitRatio) {
    // TODO: Write logic to split data into training and testing sets
}

// ---------------------------------------------------------
// Member 2: Analytical Models
// ---------------------------------------------------------
vector<double> closedFormRegression(const vector<vector<double>>& x, const vector<double>& y) { 
    // TODO: Implement exact mathematical solution for line of best fit
    return {0.0}; // Mock return
}

// ---------------------------------------------------------
// Member 3: Iterative Models
// ---------------------------------------------------------
vector<double> gradientDescent(const vector<vector<double>>& x, const vector<double>& y) { 
    // TODO: Implement iterative gradient descent algorithm
    return {0.0}; // Mock return
}

// ---------------------------------------------------------
// Member 4: Data Processing
// ---------------------------------------------------------
void applySMOTE(vector<vector<double>>& data) {
    // TODO: Implement Synthetic Minority Over-sampling Technique
}

// ---------------------------------------------------------
// Member 5: Statistical Evaluation
// ---------------------------------------------------------
double calculateRSquared(const vector<double>& actual, const vector<double>& predicted) { 
    // TODO: Calculate coefficient of determination
    return 0.0; // Mock return
}

// ---------------------------------------------------------
// Member 6: Error & Bounds
// ---------------------------------------------------------
double calculateStandardError(const vector<double>& actual, const vector<double>& predicted) { 
    // TODO: Calculate standard error of estimation
    return 0.0; // Mock return
}