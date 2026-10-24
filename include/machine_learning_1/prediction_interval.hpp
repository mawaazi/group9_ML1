#ifndef PREDICTION_INTERVAL_HPP
#define PREDICTION_INTERVAL_HPP

#include <vector>
#include <utility>

std::pair<double, double> calculatePredictionInterval(
    double new_x,
    const std::vector<double>& x_data,
    const std::vector<double>& y_data,
    double slope,
    double intercept,
    double t_value
);

#endif // PREDICTION_INTERVAL_HPP