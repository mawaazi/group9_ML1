# Group 9 Machine Learning 1: Linear Regression from Scratch. A C++ Library.
A lightweight, modern C++23 library implementing **Linear Regression from scratch**, complete with mathematical statistics, optimization algorithms, data sampling tools, automated testing, and executable test and example files for each model once the library is built.

---

## Table of Contents
- [Contributions by Group Members](#contributions-by-group-members)
- [Project Name and Description](#project-name-and-description)
- [Project Objectives](#project-objectives)
- [Main Features](#main-features)
- [Project Structure](#project-structure)
- [Some OOP Concepts Used In Our Library](#some-oop-concepts-used-in-our-library)
- [An overview of the Library](#an-overview-of-the-library)
- [Requirements and Dependencies](#requirements-and-dependencies)
- [Installation or Build Instructions](#installation-or-build-instructions)
- [How to Use the Library](#how-to-use-the-library)
- [Examples](#examples)
- [How to Run the Tests](#how-to-run-the-tests)
- [Limitations](#limitations)
- [References](#references)
- [AI Clause for Entire project](#ai-clause-for-entire-project)
- [Proof of contribution](#proof-of-contribution)

---
## Contributions by Group Members

| Member Name | Assigned Modules / Key Tasks |
| :--- | :--- |
| **Mawaazi Abdulrahman** | Project Lead / `TrainTestSplit` & `StatisticalSignificance` modules / Unified CMake & CTest architecture / Weekly & General Reports |
| **Chelangat Faith** | Standard Error Estimation (`standard_error_estimation.hpp`) & Closed Form matrix equations (`closed_form.hpp`) |
| **Nakyobe Geogin Martha** | Batch Gradient Descent & Stochastic Gradient Descent (`gradient_descent.hpp`) |
| **Nantongo Melanie** | Multiple Linear Regression, Batch Gradient Descent (`gradient_descent.cpp`) & Standard Error Estimation|
| **[MEMBER 5 NAME]** | Standard Error of Estimation & Prediction Intervals (`standard_error.hpp`) |
| **[MEMBER 6 NAME]** | Overcoming Overfitting using SMOTE data resampling (`smote.hpp`) |
| **[MEMBER 7 NAME]** | Multiple Linear Regression matrix solver formulation |

Back to [Table of Contents](#table-of-contents)

## Project Name and Description

**Library Name:** `machine_learning_1`

This project provides a portable, modular C++23 machine learning library focused on single and multiple linear regression algorithms. Built completely from first principles without external linear algebra libraries, it encapsulates numerical optimization, data sampling (SMOTE), statistical significance validation, and evaluation metrics behind a clean public API.

Back to [Table of Contents](#table-of-contents)
---

## Project Objectives

1. **Object-Oriented & Modular Design:** Separate public interfaces (`include/`) from core implementations (`src/`) across distinct mathematical modules.
2. **First-Principles Implementation:** Develop matrix operations, gradient descent variants, standard errors, and sampling algorithms using standard C++ structures.
3. **Automated Testing & Build Automation:** Maintain a unified `CMakeLists.txt` build system integrated with CTest for test execution.
4. **Error Handling & Type Safety:** Enforce compile-time type validation (`std::is_floating_point_v`) and runtime exception safety against invalid datasets (`NaN`, `Inf`, zero variance).

Back to [Table of Contents](#table-of-contents)
---

## Main Features

- **Ordinary Least Squares (OLS) & Closed-Form Matrix Solver:** Analytical solutions using standard linear equations and matrix normal equations ($\boldsymbol{\beta} = (\mathbf{X}^T\mathbf{X})^{-1}\mathbf{X}^T\mathbf{y}$).
- **Optimization Algorithms:** Batch Gradient Descent and Stochastic Gradient Descent (SGD).
- **Statistical Evaluation Metrics:**
  - Pearson Correlation Coefficient ($r$)
  - Coefficient of Determination ($R^2$) with template precision support
  - Slope Statistical Significance ($t$-statistic, standard error of slope, degrees of freedom)
  - Standard Error of Estimation ($S_{y \cdot x}$) & Prediction Intervals
- **Data Preprocessing & Resampling:**
  - Seeded Train/Test Index Partitioning (`TrainTestSplit`)
  - Synthetic Minority Over-sampling Technique (SMOTE) for imbalanced data handling
- **Command-Line Applications:** Executable files with preset datasets to evaluate our models.

Back to [Table of Contents](#table-of-contents)
---

## Project Structure

```text
group9_ML1/
├──.vscode/
├── CMakeLists.txt
├── LICENSE
├── README.md
├── .gitignore
├── include/
│   └── machine_learning_1/
│       ├── best_fit.hpp
│       ├── closed_form.hpp
│       ├── coefficient_of_determination.h
│       ├── correlation_coefficient.hpp
│       ├── gradient_descent.hpp
│       ├── ml_error.hpp
|       ├── ml_pipeline.hpp 
|       ├── prediction_interval.hpp
|       ├── smote.hpp
|       ├── standard_error_estimation.hpp
│       ├── statistical_significance.hpp 
│       ├── stochastic_gradient_descent.hpp
│       └── train_test_split.hpp
├── src/
│   ├── best_fit.cpp
│   ├── closed_form.cpp
|   ├── coefficient_of_determination.cpp
│   ├── correlation_coefficient.cpp
│   ├── gradient_descent.cpp
│   ├── ml_error.cpp
|   ├── ml_pipeline.cpp
|   ├── prediction_interval.cpp
|   ├── main.cpp
|   ├── standard_error_estimation.cpp
│   ├── statistical_significance.cpp
|   ├── stochastic_gradient_descent.cpp
│   └── train_test_split.cpp
├── tests/
|   ├── test_line_of_best_fit.cpp
│   ├── test_closed_form.cpp
|   ├── test_module1.cpp
|   ├── test_r2_unit.cpp
|   ├── test_coefficient_of_determination.cpp
│   ├── test_correlation_coefficient.cpp
│   ├── test_gradient_descent.cpp
│   ├── test_smote_day1.cpp
|   ├── test_smote_day2.cpp
|   ├── test_prediction_interval.cpp
|   ├── test_smote_day3.cpp
|   ├── test_standard_error.cpp
│   ├── test_statistical_significance.cpp
|   ├── test_stochastic_gradient_descent.cpp
│   └── test_train_test_split.cpp
|
├── examples/
│   ├── significance_example.cpp
|   ├── SDG_example.cpp
|   ├── closed_form_example.cpp
|   ├── gradient_descent_example.cpp
|   ├── standard_error_example.cpp
|   ├── test_r2.cpp
│   └── train_test_split_example.cpp
└── reports/
    ├── week-01.md
    ├── week-02.md
    ├── week-03.md
    ├── week-04.md
    └── General_report.md
```

Back to [Table of Contents](#table-of-contents)
---

## OOP Concepts Used in Our Library

### 1. Compile-Time Parametric Polymorphism (Templates)
Metrics like `coefficient_of_determination<T>` use C++ type-traits (`std::is_floating_point_v<T>`) to support `float`, `double`, and `long double` natively without code duplication.

### 2. Encapsulation & Guarded Data Invariants
Classes like `Correlation` guard paired dataset vectors (`xValues`, `yValues`) privately, enforcing validation during object construction.

---

## Shared Internal Helpers and Error System

To ensure DRY (Don't Repeat Yourself) compliance, validation routines live in `src/internal/input_checks.cpp`:
* `check_equal_sizes(x, y)`: Asserts length parity.
* `check_finite_values(v)`: Uses `std::isfinite` to trap `NaN` and `Inf` inputs early.
* `check_non_zero_variance(v)`: Guards against divide-by-zero errors when total sum of squares ($SS_{tot}$) is zero.

Back to [Table of Contents](#table-of-contents)
---

## An overview of the library

| Module / Topic | Class / Function Interface | Core Functionality |
| :--- | :--- | :--- |
| **Line of Best Fit** | `calculateBestFit(x, y)` | Ordinary Least Squares (OLS) simple slope and intercept. |
| **Closed Form Equation** | `fit(X, y)`, `predict(coeffs, x)` | Matrix normal equations: $\boldsymbol{\beta} = (\mathbf{X}^T\mathbf{X})^{-1}\mathbf{X}^T\mathbf{y}$. |
| **Gradient Descent** | `computeGradientDescent(...)` | Batch gradient descent optimization over weights. |
| **Stochastic GD** | `computeSGD(...)` | Iterative single-sample weight optimization. |
| **Correlation** | `Correlation::pearson(x, y)` | Pearson $r$ calculation with static and stateful overloads. |
| **R² Determination** | `coefficient_of_determination<T>(y, y_hat)` | Single-pass template calculation for variance explained ($R^2$). |
| **Statistical Significance** | `evaluateSlopeSignificance(x, y, slope)` | Standard error of slope, t-statistics, degrees of freedom, and significance checks. |
| **Standard Error & Intervals** | `calculateStandardError(...)`, `predictionInterval(...)` | Residual standard deviation ($S_{y\cdot x}$) and point prediction interval bounds. |
| **Train/Test Split** | `TrainTestSplitter::splitPaired(...)` | Stratified/seeded index partitioning into training and validation sets. |
| **SMOTE Overfitting** | `applySMOTE(...)` | Synthetic Minority Over-sampling Technique to balance skewed training data. |
| **Multiple Regression** | `MultipleLinearRegression::fit(...)` | Extension to multi-feature continuous regression. |

Back to [Table of Contents](#table-of-contents)
---

## Requirements and Dependencies

- **Compiler:** GCC 13+ / MinGW-w64 13+ or Clang 16+ (requires C++23 standard support).
- **Build System:** CMake version 3.20 or newer.
- **Generator:** `MinGW Makefiles` (Windows) or standard Unix Makefiles (macOS/Linux).
- **External Dependencies:** None. Standard C++ Library only (`std::vector`, `std::cmath`, `std::concepts`).

Back to [Table of Contents](#table-of-contents)
---

## Installation or Build Instructions

### 1. Build the Library and executable files for tests and examples.

#### On Windows (PowerShell / Command Prompt using MinGW):
```powershell
# Configure build directory
cmake -S . -B build -G "MinGW Makefiles"

# Compile library, examples and tests.
cmake --build build
```

#### On Linux / macOS:
```bash
cmake -S . -B build
cmake --build build -j$(nproc)
```

### 2. Run the desired .exe files
After building, run any test or example .exe file (check the build folder):
```powershell
.\build\test_line_of_best_fit.exe
```
Back to [Table of Contents](#table-of-contents)
---

## How to Use the Library

Link `machine_learning_1` inside your own C++ project using CMake or compiler include paths.

### Basic C++ Code Example

```cpp
#include <iostream>
#include <vector>
#include "machine_learning_1/best_fit.hpp"
#include "machine_learning_1/statistical_significance.hpp"
#include "machine_learning_1/coefficient_of_determination.h"

int main() {
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y = {2.1, 4.1, 5.9, 8.0, 10.1};

    // 1. Calculate Ordinary Least Squares (OLS) line of best fit
    LineParameters line = calculateBestFit(x, y);
    std::cout << "Slope: " << line.slope << ", Intercept: " << line.intercept << "\n";

    // 2. Evaluate statistical significance of the slope
    auto sig = ml_library::StatisticalSignificance::evaluateSlopeSignificance(x, y, line.slope);
    std::cout << "t-Statistic: " << sig.t_statistic << "\n";
    std::cout << "Significant: " << (sig.is_significant ? "Yes" : "No") << "\n";

    return 0;
}
```
Back to [Table of Contents](#table-of-contents)
---

## Examples

Pre-built executable examples demonstrating modular features are located in the `build` folder:

1. **Train/Test Split Example:**
   ```powershell
   .\build\train_test_split_example.exe
   ```
2. **Statistical Significance Example:**
   ```powershell
   .\build\significance_example.exe
   ```
Back to [Table of Contents](#table-of-contents)
---

## How to Run the Tests

Automated unit tests use CTest to evaluate normal execution paths, boundary conditions, and invalid inputs.

Run all tests via CTest:
```powershell
cd build
ctest --output-on-failure
```

Or run individual test binaries directly:
```powershell
.\build\test_train_test_split.exe
.\build\test_statistical_significance.exe
```
Back to [Table of Contents](#table-of-contents)
---

## Limitations

1. **Zero Variance Datasets:** Evaluation metrics ($R^2$, Pearson $r$) are mathematically undefined when target vectors have zero variance ($SS_{tot} = 0$). The library throws `ml1::InvalidInputError` in these cases.
2. **Multicollinearity in Normal Equations:** High correlation between feature columns can render $(X^T X)$ singular during matrix inversion. Gradient Descent should be used for collinear datasets.
3. **Feature Scaling Requirement:** Gradient Descent variants (Batch GD & SGD) require standardized feature scaling to guarantee optimal convergence rates.

Back to [Table of Contents](#table-of-contents)
---

## References

1. T. Hastie, R. Tibshirani, and J. Friedman, *The Elements of Statistical Learning*, 2nd ed., Springer, 2009.
2. N. R. Draper and H. Smith, *Applied Regression Analysis*, 3rd ed., Wiley-Interscience, 1998.
3. B. Stroustrup, *The C++ Programming Language*, 4th ed., Addison-Wesley, 2013.
4. N. V. Chawla et al., "SMOTE: Synthetic Minority Over-sampling Technique," *Journal of Artificial Intelligence Research*, vol. 16, pp. 321–357, 2002.
5. ISO/IEC 14882:2023, *Information technology — Programming languages — C++*, 2023.

Back to [Table of Contents](#table-of-contents)
---

## AI Clause for Entire Project

In accordance with the project guidelines, AI tools were utilized solely as supporting mechanisms for debugging, CMake syntax verification, and testing framework setup:

* **Week 1 Progress Report:** AI Clause logged in `reports/week-01.md`.
* **Week 2 Progress Report:** AI Clause logged in `reports/week-02.md`.
* **Week 3 Progress Report:** AI Clause logged in `reports/week-03.md`.
* **Week 4 Progress Report:** AI Clause logged in `reports/week-04.md`.
* **Final Submission Summary:** Gemini AI was utilized to assist in troubleshooting CMake generator flags, configuring CTest targets, and structuring the markdown reports. Most core mathematical logic, C++ implementations, and architectural decisions were authored, tested, and verified directly by the group memberss.

Back to [Table of Contents](#table-of-contents)
---

## Proof of Contribution

You can view individual member commits on our official GitHub Repository:
* View contributions by **Mawaazi Abdulrahman**: [Commits by mawaazi](https://github.com/mawaazi/group9_ML1/commits/main?author=mawaazi&before=c522143e4e564744434ec8f4f80bf46a6b09cb4a+35)
* View contributions by **Chelangat Faith**: [Commits by chela](https://github.com/mawaazi/group9_ML1/commits/main?author=Chelangat-faith)
* View contributions by **Nakyobe Geogin Martha**: [Commits by geogin](https://github.com/mawaazi/group9_ML1/commits/main?author=geo2104)
* View contributions by **Nantongo Melanie**: [Commits by melanie](https://github.com/mawaazi/group9_ML1/commits/main?author=nmelanie-ui)
* View contributions by **[MEMBER 5]**: [Commits by MEMBER 5](https://github.com/[YOUR-ORG]/group9_ML1/commits/main?author=[USERNAME])
* View contributions by **[MEMBER 6]**: [Commits by MEMBER 6](https://github.com/[YOUR-ORG]/group9_ML1/commits/main?author=[USERNAME])
* View contributions by **[MEMBER 7]**: [Commits by MEMBER 7](https://github.com/[YOUR-ORG]/group9_ML1/commits/main?author=[USERNAME])

Back to [Table of Contents](#table-of-contents)
