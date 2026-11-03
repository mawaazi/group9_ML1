#ifndef STOCHASTIC_GRADIENT_DESCENT_HPP
#define STOCHASTIC_GRADIENT_DESCENT_HPP

#include<vector>

namespace LinearRegression{

    //Base class for gradient descent optimizers
    class GradientDescentOptimizer{
        private:
        double learningRate;
        int iterations;

        protected:
        double getLearningRate() const;
        int getIterations() const;

        public:
        GradientDescentOptimizer(double lR, int iter);

        virtual std:: vector<double> optimize(
            const std:: vector<std::vector<double>> &x,
            const std:: vector<double> &y,
            std:: vector<double> weights

        )=0;

        virtual ~GradientDescentOptimizer()= default;

    };

    //Derived class implementing Stochastic Gradient Descent
    class StochasticGradientDescent : public GradientDescentOptimizer{
        public:
        StochasticGradientDescent(double lR, int iter);

        std::vector<double> optimize(
            const std:: vector<std::vector<double>> &x,
            const std:: vector<double> &y,
            std:: vector<double> weights
        )override;//overrides base class function with actual SGd implementation
    };


}
#endif