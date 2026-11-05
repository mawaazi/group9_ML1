#include "machine_learning_1/prediction_interval.hpp"
#include <cmath>

PredictionBounds calculatePredictionInterval(
    double new_x,
    const std::vector<double>& x_data,
    const std::vector<double>& y_data,
    double slope,
    double intercept,
    double t_value
)
{
    int n = x_data.size();
    if (n<= 2) return {0.0, 0.0, 0.0}; // Not enough data points to calculate prediction interval

    double sum_x = 0.0;
    for (double x : x_data) sum_x += x;
    double mean_x = sum_x / n;

    double ss_x = 0.0;
    for (double x : x_data) {
        ss_x += (x - mean_x) * (x - mean_x);
    }
    
    double sse =0.0;
    for (int i = 0; i < n; ++i) {
        double predicted_y = slope * x_data[i] + intercept;
        sse += (y_data[i] - predicted_y) * (y_data[i] - predicted_y);
    }

    double se = std::sqrt(sse / (n - 2));

    double margin_of_error = t_value * se * std::sqrt(1.0 + (1.0 / n) + ((new_x - mean_x) * (new_x - mean_x)) / ss_x);
    double predicted_y_new = slope * new_x + intercept;

    return {predicted_y_new - margin_of_error, predicted_y_new + margin_of_error, predicted_y_new};

}