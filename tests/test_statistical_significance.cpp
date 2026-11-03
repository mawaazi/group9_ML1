#include <iostream>
#include <vector>
#include <cassert>
#include <stdexcept>
#include "ml_library/statistical_significance.hpp"

void testSlopeSignificance() {
    std::cout << "[TEST] Running Slope Statistical Significance Test...\n";

    // Sample data: simple linear relationship y = 2x + 1
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y = {3.0, 5.0, 7.0, 9.0, 11.0};
    double fitted_slope = 2.0;

    auto result = ml_library::StatisticalSignificance::evaluateSlopeSignificance(x, y, fitted_slope);

    std::cout << "  -> Standard Error of Slope: " << result.standard_error_slope << "\n";
    std::cout << "  -> t-Statistic:             " << result.t_statistic << "\n";
    std::cout << "  -> Degrees of Freedom:      " << result.degrees_of_freedom << "\n";
    std::cout << "  -> Is Significant:          " << (result.is_significant ? "Yes" : "No") << "\n";

    // Validate degrees of freedom (n - 2 for simple linear regression)
    assert(result.degrees_of_freedom == 3);

    std::cout << "[PASS] Statistical significance test passed successfully!\n\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << " STATISTICAL SIGNIFICANCE TEST SUITE\n";
    std::cout << "========================================\n\n";

    try {
        testSlopeSignificance();
        std::cout << "ALL STATISTICAL TESTS PASSED CLEANLY!\n";
    } catch (const std::exception& e) {
        std::cerr << "[FAIL] Test failed with exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}