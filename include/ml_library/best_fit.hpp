#ifndef BEST_FIT_HPP
#define BEST_FIT_HPP

#include <vector>
struct LineParameters {
    double slope;
    double intercept;
};
LineParameters calculateBestFit(const std::vector<double>& x, const std::vector<double>& y);

#endif // BEST_FIT_HPP