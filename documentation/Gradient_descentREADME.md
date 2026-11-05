# Batch Gradient Descent

## Overview

This module implements Batch Gradient Descent (BGD), an optimization algorithm used to train linear regression models.

The main purpose of the algorithm is to find the best values for the model's bias and weights so that its predictions are as close as possible to the actual output values.

Batch Gradient Descent uses the entire training dataset to calculate the gradients before updating the model parameters.

The implementation supports both simple and multiple linear regression, meaning it can work with one or several input features.

## How It Works

The linear regression model follows this general equation:

**Predicted output = Bias + (Weight 1 × Feature 1)+ (Weight 2 × Feature 2) + ...**

The algorithm starts with initial values for the bias and weights, then gradually adjusts them to reduce prediction errors.

It uses Mean Squared Error (MSE) to measure how far the predicted values are from the actual values.

MSE is calculated by:

**MSE = Sum of squared prediction errors / Number of samples**

The algorithm follows these steps:

1. Initialize the bias and weights.
2. Use the current parameters to predict outputs for all training samples.
3. Calculate the errors between predicted and actual values.
4. Calculate the gradients using all the training samples.
5. Update the bias and weights.
6. Repeat the process for the specified number of iterations.

In BGD, parameters are only updated after the entire training dataset has been processed.

## Implementation

The module consists of three main files:
 `gradient_descent.hpp` which Contains the function declaration. 
 `gradient_descent.cpp` which Contains the actual implementation of the algorithm. |
`test_gradient_descent.cpp` which Tests the algorithm's functionality and accuracy. |

The main function is:

**LinearRegression::computeGradientDescent()**

It accepts five parameters:

- `x`: Input features used for training.
- `y`: Actual output values corresponding to the input samples.
- `weights`: Initial bias and feature weights.
- `learningRate`: Controls how large each parameter update is.
- `iterations`: Number of times the algorithm repeats the learning process.

The function returns a vector containing the updated parameters.

The first element represents the bias, while the remaining elements represent the weights of the input features.

## Example

To demonstrate the implementation, consider a multiple linear regression problem:

**y = 2 + 3x1 + 4x2**

The expected parameters are:

- Bias = 2
- Weight of x1 = 3
- Weight of x2 = 4

The algorithm is given training samples and starts with initial weights of zero.

It then attempts to learn the correct parameters through repeated updates.

For example, the following settings are used in the test:

vector<double> initial_weights = {0.0, 0.0, 0.0};

double learningRate = 0.01;
int iterations = 5000;


After training, the resulting weights should be very close to the expected values.

## Testing

The module includes a test program located in:

`tests/test_gradient_descent.cpp`

The test uses a multiple linear regression dataset with two input features.

It checks whether the algorithm can learn the expected bias and weights within an acceptable margin of error.

### Running the Tests

From the project root directory, compile in the terminal of your IDE using:

**g++ -std=c++17 -Wall -Wextra -Iinclude src/gradient_descent.cpp tests/test_gradient_descent.cpp -o test_gradient.exe**

Run the executable:

**./test_gradient.exe**


A successful test should produce output similar to:

Multiple regression: PASS

Passed: 1 | Failed: 0**

## Advantages

- Uses the entire training dataset when calculating gradients.
- Produces relatively stable parameter updates.
- Supports multiple input features.
- Has a straightforward implementation.
- Works well with smaller and moderately sized datasets.

## Limitations

- Each iteration requires processing the entire dataset.
- Can become computationally expensive when working with very large datasets.
- Performance depends on choosing a suitable learning rate.
- May require many iterations to approach the optimal parameters.

## Conclusion

Batch Gradient Descent provides a systematic way of training linear regression models by using the entire training dataset to calculate parameter updates.

The implementation supports both simple and multiple linear regression and provides a useful example of how optimization algorithms can be implemented in C++.