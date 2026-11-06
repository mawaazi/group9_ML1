# Week 4 Report – Correlation Coefficient Module

**Group:** Group 9 – Machine Learning 1  
**Contributor:** Perry  
**Module:** Pearson Correlation Coefficient  
**Programming Language:** C++

## 1. Introduction

During Week 4, I worked on the Correlation Coefficient module of our Machine Learning 1 project. The purpose of this module is to calculate Pearson's correlation coefficient, which measures the strength and direction of a linear relationship between two sets of numerical data.

The coefficient ranges from -1 to +1. A value close to +1 indicates a strong positive relationship, a value close to -1 indicates a strong negative relationship, and a value close to zero indicates little or no linear relationship.

## 2. Work Completed

My contribution focused on developing and documenting the Correlation Coefficient module.

The work included:

- Creating the header file containing the class declaration and public interface.
- Implementing the correlation calculations in the source file.
- Adding input validation to reject invalid datasets.
- Writing tests to verify the calculations and error handling.
- Adding documentation to the project's README.
- Preparing a separate example program to demonstrate how the module is used.

## 3. Implementation

The module was developed using C++17 and object-oriented programming principles.

The `Correlation` class groups the data and related operations together. Encapsulation is applied by keeping the datasets private and providing public functions to calculate the correlation coefficient.

The calculation follows Pearson's correlation formula:

r = Σ[(x − x̄)(y − ȳ)] / √[Σ(x − x̄)² × Σ(y − ȳ)²]

The implementation also uses scaling and `long double` arithmetic to reduce numerical problems when handling large values.

## 4. Input Validation

Input validation was included to improve the reliability of the module.

The program checks that both datasets contain the same number of elements, have at least two paired observations, contain finite numerical values, and have nonzero variance.

Invalid inputs are handled using `std::invalid_argument` exceptions.

## 5. Testing

The module was tested using different datasets and conditions, including positive correlation, negative correlation, invalid inputs, and large numerical values.

During the earlier testing stage, the module successfully passed all 21 test checks.

An additional example program was prepared using the datasets:

- X = {1, 2, 3}
- Y = {40, 50, 60}

These datasets have a perfect positive linear relationship, so the expected correlation coefficient is 1.

## 6. C++ Concepts Applied

The implementation demonstrates several C++ concepts:

- **Classes and objects:** Used to organize the correlation data and calculations.
- **Encapsulation:** Used to protect the stored datasets.
- **Vectors:** Used to store numerical values.
- **Functions:** Used to separate the calculation and validation operations.
- **Exception handling:** Used to reject invalid inputs.
- **Header and source files:** Used to separate declarations from implementation.
- **Standard library:** Used for mathematical operations and numerical handling.

## 7. Challenges Encountered

Some of the challenges included resolving compilation issues, correcting header file locations, and ensuring that the module followed the group's folder structure.

These issues were addressed by adjusting the file paths, reviewing the source code, and testing the implementation.

## 8. Conclusion

The Correlation Coefficient module provides a reusable way to calculate Pearson's correlation coefficient in C++.

The main implementation and testing were completed, and the module was documented for integration into the group project. A separate example program was also prepared to demonstrate its usage.

## 9. AI Assistance

ChatGPT was used to assist with parts of the code, documentation, debugging, and explanations. The implementation was reviewed and tested in VS Code.