#include <iostream>
#include <vector>
#include "machine_learning_1/correlation_coefficient.hpp"

int main() {
    std::vector<double> x = {1, 2, 3};
    std::vector<double> y = {40, 50, 60};

    statistics::Correlation data(x, y);

    double r = data.coefficient();

    std::cout << "Correlation coefficient: " << r << '\n';

    return 0;
}