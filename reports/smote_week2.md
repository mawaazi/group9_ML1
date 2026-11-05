# SMOTE Development Report — week 2
**Author:** BORIT DERRICK SIWA
**Focus:** Core SMOTE Generation Algorithm

## 1. Goal for week 2
To implement the core SMOTE logic: separating the dataset by class, finding nearest neighbors, and generating synthetic data points to balance the dataset.

## 2. Implementation Details
- **Class Separation:** The function first separates the indices of the minority (0) and majority (1) classes.
- **Balancing Logic:** It calculates exactly how many synthetic points are needed (`majority_size - minority_size`).
- **Randomization:** Used `<random>` (`std::mt19937`) for high-quality randomness.
- **Synthetic Generation:** For each new point:
  1. Randomly selects a base minority point.
  2. Finds its `k` nearest neighbors.
  3. Randomly selects one neighbor.
  4. Generates a random `lambda` between 0.0 and 1.0.
  5. Interpolates: `new_point = base + lambda * (neighbor - base)`.

## 3. Testing
Created a mock dataset with 3 minority points and 5 majority points. 
- Before SMOTE: 3 minority, 5 majority.
- After SMOTE: 5 minority, 5 majority.
- Verified that the new synthetic points are correctly interpolated between the existing minority points (e.g., values like 1.15 are between 1.0 and 2.0).

## 4. Next Steps (week 3)
Final integration. We will add a check to ensure the algorithm can handle multiple features (multi-dimensional data) and create the final unit test suite.