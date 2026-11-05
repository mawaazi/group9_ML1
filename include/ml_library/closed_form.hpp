#ifndef CLOSED_FORM_HPP
#define CLOSED_FORM_HPP

#include <vector>

class ClosedFormRegression {
private:
    // Stores the intercept and feature coefficients.
    std::vector<double> coefficients;

public:
    // Calculates regression coefficients from training data.
    void fit(
        const std::vector<std::vector<double>>& X,
        const std::vector<double>& y
    );

    // Predicts an output using new feature values.
    double predict(
        const std::vector<double>& features
    ) const;

    // Returns the calculated coefficients.
    std::vector<double> get_coefficients() const;
};
#endif // CLOSED_FORM_HPP
