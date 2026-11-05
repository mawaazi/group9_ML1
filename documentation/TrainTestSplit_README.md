# Train/Test Splitter (`ml_library`)

## 1. Overview & Theory
In machine learning, evaluating a model on the same data it was trained on leads to **overfitting**—the model simply memorizes the data rather than learning the underlying patterns. The standard solution is the **Train/Test Split**.

This module provides a robust, reproducible mechanism for partitioning datasets into two subsets:
*   **Training Set:** Used to train the model (e.g., calculate linear regression weights).
*   **Test Set:** Held back to evaluate the model's performance on unseen data.

To prevent bias (e.g., if data is sorted by house price), the dataset must be shuffled randomly before splitting. To ensure **reproducibility** (so experiments can be repeated and graded consistently), the shuffling uses a deterministic pseudo-random number generator (PRNG) initialized with a user-defined `seed`.

## 2. Main Features & API Functions

The `TrainTestSplitter` class provides a streamlined, stateless API for data partitioning. It exposes two primary public methods and relies on one private validation method.

### 2.1 The Data Container: `SplitResult<T>`
Before detailing the functions, it is important to note the return type. Both public functions return data wrapped in a `SplitResult<T>` struct. 
*   **Purpose:** A lightweight, generic structure containing two public `std::vector<T>` members: `train_data` and `test_data`. It ensures that whenever a split is performed, both the training and testing partitions are returned to the user in a single, clean object.

### 2.2 Single Dataset Split: `split()`
```cpp
template <Numeric T>
static SplitResult<T> split(const std::vector<T>& data, double test_ratio, unsigned int seed = 42);
```
*   **Purpose:** Splits a single 1-dimensional dataset (e.g., a standalone array of house prices) into training and testing subsets.
*   **How it works:** It creates a vector of indices `[0, 1, 2... N-1]`, shuffles them using `std::mt19937` (seeded for reproducibility), and calculates the `test_size`. It then iterates through the shuffled indices, pushing the first segment into `train_data` and the remaining segment into `test_data`.
*   **Parameters:**
    *   `data`: A constant reference to the input vector. `const&` prevents expensive copies and ensures the original data is not mutated.
    *   `test_ratio`: A double (e.g., `0.2`) representing the percentage of data reserved for testing.
    *   `seed`: An `unsigned int` defaulting to `42`. Ensures the random shuffle is identical every time the code is run.

### 2.3 Paired Dataset Split: `splitPaired()`
```cpp
template <Numeric FeatureT, Numeric TargetT> 
static std::pair<SplitResult<FeatureT>, SplitResult<TargetT>> splitPaired(
    const std::vector<FeatureT>& X, const std::vector<TargetT>& y, double test_ratio, unsigned int seed = 42);
```
*   **Purpose:** The core machine learning function. It splits features (`X`) and targets (`y`) simultaneously, guaranteeing that the row alignment between a feature and its corresponding label is never broken.
*   **How it works:** It first checks if `X.size() == y.size()`. Then, it generates a **single** array of shuffled indices. It uses these exact same indices to pull data from both `X` and `y`. If index `5` goes to the training set for `X`, index `5` also goes to the training set for `y`.
*   **Returns:** A `std::pair` containing two `SplitResult` objects—one for the features and one for the targets. 

### 2.4 Input Validation: `validateInputs()` (Private)
```cpp
static void validateInputs(std::size_t data_size, double test_ratio);
```
*   **Purpose:** Acts as a defensive guard to prevent undefined behavior or mathematical impossibilities during the split.
*   **How it works:** It checks two conditions:
    1.  If the dataset size is less than 2, it throws a `std::invalid_argument` (you cannot split a single item into two groups).
    2.  If the `test_ratio` is `<= 0.0` or `>= 1.0`, it throws a `std::out_of_range` (you must leave at least one item for training and one for testing).
*   **Encapsulation:** It is marked `private` because it is an internal safety mechanism. The end-user does not need to call this directly; it is automatically called by `split` and `splitPaired`.

## 3. OOP Design & Reasoning
The architecture prioritizes safety, reusability, and performance. 

