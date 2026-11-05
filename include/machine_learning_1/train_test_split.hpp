#ifndef TRAIN_TEST_SPLIT_HPP_INCLUDED
#define TRAIN_TEST_SPLIT_HPP_INCLUDED

#include <vector>
#include <utility> //Provides std::pair<T1, T2>, required by splitPaired() to return a pair of SplitResult structs (X split and y split) in a single unified return value
#include <concepts> //Provides C++20/C++23 fundamental language concepts (std::integral, std::floating_point) to constrain template parameters at compile time.
#include <stdexcept> //Provides std::invalid_argument and std::out_of_range exception classes for runtime input validation.
#include <cstddef> //Provides std::size_t, ensuring portable, architecture-independent integer types for array indexing and memory allocations.

namespace ml_library {
    
    //restricting data types strictly to numbers(int, float, double, short, etc)
    template <typename T>
    concept Numeric = std::integral<T> || std::floating_point<T>;

    //this struct is for holding the trainng and testing dataa partions
    template <Numeric T>
    struct SplitResult {
        std::vector<T> train_data;
        std::vector<T> test_data;
    };

    //this class splits datasets into training and testing subsets
    class TrainTestSplitter {
        public:
            //splits a single dataset vector into train and test subsets
            /// @param data the complete input dataset
            /// @param test_ratio fraction of data reserrved for testing e.g 0.2 for 20%
            /// @param seed he optional random seed for reproducible shuffling
            /// @return SplitResult(struct) containing train aand test vectors
            template <Numeric T>
            static SplitResult<T> split(const std::vector<T>& data, double test_ratio, unsigned int seed = 42);
            
            //Splits paired feature vectors (X) and target vectors (y) simultaneously. 
            template <Numeric FeatureT, Numeric TargetT> 
            static std::pair<SplitResult<FeatureT>, SplitResult<TargetT>> splitPaired(
                const std::vector<FeatureT>& X,
                const std::vector<TargetT>& y,
                double test_ratio,
                unsigned int seed = 42
            );
        
        private:
        //this helper function ensures inputs are valid numerical data and sizes. throws invalid-argument if violated
        static void validateInputs(std::size_t data_size, double test_ratio);    
    };


} // namespace ml_library
#endif // ML_LIBRARY_TRAIN_TEST_SPLIT_HPP