#include"../include/machine_learning_1/standard_error_estimation.hpp"

#include<vector>
#include<stdexcept>
#include<cmath>

using namespace std;

double calculateStandardError(
const vector<vector<double>>& X,
const vector<double>& y,
const vector<double>& coefficients
)
{
    size_t n = X.size();

    //check that data is there
    if(n==0){
        throw invalid_argument("Training data cannot be empty.");
    }
    
    //check that X and y have the same number of samples
    if(y.size()!=n){
        throw invalid_argument("The number of samples in X must match the number of values in y.");
    }

    //Number of estimated parameters
    // coefficients[0]= intercept
    //coefficients[1...]= feature coefficients
    size_t p = coefficients.size();

    //X must contain p-1 features
    size_t numberOfFeatures = p-1;

    //checkt that every row has the correct number of features.
    for(size_t i=0;i<n;++i){

        if(X[i].size()!= numberOfFeatures){
            throw invalid_argument(
                "Number of features in X doesn't match the coefficients."
            );
        }
        
    }

    //We need positive degrees of freedom:
    //degrees of freedom = n-p
    //therefore:
    // n must be greater than p.
    if (n<=p){
        throw invalid_argument("Not enough observations to calculate standard error of estimation.");
    }

    if (coefficients.empty()) {
    throw invalid_argument("Coefficients cannot be empty.");
    }

    //Calculate the sum of squared errors (SSE)
    double SSE=0.0;
    for(size_t i=0; i<n; ++i){
        // start with the intercept
        double prediction = coefficients[0];
        //Add the contribution from each feature.
        for(size_t j=1;j<p; ++j){
            prediction += coefficients[j]*X[i][j-1];
        }
        //Residual
        // e=actual-predicted;
        double error = y[i] - prediction;
        //Add squared residual to SSE
        SSE += error * error;
    }
    //Degrees of freedom.
    size_t degreesOfFreedom = n - p;

    //standard error of estimation
    double standardError = sqrt(SSE / degreesOfFreedom);
    
    return standardError;
}