*   **Stateless Utility Class (`TrainTestSplitter`)**: The class contains no member variables and no state. Therefore, all methods are declared `static`. You do not need to instantiate an object (`TrainTestSplitter splitter;`) to use it; you simply call `TrainTestSplitter::split(...)`. 
*   **Data Carrier (`SplitResult<T>`)**: A `struct` is used to group the resulting `train_data` and `test_data` vectors. It is kept public and lightweight, serving purely as a return type.
*   **Encapsulation & Separation of Concerns**: The core logic is hidden inside a `.cpp` file, while the `.hpp` file only exposes the public interface and documentation. Internal validation (`validateInputs`) is kept strictly `private`.
*   **The "Index Shuffling" Strategy**: Instead of shuffling the raw data vectors directly, the algorithm creates an array of indices `[0, 1, 2... N-1]`, shuffles those, and uses them to pull data. 
    *   *Reasoning:* When splitting paired data (`X` and `y`), shuffling `X` and `y` independently destroys their correspondence. By shuffling the *indices* and applying the same shuffled array to both `X` and `y`, we guarantee they remain perfectly aligned.

## 4. C++ Concepts & Implementation (C++20/23)
This module heavily utilizes modern C++ features to enforce compile-time safety and improve performance:

*   **Concepts (`concept Numeric`)**: We restrict the templates strictly to `std::integral` (int, short) and `std::floating_point` (float, double) types. If a user attempts to split a `std::vector<std::string>`, the compiler throws a clean, easily readable error before the program even runs.
*   **Templates**: The code is **type-agnostic**. The same logic handles `float`, `double`, `int`, and `short` seamlessly.
*   **STL Algorithms**:
    *   `std::iota`: Fills the index vector with sequential numbers `[0, 1, 2...]`.
    *   `std::mt19937`: A high-quality Mersenne Twister PRNG, standard in modern C++.
    *   `std::shuffle`: Randomly permutes the indices using the PRNG.
*   **Exception Handling**: Runtime validation (e.g., ensuring dataset size is `>= 2` and ratio is strictly between `0.0` and `1.0`) uses `std::invalid_argument` and `std::out_of_range`.
*   **Explicit Template Instantiations**: Because the implementation is separated into a `.cpp` file, the compiler does not automatically generate machine code for templates (as it doesn't know which types the user will choose). At the bottom of the `.cpp`, we explicitly instantiate the templates for `<double>`, `<float>`, `<int>`, and `<short>`. This keeps the header clean and compile times fast.

## 5. Advantages
*   **Type Safety:** The `Numeric` concept prevents passing non-numeric data at compile time.
*   **Synchronization:** `splitPaired` guarantees that features (`X`) and targets (`y`) are split identically without losing their relational mapping.
*   **Reproducibility:** A default seed (`42`) is provided, but users can change it to generate different splits for Monte Carlo cross-validation.
*   **Performance:** Memory is reserved upfront using `.reserve()` to prevent vector reallocations during the split. Shuffling `std::size_t` indices is much faster than moving heavy data objects in memory.

## 6. Tradeoffs
*   **Explicit Instantiation Requirement:** Because we chose to hide the implementation in a `.cpp` file, the library is restricted to the types explicitly instantiated at the bottom of the file (`double`, `float`, `int`, `short`). If a user tries to use `long double`, they will get a linker error unless they add the instantiation themselves. (A header-only design would fix this but would increase compile times).
*   **Memory Overhead:** The index shuffling requires an extra temporary array of size $N$ (`std::vector<std::size_t> indices`) which takes $O(N)$ memory.

## 7. Testing and Examples
*   **Example (`train_test_split_example.cpp`)**: Demonstrates splitting paired house IDs (Features/`X`) and house prices (Targets/`y`). It wraps the call in a `try-catch` block. If an exception is thrown (e.g., invalid ratio), `e.what()` catches the error and prints it to `std::cerr`.
*   **Tests (`test_train_test_split.cpp`)**: Uses `assert()` to verify that the combined size of the training and testing sets equals the original dataset size, ensuring no data loss occurs during the split. It also tests mixed types (e.g., `float` features and `short` targets) to prove type-agnosticism.

## 8. Limitations
*   **No Stratification:** The current random split does not support stratified sampling (e.g., ensuring the train and test sets have the same percentage of a specific class, which is crucial for classification tasks).
*   **Strict Type Matching:** The `splitPaired` function requires `X` and `y` to be separate vectors. It does not currently support multidimensional feature matrices (e.g., `std::vector<std::vector<double>>`).

## 9. Conclusion
This module provides a highly robust, modern C++ implementation of the machine learning train/test split. By utilizing C++20 concepts, explicit template instantiations, and an innovative index-shuffling algorithm, it guarantees data integrity, compile-time safety, and computational efficiency.
