#include <iostream>
#include "../include/machine_learning_1/ml_pipeline.hpp"

// Safe to use here as well.
using namespace std;

int main() {
    cout << "Starting ML Pipeline..." << endl;
    
    // 1. Data Loading Phase
    auto data = loadCSV("dummy.csv");
    
    // 2. Data Processing Phase
    applySMOTE(data);
    trainTestSplit(data, 0.8);
    
    // Dummy variables for compilation testing (will be replaced by actual data)
    vector<vector<double>> x_train; 
    vector<double> y_train; 
    
    // 3. Training Phase
    auto weights = gradientDescent(x_train, y_train);
    
    // 4. Evaluation Phase
    auto r_squared = calculateRSquared(y_train, y_train);
    
    cout << "Pipeline compiled and executed successfully." << endl;
    return 0;
}