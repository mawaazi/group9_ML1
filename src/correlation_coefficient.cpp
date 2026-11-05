#include "machine_learning_1/correlation_coefficient.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
namespace statistics {
Correlation::Correlation(const std::vector<double>& x,
                         const std::vector<double>& y)
    : xValues(x), yValues(y) {}

double Correlation::coefficient() const {
    return pearson(xValues, yValues);
}

double Correlation::pearson(const std::vector<double>& x,
                            const std::vector<double>& y) {
    // Every x value must have a matching y value.
    if (x.size() != y.size())
        throw std::invalid_argument("The two datasets must have equal lengths.");
    if (x.size() < 2)
        throw std::invalid_argument("At least two pairs are required.");

    // Scaling reduces the risk of overflow for large inputs.
    long double scaleX = 0, scaleY = 0;
    for (std::size_t i = 0; i < x.size(); ++i) {
        if (!std::isfinite(x[i]) || !std::isfinite(y[i]))
            throw std::invalid_argument("All values must be finite numbers.");
        scaleX = std::max(scaleX, std::abs(static_cast<long double>(x[i])));
        scaleY = std::max(scaleY, std::abs(static_cast<long double>(y[i])));
    }
    if (scaleX == 0 || scaleY == 0)
        throw std::invalid_argument("Correlation is undefined for constant data.");

    // Find the mean of each scaled dataset.
    long double meanX = 0, meanY = 0;
    const long double n = static_cast<long double>(x.size());
    for (std::size_t i = 0; i < x.size(); ++i) {
        meanX += (x[i] / scaleX) / n;
        meanY += (y[i] / scaleY) / n;
    }

    // Work with deviations from the means.
    long double sumXX = 0, sumYY = 0, sumXY = 0;
    for (std::size_t i = 0; i < x.size(); ++i) {
        const long double dx = x[i] / scaleX - meanX;
        const long double dy = y[i] / scaleY - meanY;
        sumXX += dx * dx;
        sumYY += dy * dy;
        sumXY += dx * dy;
    }
    // A constant dataset has no defined correlation coefficient.
    if (std::all_of(x.begin(), x.end(), [&](double v) { return v == x.front(); }) ||
        std::all_of(y.begin(), y.end(), [&](double v) { return v == y.front(); }) ||
        sumXX == 0 || sumYY == 0)
        throw std::invalid_argument("Correlation is undefined for constant data.");

    // Separate square roots avoid multiplying two large sums.
    const long double r = (sumXY / std::sqrt(sumXX)) / std::sqrt(sumYY);
    // Allow for small rounding errors at -1 and 1.
    return static_cast<double>(std::max(-1.0L, std::min(r, 1.0L)));
}
}
