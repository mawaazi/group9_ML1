#ifndef STANDARD_ERROR_HPP
#define STANDARD_ERROR_HPP

#include <vector>

double calculateStandardError(
    const std::vector<std::vector<double>>& X,
    const std::vector<double>& y,
    const std::vector<double>& coefficients
);

#endif