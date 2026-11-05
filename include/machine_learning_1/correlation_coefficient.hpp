#ifndef CORRELATION_HPP
#define CORRELATION_HPP

#include <vector>

namespace statistics {
class Correlation {
private:
    // Each object keeps its own copy of the paired values.
    std::vector<double> xValues;
    std::vector<double> yValues;

public:
    Correlation(const std::vector<double>& x, const std::vector<double>& y);

    // Calculates r without changing the stored values.
    // Invalid datasets cause std::invalid_argument when this is called.
    double coefficient() const;

    // Use this version when the data does not need to be stored in an object.
    // Requires equal lengths, two or more pairs, finite values and variation.
    static double pearson(const std::vector<double>& x,
                          const std::vector<double>& y);
};
}

#endif
