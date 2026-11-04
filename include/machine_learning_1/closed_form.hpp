
#ifndef CLOSED_FORM_HPP
#define CLOSED_FORM_HPP

#include <vector>

using namespace std;

vector<double> fit(
    const vector<vector<double>>& X,
    const vector<double>& y
);

double predict(
    const vector<double>& coefficients,
    const vector<double>& features
);

#endif
