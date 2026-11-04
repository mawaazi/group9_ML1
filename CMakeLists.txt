cmake_minimum_required(VERSION 3.20)
project(MLLibrary VERSION 1.0.0 LANGUAGES CXX)

# Enforce modern C++23 standard globally
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Tell the compiler where to find public header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Compile your library implementation files together into a static library target
add_library(machine_learning_1 
    src/train_test_split.cpp 
    src/statistical_significance.cpp
)

# Enable CTest runner support
enable_testing()

# ==========================================
# TEST EXECUTABLES
# ==========================================
add_executable(test_train_test_split tests/test_train_test_split.cpp)
target_link_libraries(test_train_test_split PRIVATE machine_learning_1)

add_executable(test_statistical_significance tests/test_statistical_significance.cpp)
target_link_libraries(test_statistical_significance PRIVATE machine_learning_1)

# ==========================================
# EXAMPLE EXECUTABLES
# ==========================================
add_executable(example_split examples/train_test_split_example.cpp)
target_link_libraries(example_split PRIVATE machine_learning_1)

add_executable(example_significance examples/significance_example.cpp)
target_link_libraries(example_significance PRIVATE machine_learning_1)

# ==========================================
# AUTOMATED CTEST REGISTRATION
# ==========================================
add_test(NAME TrainTestSplitTest COMMAND test_train_test_split)
add_test(NAME StatisticalSignificanceTest COMMAND test_statistical_significance)