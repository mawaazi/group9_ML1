#include "../include/machine_learning_1/stochastic_gradient_descent.hpp"
#include<stdexcept>
#include<algorithm>
#include<random>

namespace LinearRegression{

    //Initialises the optimiser parameters
    GradientDescentOptimizer::GradientDescentOptimizer(double lR, int iter)
    : learningRate(lR), iterations(iter){
        if (lR <=0 || iter <0) {
            throw std::invalid_argument("Invalid learning rate or iteration count");
        }
    }

    //Returns the Learning rate
    double GradientDescentOptimizer::getLearningRate() const{
        return learningRate;
    }

    //Returns the number of iterations
    int GradientDescentOptimizer::getIterations() const{
        return iterations;
    }

    //Initialise the stochastic gradient descent optimiser
    StochasticGradientDescent::StochasticGradientDescent(double lR, int iter)
    :GradientDescentOptimizer(lR,iter){

    }

    //Updates the model weights using one training example at a time
    std::vector<double> StochasticGradientDescent::optimize(
        const std::vector<std::vector<double>> &x,
        const std::vector<double> &y,
        std::vector<double> weights
    ){
        if (x.empty() || x.size() != y.size()){
            throw std::invalid_argument("Invalid training data.");
        }

        const std:: size_t featureCount = x[0].size();

        if (weights.size() != featureCount +1){
            throw std::invalid_argument("Incorrect number of weights.");
        }

        for (const auto& row: x){
            if (row.size() != featureCount){
                throw std::invalid_argument("Inconsistent number of features.");
            }
        }

        double lR = getLearningRate();
        int iter = getIterations();

        std::vector<std::size_t> indices(x.size());

        for  (std::size_t i=0; i< indices.size(); ++i){
            indices [i] = i;
        }
        std::mt19937 generator(std:: random_device{}());

        for (int epoch =0; epoch <iter; ++epoch){
            std::shuffle(indices.begin(), indices.end(), generator);
            for (std::size_t i : indices){
                double prediction = weights[0];

                for (std::size_t j=0; j< featureCount; ++j){
                    prediction += weights [j+1] * x[i][j];
                }
                double error = prediction - y[i];

                weights[0] -= lR *error;

                for(std::size_t j=0; j< featureCount; ++j){
                    weights[j +1] -= lR * error * x[i][j];
                }
            }
        }

        return weights;
    }
}