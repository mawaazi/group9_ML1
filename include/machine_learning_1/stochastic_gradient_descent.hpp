#ifndef STOCHASTIC_GRADIENT_DESCENT_HPP
#define STOCHASTIC_GRADIENT_DESCENT_HPP//header guards to prevent compilation error

#include<vector>

namespace LinearRegression{

    //Base class for gradient descent optimizers
    class GradientDescentOptimizer{
        private:
        double learningRate;
        int iterations;//attributes cannot be directly accessed directly.

        protected:
        double getLearningRate() const;
        int getIterations() const;//these can be accessed by both parent and derived class

        public:
        GradientDescentOptimizer(double lR, int iter);//constructor

        virtual std:: vector<double> optimize(
            const std:: vector<std::vector<double>> &x,
            const std:: vector<double> &y,
            std:: vector<double> weights
        )=0;//virtual function to be implemented in the derived classes

        virtual ~GradientDescentOptimizer()= default;//destructor
    };
    //Derived class implementing Stochastic Gradient Descent
    class StochasticGradientDescent : public GradientDescentOptimizer{
        public:
        StochasticGradientDescent(double lR, int iter);//derived class constructor

        std::vector<double> optimize(
            const std:: vector<std::vector<double>> &x,
            const std:: vector<double> &y,
            std:: vector<double> weights
        )override;//overrides base class function with actual SGd implementation
    };
}
#endif