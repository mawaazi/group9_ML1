#include <iostream>
#include <vector>
#include "../include/machine_learning_1/smote.hpp"

using namespace ml1;

int main() {
    // Create an imbalanced dataset:
    // Class 0 (Minority): 3 points
    // Class 1 (Majority): 5 points
    Dataset imbalanced_data;
    imbalanced_data.features = {
        {1.0, 1.0}, {1.5, 1.5}, {1.2, 1.2}, // Class 0 (Minority)
        {5.0, 5.0}, {6.0, 6.0}, {5.5, 5.5}, {4.0, 4.0}, {6.5, 6.5} // Class 1 (Majority)
    };
    imbalanced_data.labels = {0, 0, 0, 1, 1, 1, 1, 1};

    std::cout << "Original Dataset Size: " << imbalanced_data.labels.size() << "\n";
    int original_minority = 0;
    for (int label : imbalanced_data.labels) if (label == 0) original_minority++;
    std::cout << "Original Minority Count: " << original_minority << "\n\n";

    // Apply SMOTE
    Dataset balanced_data = apply_smote(imbalanced_data, 2); // k=2 neighbors

    std::cout << "Balanced Dataset Size: " << balanced_data.labels.size() << "\n";
    int new_minority = 0;
    for (int label : balanced_data.labels) if (label == 0) new_minority++;
    std::cout << "New Minority Count: " << new_minority << "\n\n";

    // Show some of the new synthetic points
    std::cout << "Sample Synthetic Points (Class 0):\n";
    for (std::size_t i = 3; i < 6 && i < balanced_data.features.size(); ++i) {
        std::cout << "(" << balanced_data.features[i][0] << ", " << balanced_data.features[i][1] << ")\n";
    }

    return 0;
}