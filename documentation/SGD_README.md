# Stochastic Gradient Descent

## Overview

This module implements Stochastic Gradient Descent (SGD), an optimization algorithm used to train linear regression models.

Unlike Batch Gradient Descent, which uses the entire training dataset before updating the model parameters, SGD updates the parameters after processing each individual training sample.

This allows the algorithm to make frequent updates during training and can be useful when working with large datasets.

The implementation supports both simple and multiple linear regression.

It also uses a class-based approach, making use of object-oriented programming concepts such as inheritance, encapsulation and polymorphism.

## How It Works

The linear regression model follows this general equation:

**Predicted output = Bias + (Weight 1 × Feature 1)+ (Weight 2 × Feature 2) + ...**

The aim is to find suitable values for the bias and weights so that the difference between predicted and actual outputs is minimized.

The algorithm uses the prediction error to determine how the parameters should be adjusted.

The general weight update rule is:

**New weight = Old weight - (Learning rate × Gradient)**

In SGD, the gradient is calculated using one training sample at a time.

The algorithm follows these steps:

1. Initialize the bias and weights.
2. Shuffle the training samples.
3. Select one training sample.
4. Calculate the predicted output.
5. Find the difference between the predicted and actual output.
6. Use the error to calculate the gradient.
7. Immediately update the bias and weights.
8. Move to the next training sample and repeat the process.
9. Continue until the specified number of iterations is completed.

The samples are shuffled to avoid processing them in the same order during every training cycle.

Since updates happen after each sample, the parameter values may fluctuate during training.

## Object-Oriented Design

The implementation uses two main classes:

### 1. GradientDescentOptimizer

This is the base class from which the SGD implementation inherits.

It stores the common optimization settings:

- Learning rate
- Number of iterations

These attributes are private, meaning they cannot be accessed directly from outside the class.

The class provides protected getter functions that allow derived classes to access these settings.

It also declares a pure virtual function called `optimize()`, which must be implemented by any derived optimization class.

### 2. StochasticGradientDescent

This is a derived class that inherits from `GradientDescentOptimizer`.

It provides the actual implementation of the `optimize()` function, performing the Stochastic Gradient Descent process.

This design demonstrates several OOP concepts:

- **Encapsulation:** The learning rate and number of iterations are kept private.
- **Inheritance:** The SGD class inherits common functionality from the base optimizer class.
- **Polymorphism:** The derived class implements the virtual `optimize()` function.

This structure also makes it easier to extend the project with other optimization algorithms in the future.

## Implementation

The module consists of the following files:

`stochastic_gradient_descent.hpp`:Declares the base and derived classes. 
`stochastic_gradient_descent.cpp`:Contains the SGD implementation. 
`test_stochastic_gradient_descent.cpp`:Tests the algorithm under different conditions. 
`SDG_example.cpp`:Demonstrates how to use the SGD implementation. 

The main class is:
StochasticGradientDescent

It inherits from:
GradientDescentOptimizer

The `optimize()` function receives the input features, actual output values and initial weights, then returns the updated parameters.

## Example

Consider a simple linear regression problem:

**y = 2 + 3x**

The expected parameters are:

- Bias = 2
- Weight = 3

The algorithm starts with initial parameter values and gradually learns the appropriate bias and weight from the training data.

The following shows how an SGD object can be created:

StochasticGradientDescent optimizer(0.01, 1000);

vector<double> result = optimizer.optimize(
    x, y, weights
);


After training, the resulting parameters should approach the expected values.

## Testing

The module includes a test program located in:

`tests/test_stochastic_gradient_descent.cpp`

The tests cover six different scenarios:

1. Simple linear regression.
2. Multiple linear regression.
3. Zero iterations.
4. Empty training dataset.
5. Mismatched input and output sizes.
6. Invalid learning rate.

These tests help verify that the algorithm works correctly under normal conditions and handles some invalid inputs appropriately.

### Running the Tests

From the project root directory, compile in IDE terminal using:

**g++ -std=c++17 -Wall -Wextra -Iinclude src/stochastic_gradient_descent.cpp tests/test_stochastic_gradient_descent.cpp -o test_sgd.exe**


Run the executable:

**./test_sgd.exe**

A successful test run should report something like:

Passed: 6 | Failed: 0


## Advantages

- Updates parameters after processing each individual sample.
- Can be useful when working with large datasets.
- Makes frequent updates during training.
- Supports multiple input features.
- Uses an extensible object-oriented design.

## Limitations

- Parameter updates can fluctuate because they are based on individual samples.
- May not converge smoothly to the optimal parameters.
- Performance depends on selecting a suitable learning rate.
- Results can vary depending on sample ordering and the number of iterations.

## Conclusion

Stochastic Gradient Descent provides an alternative approach to training linear regression models.

By updating parameters after each individual training sample, it allows the model to learn continuously without waiting for the entire dataset to be processed before every update.

The class-based implementation also demonstrates how object-oriented programming can be used to create reusable and extensible components in a machine learning project.