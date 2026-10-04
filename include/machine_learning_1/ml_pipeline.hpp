#ifndef ML_PIPELINE_HPP
#define ML_PIPELINE_HPP

#include <vector>

// STRICT RULE: Do not add "using namespace std;" in this header file.
// All function signatures here must explicitly use std::vector.

// ==============================================================================
// TEAM INTERFACES - Define inputs and outputs here
// ==============================================================================

// Member 1: Data & Utilities
std::vector<std::vector<double>> loadCSV(const char* filepath);
void trainTestSplit(const std::vector<std::vector<double>>& data, double splitRatio);

// Member 2: Analytical Models
std::vector<double> closedFormRegression(const std::vector<std::vector<double>>& x, const std::vector<double>& y);

// Member 3: Iterative Models
std::vector<double> gradientDescent(const std::vector<std::vector<double>>& x, const std::vector<double>& y);

// Member 4: Data Processing
void applySMOTE(std::vector<std::vector<double>>& data);

// Member 5: Statistical Evaluation
double calculateRSquared(const std::vector<double>& actual, const std::vector<double>& predicted);

// Member 6: Error & Bounds
double calculateStandardError(const std::vector<double>& actual, const std::vector<double>& predicted);

#endif