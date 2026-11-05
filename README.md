# group9_ML1
This is Group 9's project repository. We will be taking on Machine Learning 1 (Linear regression from scratch).


# Closed-Form Multiple Linear Regression
## 1. Overview
This module implements **multiple linear regression using the closed-form method** in C++.

Multiple linear regression is a supervised machine-learning algorithm used to predict a numerical output using two or more input features.

The model learns the relationship between the input features and the target output by calculating the regression coefficients from the training data.

Unlike iterative learning methods, the closed-form approach calculates the coefficients by solving a system of mathematical equations.

## 2. Mathematical Background
The general multiple linear regression equation is:

\[\hat{y}=b_0+b_1x_1+b_2x_2+\cdots+b_px_p\]

Where:

- \(\hat{y}\) is the predicted output.
- \(b_0\) is the intercept.
- \(b_1,b_2,\ldots,b_p\) are the regression coefficients.
- \(x_1,x_2,\ldots,x_p\) are the input features.
- \(p\) is the number of input features.

The coefficients are calculated using the **normal equations**:

\[
(A^TA)b=A^Ty
\]

The equivalent closed-form expression, when the inverse exists, is:

\[
\boxed{b=(A^TA)^{-1}A^Ty}
\]

Where:

- \(A\) is the design matrix, including a column of ones for the intercept.
- \(A^T\) is the transpose of the design matrix.
- \(y\) is the vector of actual target values.
- \(b\) is the vector of unknown regression coefficients.
- \((A^TA)^{-1}\) is the inverse of the matrix \(A^TA\).

This implementation solves the normal equations using **Gaussian elimination**, rather than explicitly calculating the matrix inverse.

## 3. Features
The module provides the following functionality:
- Accepts multiple input features and corresponding target values.
- Validates the training data before performing calculations.
- Constructs the design matrix, including the intercept column.
- Calculates the normal equation components.
- Solves the resulting system using Gaussian elimination.
- Stores the learned regression coefficients.
- Predicts numerical outputs for new observations.
- Provides access to the learned coefficients.
- Handles invalid inputs and singular matrices using exceptions.

## 4. Project Structure
The implementation is organised into the following files:

```text
include/
└── machine_learning_1/
    └── closed_form.hpp

src/
└── closed_form.cpp

examples/
└── closed_form_example.cpp

tests/
└── test_closed_form.cpp
```

### File descriptions
**closed_form.hpp**

Declares the `ClosedFormRegression` class, its private coefficient storage, and its public functions.

**closed_form.cpp**

Contains the implementation of the regression algorithm, including data validation, matrix calculations, Gaussian elimination, and prediction.

**closed_form_example.cpp**

Demonstrates how to create a regression model, train it, retrieve its coefficients, and make predictions.

**test_closed_form.cpp**

Contains tests that check coefficient calculation, prediction, and invalid input handling.

## 5. Class Interface

The module implements the `ClosedFormRegression` class.

It provides three main public functions:

### `fit(X, y)`

Trains the regression model using the supplied feature matrix and target vector.

```cpp
void fit(
    const std::vector<std::vector<double>>& X,
    const std::vector<double>& y
);
```

### `predict(features)`

Uses the learned coefficients to predict an output for a new observation.

```cpp
double predict(
    const std::vector<double>& features
) const;
```

### `get_coefficients()`

Returns the coefficients calculated during training.

```cpp
std::vector<double> get_coefficients() const;
```

## 6. Example Usage

The following example demonstrates how to train the regression model and make a prediction.

```cpp
#include "machine_learning_1/closed_form.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<std::vector<double>> X = {
        {1, 2}, {2, 1}, {3, 4}, {4, 3}, {5, 5}
    };

    std::vector<double> y = {50, 55, 80, 85, 100};

    // Create and train the model
    ClosedFormRegression model;
    model.fit(X, y);

    // Predict for a new observation
    double result = model.predict({6, 4});

    std::cout << "Prediction: " << result << std::endl;

    return 0;
}
```

The model learns its coefficients from the training data and uses them to predict the output for the new observation.

## 7. Compilation and Execution

The module can be compiled using a C++17-compatible compiler.

From the project root directory, compile the example using:

```bash
g++ -std=c++17 -I include src/closed_form.cpp examples/closed_form_example.cpp -o closed_form_example
```

Run the executable:

```bash
./closed_form_example
```

On Windows PowerShell, use:

```powershell
.\closed_form_example.exe
```

## 8. Testing

The module includes a test file:

```text
tests/test_closed_form.cpp
```

Compile the tests:

```bash
g++ -std=c++17 -I include src/closed_form.cpp tests/test_closed_form.cpp -o test_closed_form
```

Run the tests:

```bash
./test_closed_form
```

On Windows PowerShell:

```powershell
.\test_closed_form.exe
```

### Tests performed

The implementation is tested for:

1. Correct calculation of regression coefficients.
2. Correct prediction using the learned coefficients.
3. Rejection of observations with an incorrect number of features.
4. Rejection of empty training data.

**All four tests passed during local testing.**

## 9. Limitations

- The model predicts numerical outputs and is therefore intended for regression tasks.
- The normal equations can be numerically less stable than alternatives such as QR decomposition.
- Singular matrices are rejected because they do not produce a unique solution through the implemented method.
- The model does not automatically scale input features or restrict predictions to a particular range.

## 10. Conclusion

The Closed-Form Multiple Linear Regression module provides a C++ implementation of a regression algorithm that calculates its coefficients using the normal equations.

By combining matrix operations, Gaussian elimination, and object-oriented programming, the module provides functionality for training a regression model, retrieving its coefficients, and predicting numerical outputs for new observations.