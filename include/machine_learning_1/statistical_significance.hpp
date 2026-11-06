#ifndef ML_LIBRARY_STATISTICAL_SIGNIFICANCE_HPP
#define ML_LIBRARY_STATISTICAL_SIGNIFICANCE_HPP

#include <vector> //vectors to hold datasets
#include <concepts> // concepts to restrict templates

namespace ml_library {

    template <typename T>
    concept Numeric = std::integral<T> || std::floating_point<T>;

    //Structure holding significance test results.
    struct SignificanceResult {
        double standard_error_slope;
        double t_statistic;
        int degrees_of_freedom;
        bool is_significant;
    };

    //class responsible for calculating statistical significance.
    class StatisticalSignificance {
    public:
        //evaluates the statistical significance of a fitted linear slope.
        template <Numeric T1, Numeric T2, Numeric T3>
        static SignificanceResult evaluateSlopeSignificance(
            const std::vector<T1>& x, 
            const std::vector<T2>& y, 
            T3 slope
        );
    };

} // namespace ml_library

#endif // ML_LIBRARY_STATISTICAL_SIGNIFICANCE_HPP