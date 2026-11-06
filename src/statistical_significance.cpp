#include "machine_learning_1/statistical_significance.hpp" //importing my header
#include <cmath> // math functions like std::sqrt
#include <numeric> // std::accumulate (summation)
#include <stdexcept> // runtime error handling e.g std::invalid_argument
#include <cstddef> // for std::size_t

namespace ml_library {

    template <Numeric T1, Numeric T2, Numeric T3>
    SignificanceResult StatisticalSignificance::evaluateSlopeSignificance(
        const std::vector<T1>& x, 
        const std::vector<T2>& y, 
        T3 slope
    ) {
        if (x.size() != y.size()) {
            throw std::invalid_argument("Feature vector X and target vector y must have the same size.");
        }
        std::size_t n = x.size();
        if (n <= 2) {
            throw std::invalid_argument("Dataset size must be greater than 2 to calculate degrees of freedom (n - 2).");
        }

        double mean_x = static_cast<double>(std::accumulate(x.begin(), x.end(), 0.0)) / n;

        double ss_x = 0.0;
        for (auto val : x) {
            double diff = static_cast<double>(val) - mean_x;
            ss_x += diff * diff;
        }

        if (ss_x == 0.0) {
            throw std::invalid_argument("Variance of X cannot be zero.");
        }

        double mean_y = static_cast<double>(std::accumulate(y.begin(), y.end(), 0.0)) / n;
        double double_slope = static_cast<double>(slope);
        double intercept = mean_y - double_slope * mean_x;

        double rss = 0.0;
        for (std::size_t i = 0; i < n; ++i) {
            double y_pred = double_slope * static_cast<double>(x[i]) + intercept;
            double residual = static_cast<double>(y[i]) - y_pred;
            rss += residual * residual;
        }

        int df = static_cast<int>(n - 2);
        double standard_error_estimation = std::sqrt(rss / df);
        double se_slope = standard_error_estimation / std::sqrt(ss_x);

        double t_stat = (se_slope > 0.0) ? (double_slope / se_slope) : 0.0;
        bool significant = std::abs(t_stat) > 2.0;

        return {se_slope, t_stat, df, significant};
    }

    // Explicit Template Instantiations
    template SignificanceResult StatisticalSignificance::evaluateSlopeSignificance(
        const std::vector<double>&, const std::vector<double>&, double);

    template SignificanceResult StatisticalSignificance::evaluateSlopeSignificance(
        const std::vector<int>&, const std::vector<float>&, double);

    template SignificanceResult StatisticalSignificance::evaluateSlopeSignificance(
        const std::vector<float>&, const std::vector<float>&, float);

} // namespace ml_library