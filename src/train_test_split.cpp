#include "machine_learning_1/train_test_split.hpp"
#include <random>
#include <algorithm>
#include <numeric>
#include <stdexcept>

namespace ml_library {
        
    void TrainTestSplitter::validateInputs(std::size_t data_size, double test_ratio) {
        //runtime validation check
        if (data_size < 2) {
            throw std::invalid_argument("Dataset size must be at least 2 to perform a train/test split.");
        }
        if (test_ratio <= 0.0 || test_ratio >= 1.0){
            throw std::out_of_range("Test ratio must be strictly between 0.0 and 1.0 (exclusive).");
        }
   }

   template <Numeric T>
   SplitResult<T> TrainTestSplitter::split(const std::vector<T>& data, double test_ratio, unsigned int seed) {
    validateInputs(data.size(), test_ratio);
    
    std::size_t total_size = data.size();
    std::vector<std::size_t> indices(total_size);
    std::iota(indices.begin(), indices.end(), 0);

    std::mt19937 generator(seed);
    std::shuffle(indices.begin(), indices.end(), generator);

    std::size_t test_size = static_cast<std::size_t>(total_size*test_ratio);
    std::size_t train_size = total_size - test_size;

    SplitResult<T> result;
    result.train_data.reserve(train_size);
    result.test_data.reserve(test_size);

    for (std::size_t i = 0; i < train_size; ++i) {
        result.train_data.push_back(data[indices[i]]);
    }
    for (std::size_t i = train_size; i < total_size; ++i) {
            result.test_data.push_back(data[indices[i]]);
    }

        return result;
    }

    template <Numeric FeatureT, Numeric TargetT>
    std::pair<SplitResult<FeatureT>, SplitResult<TargetT>> TrainTestSplitter::splitPaired(
        const std::vector<FeatureT>& X, 
        const std::vector<TargetT>& y, 
        double test_ratio, 
        unsigned int seed
    ) {
        if (X.size() != y.size()) {
            throw std::invalid_argument("Feature vector X and target vector y must have the exact same size.");
        }
        validateInputs(X.size(), test_ratio);

        std::size_t total_size = X.size();
        std::vector<std::size_t> indices(total_size);
        std::iota(indices.begin(), indices.end(), 0);

        std::mt19937 generator(seed);
        std::shuffle(indices.begin(), indices.end(), generator);

        std::size_t test_size = static_cast<std::size_t>(total_size * test_ratio);
        std::size_t train_size = total_size - test_size;

        SplitResult<FeatureT> X_split;
        SplitResult<TargetT> y_split;

        X_split.train_data.reserve(train_size);
        X_split.test_data.reserve(test_size);
        y_split.train_data.reserve(train_size);
        y_split.test_data.reserve(test_size);

        for (std::size_t i = 0; i < train_size; ++i) {
            X_split.train_data.push_back(X[indices[i]]);
            y_split.train_data.push_back(y[indices[i]]);
        }
        for (std::size_t i = train_size; i < total_size; ++i) {
            X_split.test_data.push_back(X[indices[i]]);
            y_split.test_data.push_back(y[indices[i]]);
        }

        return {X_split, y_split};
    }

    // ============================================================================
    // Explicit Template Instantiations (Allows .cpp compilation for numbers)
    // ============================================================================
    template SplitResult<double> TrainTestSplitter::split(const std::vector<double>&, double, unsigned int);
    template SplitResult<float> TrainTestSplitter::split(const std::vector<float>&, double, unsigned int);
    template SplitResult<int> TrainTestSplitter::split(const std::vector<int>&, double, unsigned int);

    template std::pair<SplitResult<double>, SplitResult<double>> TrainTestSplitter::splitPaired(const std::vector<double>&, const std::vector<double>&, double, unsigned int);
    template std::pair<SplitResult<int>, SplitResult<double>> TrainTestSplitter::splitPaired(const std::vector<int>&, const std::vector<double>&, double, unsigned int);
    template std::pair<SplitResult<float>, SplitResult<short>> TrainTestSplitter::splitPaired(const std::vector<float>&, const std::vector<short>&, double, unsigned int);

} // namespace ml_library
