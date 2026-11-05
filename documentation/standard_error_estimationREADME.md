# Standard Error of Estimation

## 1. Overview

This module implements the **Standard Error of Estimation (SEE)** in C++.

The Standard Error of Estimation is a statistical measure used in regression analysis to determine how closely a regression model's predicted values agree with the actual observed values.

It measures the typical size of the prediction errors made by a regression model.

A smaller standard error indicates that the predicted values are generally closer to the actual values, while a larger standard error indicates greater variation between the predicted and actual values.

This module calculates the Standard Error of Estimation using the regression coefficients supplied to it.

Unlike a regression training algorithm, this module does not calculate the regression coefficients. It uses coefficients obtained from an already fitted regression model.

## 2. Mathematical Background

The Standard Error of Estimation is calculated using the residuals, which represent the differences between the actual and predicted values.

### 2.1 Multiple Linear Regression Equation

For a regression model with multiple input features, the predicted output is given by:

**ŷᵢ = b₀ + b₁xᵢ₁ + b₂xᵢ₂ + ⋯ + bₚ₋₁xᵢ,ₚ₋₁**

Where:

- **ŷᵢ** is the predicted output for observation i.
- **b₀** is the intercept.
- **b₁, b₂, …, bₚ₋₁** are the feature coefficients.
- **xᵢ₁, xᵢ₂, …, xᵢ,ₚ₋₁** are the input feature values for observation i.

### 2.2 Residuals

A residual is the difference between an actual observed value and its corresponding predicted value.

It is calculated as:

**eᵢ = yᵢ − ŷᵢ**

Where:

- **eᵢ** is the residual for observation i.
- **yᵢ** is the actual observed value.
- **ŷᵢ** is the predicted value.

### 2.3 Sum of Squared Errors (SSE)

The Sum of Squared Errors measures the total squared difference between the actual and predicted values.

It is calculated by squaring each residual and adding all the squared residuals together:

**SSE = e₁² + e₂² + ⋯ + eₙ²**

Alternatively:

**SSE = Σ (yᵢ − ŷᵢ)²**, for i = 1 to n.

Where:

- **SSE** is the Sum of Squared Errors.
- **n** is the total number of observations.
- **yᵢ** is the actual value.
- **ŷᵢ** is the predicted value.

Squaring the residuals prevents positive and negative errors from cancelling each other out.

### 2.4 Degrees of Freedom

The degrees of freedom are calculated by subtracting the number of estimated regression parameters from the total number of observations.

**Degrees of Freedom = n − p**

Where:

- **n** is the number of observations.
- **p** is the total number of estimated regression parameters, including the intercept.

For example, a regression model with two input features has three estimated parameters:

- One intercept.
- Two feature coefficients.

Therefore, p = 3.

The implementation requires the number of observations to be greater than the number of estimated parameters:

**n > p**

This ensures that the degrees of freedom are positive.

### 2.5 Standard Error of Estimation

The Standard Error of Estimation is calculated using:

**SEE = √[SSE / (n − p)]**

Where:

- **SEE** is the Standard Error of Estimation.
- **SSE** is the Sum of Squared Errors.
- **n** is the number of observations.
- **p** is the number of estimated regression parameters, including the intercept.

The result estimates the typical size of the model's prediction errors, expressed in the same units as the target variable.

## 3. Features

The module provides the following functionality:

- Accepts a feature matrix, actual target values and regression coefficients.
- Validates that the training data is not empty.
- Checks that the number of observations in the feature matrix matches the number of target values.
- Checks that the regression coefficients are provided.
- Verifies that the number of input features matches the supplied regression coefficients.
- Checks that there are enough observations to calculate the standard error.
- Calculates predicted values using the supplied regression coefficients.
- Calculates residuals for each observation.
- Computes the Sum of Squared Errors (SSE).
- Calculates the degrees of freedom.
- Returns the Standard Error of Estimation.
- Handles invalid input using exceptions.

## 4. Project Structure

The implementation is organised into the following files:

```text
include/
└── machine_learning_1/
    └── standard_error_estimation.hpp

src/
└── standard_error_estimation.cpp

examples/
└── standard_error_estimation_example.cpp

tests/
└── test_standard_error_estimation.cpp
```

### File descriptions

**standard_error_estimation.hpp**

Declares the `calculateStandardError()` function, which accepts the feature matrix, actual target values and regression coefficients.

**standard_error_estimation.cpp**

Contains the implementation of the Standard Error of Estimation calculation, including input validation, prediction calculation, residual calculation, SSE calculation and degrees of freedom.

**standard_error_estimation_example.cpp**

Demonstrates how to supply training data and regression coefficients, calculate the Standard Error of Estimation and display the result.

**test_standard_error_estimation.cpp**

Contains tests that check the calculation using perfect regression data, regression data containing errors, and invalid input.

