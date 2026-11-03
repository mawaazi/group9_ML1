#include <iostream>
#include <vector>
#include "ml_library/statistical_significance.hpp"

int main() {
    std::cout << "========================================\n";
    std::cout << " STATISTICAL SIGNIFICANCE EXAMPLE\n";
    std::cout << "========================================\n\n";

    // Sample data: Linear relationship y = 2.5x + 1.0 with minor variations
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
    std::vector<double> y = {3.6, 5.8, 8.2, 11.1, 13.0, 15.5, 18.2, 20.9};
    double fitted_slope = 2.48; // Estimated slope from regression

    try {
        auto result = ml_library::StatisticalSignificance::evaluateSlopeSignificance(x, y, fitted_slope);

        std::cout << "[INFO] Statistical significance evaluation successful!\n";
        std::cout << "  -> Fitted Slope:              " << fitted_slope << "\n";
        std::cout << "  -> Standard Error (Slope):    " << result.standard_error_slope << "\n";
        std::cout << "  -> t-Statistic:               " << result.t_statistic << "\n";
        std::cout << "  -> Degrees of Freedom:        " << result.degrees_of_freedom << "\n";
        std::cout << "  -> Statistically Significant: " << (result.is_significant ? "Yes" : "No") << "\n\n";

    } catch (const std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << '\n';
        return 1;
    }

    return 0;
}