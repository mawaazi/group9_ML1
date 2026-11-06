# SMOTE Development Report — Day 1
**Author:** BORIT DERRICK SIWA
**Library:** Machine Learning 1 (ML1) — SMOTE (Synthetic Minority Over-sampling Technique)
**Focus:** Data Structures, Distance Metrics, and K-Nearest Neighbors (KNN)

## 1. Goal for Day 1
To establish the mathematical foundation for the SMOTE algorithm. SMOTE works by finding the nearest neighbors of a minority class point and generating synthetic points between them. Therefore, Day 1 focuses on defining the dataset structure, calculating Euclidean distances, and finding those nearest neighbors.

## 2. Implementation Details
- **Data Structure:** Created a `Dataset` struct to neatly hold `features` (X values) and `labels` (Y values).
- **Distance Metric:** Implemented `euclidean_distance()`. It calculates the straight-line distance between two feature vectors, which is essential for determining how close data points are in multi-dimensional space.
- **K-Nearest Neighbors:** Implemented `find_k_nearest_neighbors()`. This function:
  1. Iterates through all minority class points.
  2. Computes the distance from a target point to every other point.
  3. Sorts the distances in ascending order.
  4. Returns the top `k` closest points.

## 3. Safety & Error Handling
- Added a size mismatch check in the distance function to ensure vectors are comparable.
- Added a boundary check in the KNN function to ensure `k` is not larger than the number of available minority samples (which would cause an out-of-bounds error).

## 4. Testing
Compiled with `g++ -std=c++23`.
Tested with a 2D dataset:
- Point 0: (1, 1)
- Point 1: (2, 2)
- Point 2: (10, 10)

**Verification:**
- The Euclidean distance between Point 0 and Point 1 was correctly calculated as `1.41421`.
- The algorithm correctly identified Point 1 as the nearest neighbor to Point 0.

## 5. Next Steps (Day 2)
With the neighbor-finding logic proven to work, Day 2 will focus on the core SMOTE generator: taking a point, picking a neighbor, generating a random interpolation factor (\(\lambda\)), and creating the synthetic data point.
