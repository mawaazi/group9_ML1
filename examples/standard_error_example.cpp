#include"../include/machine_learning_1/standard_error_estimation.hpp"

#include<iostream>
#include<vector>
using namespace std;

int main(){
    cout << "==STANDARD ERROR OF ESTIMATION EXAMPLE=="<< endl;

    //TRAINING DATA

    // Each row contains: x1,x2
    vector<vector<double>> X = {
        {1.0, 1.0},
        {2.0, 1.0},
        {1.0, 2.0},
        {3.0, 2.0},
        {2.0, 3.0},
        {4.0, 3.0}
    };
    //actual target values.
    vector<double> y = {9.2,11.7,13.4,18.6,20.3,26.1};

    //FITTED MODEL
    //suppose another part of the project has already fitted the regression model and produced these coefficients:
    // y= beta0 + beta1*x1 + beta2*x2
    // beta0 = 2.0, beta1 = 3.0, beta2 = 4.0
    vector<double> coefficients = {2.0, 3.0, 4.0};

    //Calculate the standard error of estimation
    double standardError = calculateStandardError(X,y,coefficients);
    cout<<"\nRegression model:"<<endl;
    cout<< "y=" <<coefficients[0]<<" + "<<coefficients[1]<<"*x1 + "<<coefficients[2]<<"*x2"<<endl;
    cout<<"\nStandard error of estimation: "<<standardError<<endl;

    //INTERPRETATION
    cout<<"\nInterpretation:"<<endl;
    cout<<"The model's predictions typically differ"<<"from the obseved values by approximately "<<standardError<<"units of y."<<endl;

    return 0;
}