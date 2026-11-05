#include <iostream>
#include <vector>
#include<cmath>
#include <stdexcept>
#include "../include/machine_learning_1/stochastic_gradient_descent.hpp"

using namespace std;

int main(){
     int passed =0, failed =0;

    //Test 1: Simple linear regression(y=2+3x)
    vector<vector<double>> x = {{1}, {2}, {3}, {4}};
    vector<double> y = {5, 8, 11, 14};
    vector<double> weights = {0, 0};

    try{
        LinearRegression::StochasticGradientDescent sgd(0.001, 5000);
        vector<double> result = sgd.optimize(x, y, weights);
        cout<< "Bias: "<<result[0]<< ", Weight: "<<result[1]<<endl;

        if (fabs(result[0] - 2) < 0.1 && fabs(result[1] - 3) < 0.1) {
         cout << "Simple regression: PASS \n";
         passed ++;   
    } else{
        cout<< "Simple regression: FAIL \n";
        failed++;
    }
    
}catch(...){
    cout<< "Simple regression: FAIL\n";
    failed ++;
}

// Test 2: Multiple linear regression
x = {{1, 1}, {2, 1}, {1, 2}, {2, 2}};
y = {6, 8, 9, 11};
weights = {0, 0, 0};

try{
    LinearRegression::StochasticGradientDescent sgd(0.001, 5000);
    vector<double> result = sgd.optimize(x, y, weights);
    cout << "Bias: " << result[0]<< ", Weight 1: " << result[1]
     << ", Weight 2: " << result[2] << endl;

    if(fabs(result[0] - 1)<0.25 &&
    fabs(result[1] - 2) <0.25 &&
    fabs(result[2] - 3) < 0.25){
        cout << "Multiple regression: PASS \n";
        passed ++;
    }else {
        cout<< "Multiple regression: FAIL \n";
        failed++;
    }
}catch(...){
    cout<< "Multiple regression: FAIL \n";
    failed++;
}

//Test 3: Zero iterations should preserve initial weights
try {
    LinearRegression::StochasticGradientDescent sgd(0.01, 0);
    vector<double> result = sgd.optimize({{1}}, {5}, {4, 6});

    if (result[0] == 4 && result[1] == 6){
        cout << "Zero iterations: PASS\n";
        passed++;
    }else{
        cout << "Zero iterations: FAIL\n";
        failed++;
    }
}catch(...){
    cout << "Zero iterations: FAIL\n";
    failed++;
}

//Test 4: Empty dataset should be rejected
try{
    LinearRegression::StochasticGradientDescent sgd(0.01, 10);
    sgd.optimize({}, {}, {0});
    cout << "Empty dataset: FAIL\n";
    failed++;
}catch (const invalid_argument&){
    cout << "Empty dataset: PASS\n";
    passed++;
}catch(...){
    cout << "Empty dataset: FAIL (unexpected exception)\n";
    failed++;
}

//Test 5:Mismatched dataset sizes should be rejected
try{
    LinearRegression::StochasticGradientDescent sgd(0.01, 10);
    sgd.optimize({{1}, {2}}, {3}, {0, 0});
    cout << "Mismatched sizes: FAIL\n";
    failed++;
}catch(const invalid_argument&){
    cout << "Mismatched sizes: PASS\n";
    passed++;
}catch(...){
    cout << "Mismatched sizes: FAIL (unexpected exception)\n";
    failed++;
}

//Test 6: Invalid learning rate should be rejected
try{
    LinearRegression::StochasticGradientDescent sgd(0, 10);
    cout << "Invalid learning rate: FAIL\n";
    failed++;
}catch (const invalid_argument&){
    cout << "Invalid learning rate: PASS\n";
    passed++;
}catch (...){
    cout << "Invalid learning rate: FAIL (unexpected exception)\n";
    failed ++;
}

cout << "\nPassed: " << passed << " | Failed: " << failed << endl;
return failed == 0 ? 0 : 1;
}
    