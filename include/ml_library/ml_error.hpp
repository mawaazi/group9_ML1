#ifndef ML_ERROR_HPP
#define ML_ERROR_HPP

#include <stdexcept>
#include <string>

namespace ml1 {

class MLError : public std::runtime_error {
public:
    explicit MLError(const std::string& message)
        : std::runtime_error("ML1 error: " + message) {}
};

class InvalidInputError : public MLError {
public:
    explicit InvalidInputError(const std::string& message)
        : MLError("Invalid input: " + message) {}
};

} 

#endif