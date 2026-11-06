Correlation Coefficient Library
This is a reusable C++17 library which can be used to calculate Pearson’s correlation coefficients between two paired data sets. The result will vary between -1 and +1 and indicates how strong the linear relationship is between two variables. A correlation does not imply causation.
Concepts Used
The library uses a Correlation class to encapsulate the calculation, including constructors, vectors, constant references, member and static functions, error handling and the statistics namespace.
Project Structure
File	Description
include/machine_learning_1/correlation_coefficient.hpp	Contains the Correlation class declaration.
src/correlation_coefficient.cpp	Implements Pearson's correlation coefficient and input validation.
tests/test_correlation_coefficient.cpp	Tests the calculations and error handling.

Installation
This project requires a C++17 compiler.
g++ -std=c++17 -Iinclude src/correlation_coefficient.cpp tests/test_correlation_coefficient.cpp -o test_correlation.exe

.\test_correlation.exe


Run the compilation command from the project's main folder. On Windows, use .\test_correlation.exe to execute the tests. All 21 checks passed successfully.

Alternatively you can use CMake (v3.16 or newer):
cmake -S . -B build

cmake --build build --config Release

ctest --test-dir build -C Release --output-on-failure


How to Use
#include "machine_learning_1/correlation_coefficient.hpp"
#include <iostream>
#include <vector>

int main() {
    std::vector<double> x{1, 2, 3};
    std::vector<double> y{40, 50, 60};

    statistics::Correlation data(x, y);

    double r = data.coefficient();

    std::cout << r << '\n';
    return 0;
}


The data sets are stored as copies within the object. If you want to calculate the correlation without storing it inside an object use statistics::Correlation::pearson(x, y).
Calculations and Validation
The correlation coefficient can be calculated using the following formula:
\[
r = \frac{\sum (x-\bar{x})(y-\bar{y})}{\sqrt{\sum(x-\bar{x})^2\sum(y-\bar{y})^2}}
\]

The data sets must be the same size, have a minimum of 2 pairs of data, have finite values and have variance in both sets. If any of these are not met then std::invalid_argument will be thrown when calculating the correlation.

The calculations use scaling and long double to reduce the risk of overflow when working with large numbers. The final correlation coefficient is restricted to values between -1 and +1 using std::max and std::min. The algorithm runs in linear time with constant extra space, while creating an object requires linear space to store the datasets.
Testing and Limitations
There are tests that check different types of correlations, large numbers, invalid data and object behaviour. This only supports Pearson’s correlation. File importing, missing value handling, visualisations and significance testing have not been included.
Contributions and AI Use
My contribution to the group project was the implementation of the Correlation Coefficient module, including its class structure, calculations, input validation and testing. The module successfully passed all 21 test checks.

ChatGPT was used to assist with parts of the code, documentation, debugging and explanations. The code was compiled and tested in VS Code.