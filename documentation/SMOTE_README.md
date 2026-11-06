# SMOTE (Synthetic Minority Over-sampling Techique)

## 1. Project Description
SMOTE is a data preprocessing algorithm used to handle imbalanced datasets in machine learning. instead of simply duplicating minority class examples (which causes overfitting), SMOTE generates *new, synthetic* minority class instances by interpolating between existing minority points and their nearest neighbours.  

## 2. Main Features
- Balances binary classification datasets automatically. 
- Finds \(k\)-nearest neighbors using Euclidean distance.
- Generates synthetic data in N-dimensional space (works with any number of features).
- Safe random generation using `<random>` and Mersenne Twister (`std::mt19937`).

## 3. Requirements and Dependencies
- **C++ Standard:** C++17 or higher (compiled with `-std=c++23`).
- **Dependencies: ** Standard Template Library (`<vector>`, `<cmath>`, `<algorithm>`, `<random>`) and the ML1 library's `ml_error.hpp`.

## 4. How to Use the Library
Include the header in your C++ file:
```cpp
#include "machine_learning_1/smote.hpp"