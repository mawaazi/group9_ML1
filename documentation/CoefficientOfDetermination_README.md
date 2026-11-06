# Coefficient of Determination (R^2)

## 1. Project Description
The coefficient of Determination (R^2) is a statistical metric used to evaluate how well a machine learning regression model predicts actual data. It represents the proportion of the variance in the dependent variable that is predictable from the independent variable(s)

## 2. Main Features
 Calculates the R² score for regression models.
 Uses a high-performance, single-pass **O(n)** algorithm for maximum speed.
 Templated to support `float`, `double`, and `long double` data types.
 Includes strict compile-time and runtime validation (presents integer inputs, empty vectors and NaN/Infinity values).

## 3. Requirements and Dependencies
 **C++ Standard:** C++17 or higher (compiled with `-std=c++23` for this project).
 **Dependencies:** Standard Template Library (`<vector>`, `<cmath>`, `<type_traits>`), and the ML1 library's `ml_error.hpp`.

## 4. How to use the library
 Include the header in your c++ file:
 ```cpp
 #include "machine_learning_1/coefficient_of_determination.h"