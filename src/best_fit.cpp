#include "machine_learning_1/best_fit.hpp"
#include <stdexcept>

using namespace std;

LineParameters calculateBestFit(const vector<double>& x, const vector<double>& y){

    if (x.empty() || x.size() != y.size()) {
        throw invalid_argument("Input vectors must be non-empty and of the same size.");
    }
    double n = x.size();
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_x2 = 0.0;
    for (size_t i = 0; i < n; ++i) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    double denominator = (n * sum_x2) - (sum_x * sum_x);
    if (denominator == 0) {
        throw runtime_error("Denominator in slope calculation is zero, cannot compute best fit line.");
    }
    double m = ((n * sum_xy) - (sum_x * sum_y)) / denominator;
    double c = (sum_y - (m * sum_x)) / n;
    return {m, c};

} 