## 5. Function Interface

The module provides one main function:

### calculateStandardError(X, y, coefficients)

Calculates and returns the Standard Error of Estimation using the supplied feature matrix, actual target values and regression coefficients.

```cpp
double calculateStandardError(
    const std::vector<std::vector<double>>& X,
    const std::vector<double>& y,
    const std::vector<double>& coefficients
);
```

Where:

- **X** is the feature matrix containing the input observations.
- **y** is the vector containing the actual target values.
- **coefficients** is the vector containing the regression coefficients.

The coefficients are arranged as follows:

- `coefficients[0]` represents the intercept.
- `coefficients[1]` represents the coefficient of the first feature.
- `coefficients[2]` represents the coefficient of the second feature.
- The remaining elements represent the coefficients of additional features.

The function returns a `double` representing the calculated Standard Error of Estimation.

If the supplied data is invalid, the function throws an `invalid_argument` exception.

## 6. Example Usage

The following example demonstrates how to calculate the Standard Error of Estimation for a multiple linear regression model with two input features.

```cpp
#include "../include/machine_learning_1/standard_error_estimation.hpp"

#include <iostream>
#include <vector>

using namespace std;

int main() {

    cout << "== STANDARD ERROR OF ESTIMATION EXAMPLE ==" << endl;

    // Training data
    // Each row contains x1 and x2.

    vector<vector<double>> X = {
        {1.0, 1.0},
        {2.0, 1.0},
        {1.0, 2.0},
        {3.0, 2.0},
        {2.0, 3.0},
        {4.0, 3.0}
    };

    // Actual target values.
    vector<double> y = {
        9.2, 11.7, 13.4, 18.6, 20.3, 26.1
    };

    // Previously calculated regression coefficients.
    // y = 2 + 3x1 + 4x2

    vector<double> coefficients = {
        2.0, 3.0, 4.0
    };

    // Calculate Standard Error of Estimation.
    double standardError =
        calculateStandardError(X, y, coefficients);

    cout << "\nRegression model:" << endl;

    cout << "y = "
         << coefficients[0] << " + "
         << coefficients[1] << "*x1 + "
         << coefficients[2] << "*x2" << endl;

    cout << "\nStandard Error of Estimation: "
         << standardError << endl;

    // Interpretation
    cout << "\nInterpretation:" << endl;

    cout << "The model's predictions typically differ "
         << "from the observed values by approximately "
         << standardError << " units of y." << endl;

    return 0;
}
```

For this example, the calculated Standard Error of Estimation is approximately:

**SEE = 0.42817**

This indicates that the model's predictions have a typical error size of approximately 0.42817 units of the target variable.

## 7. Compilation and Execution

The module can be compiled using a C++17-compatible compiler.

From the project root directory, compile the example using:

```bash
g++ -std=c++17 -I include src/standard_error_estimation.cpp examples/standard_error_estimation_example.cpp -o standard_error_example
```

Run the executable:

```bash
./standard_error_example
```

On Windows PowerShell, use:

```powershell
.\standard_error_example.exe
```

## 8. Testing

The module includes a test file:

`tests/test_standard_error_estimation.cpp`

Compile the tests using:

```bash
g++ -std=c++17 -I include src/standard_error_estimation.cpp tests/test_standard_error_estimation.cpp -o test_standard_error
```

Run the tests:

```bash
./test_standard_error
```

On Windows PowerShell:

```powershell
.\test_standard_error.exe
```

### Tests performed

The implementation includes tests for:

**Test 1: Perfect Regression**

Checks whether the function returns zero when the predicted values exactly match the actual values.

**Test 2: Regression With Error**

Checks whether the function correctly calculates the Standard Error of Estimation when the actual values differ from the predicted values.

For this test:

- SSE = 0.55
- n = 6
- p = 3
- Degrees of freedom = 6 − 3 = 3

Therefore:

**SEE = √(0.55 / 3) ≈ 0.42817**

**Test 3: Invalid Input**

Checks whether the function throws an exception when the number of observations in the feature matrix does not match the number of actual target values.

## 9. Limitations

- The module does not train the regression model or calculate its coefficients. It requires coefficients from an already fitted model.
- The calculation assumes that the supplied coefficients correspond to the features in the feature matrix.
- The function requires more observations than estimated regression parameters.
- The module does not calculate confidence intervals or prediction intervals.
- The Standard Error of Estimation is affected by the scale and units of the target variable.
- The calculation relies on the supplied regression model and data being valid and appropriately prepared.

## 10. Conclusion

The Standard Error of Estimation module provides a C++ implementation for measuring the typical prediction error of a regression model.

By calculating predicted values, residuals, the Sum of Squared Errors and degrees of freedom, the module determines how closely a regression model's predictions agree with the actual observed values.

Through this implementation, the project provides a useful statistical measure for evaluating the accuracy of regression models.