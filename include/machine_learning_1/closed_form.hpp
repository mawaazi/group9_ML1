#ifndef CLOSED_FORM_HPP
#define CLOSED_FORM_HPP

#include <vector>

class ClosedFormRegression {
private:
    std::vector<double> coefficients;

public:
    void fit(
        const std::vector<std::vector<double>>& X,
        const std::vector<double>& y
    );

    double predict(
        const std::vector<double>& features
    ) const;

    std::vector<double> get_coefficients() const;
};

#endif // closed_form.hpp
