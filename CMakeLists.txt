cmake_minimum_required(VERSION 3.20)
project(MLLibrary VERSION 1.0.0 LANGUAGES CXX)

#enforcing C++23 globally (handles C++17, C++20, and C++23 seamlessly)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#including directories for public headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


#1.library source implementation(.cpp)
# .cpp implementation files here:
set(LIBRARY_SOURCES
    src/train_test_split.cpp
    src/statistical_significance.cpp
    src/best_fit.cpp
    src/closed_form.cpp
    src/gradient_descent.cpp
    src/correlation_coefficient.cpp
    src/main.cpp 
    src/ml_pipeline.cpp 
    src/prediction_interval.cpp
    src/standard_error_estimation.cpp 
    src/stochastic_gradient_descent.cpp  
)

#building the main static library target
add_library(machine_learning_1 ${LIBRARY_SOURCES})

#2.automating testing setup (CTest)
enable_testing()

#helper macro to keep CMake clean and avoid repeating code for every test
macro(add_ml_test TEST_NAME SOURCE_FILE)
    add_executable(${TEST_NAME} ${SOURCE_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE machine_learning_1)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endmacro()

#registeering group tests
add_ml_test(test_closed_form tests/test_closed_form.cpp)
add_ml_test(test_correlation_coefficient tests/test_correlation_coefficient.cpp)
add_ml_test(test_gradient_descent tests/test_gradient_descent.cpp)
add_ml_test(test_line_of_best_fit tests/test_line_of_best_fit.cpp)
add_ml_test(test_module1 tests/test_module1.cpp)
add_ml_test(test_prediction_interval tests/test_prediction_interval.cpp)
add_ml_test(test_r2_unit tests/test_r2_unit.cpp)
add_ml_test(test_smote_day1 tests/test_smote_day1.cpp)
add_ml_test(test_smote_day2 tests/test_smote_day2.cpp)
add_ml_test(test_smote_day3 tests/test_smote_day3.cpp)
add_ml_test(test_standard_error tests/test_standard_error.cpp)
add_ml_test(test_statistical_significance tests/test_statistical_significance.cpp)
add_ml_test(test_stochastic_gradient_descent tests/test_stochastic_gradient_descent.cpp)
add_ml_test(test_train_test_split tests/test_train_test_split.cpp)


#3.example executables setup
#helper macro for example programs
macro(add_ml_example EXAMPLE_NAME SOURCE_FILE)
    add_executable(${EXAMPLE_NAME} ${SOURCE_FILE})
    target_link_libraries(${EXAMPLE_NAME} PRIVATE machine_learning_1)
endmacro()

#registering group examples
add_ml_example(example_sdg examples/SDG_example.cpp)
add_ml_example(example_closed_form examples/closed_form_example.cpp)
add_ml_example(example_gradient_descent examples/gradient_descent_example.cpp)
add_ml_example(example_significance examples/significance_example.cpp)
add_ml_example(example_standard_error_est examples/standard_error_estimation.cpp)
add_ml_example(example_standard_error examples/standard_error_example.cpp)
add_ml_example(example_test_r2 examples/test_r2.cpp)
add_ml_example(example_train_test_split examples/train_test_split_example.cpp)