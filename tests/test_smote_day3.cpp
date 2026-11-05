#include <iostream>
#include <vector>
#include <cassert>
#include "../include/machine_learning_1/smote.hpp"

using namespace ml1;

int main() {
    std::cout << "--- Running Final SMOTE Integration Tests ---\n";

    // 1. Create a 3D Imbalanced Dataset
    // Class 0 (Minority): 2 points
    // Class 1 (Majority): 4 points
    Dataset data;
    data.features = {
        {1.0, 1.0, 1.0}, {1.5, 1.5, 1.5},                   // Class 0
        {9.0, 9.0, 9.0}, {8.0, 8.0, 8.0}, {9.5, 9.5, 9.5}, {8.5, 8.5, 8.5} // Class 1
    };
    data.labels = {0, 0, 1, 1, 1, 1};

    std::cout << "Original Minority Count: ";
    int orig_min = 0;
    for(int l : data.labels) if(l == 0) orig_min++;
    std::cout << orig_min << " (Expected: 2)\n";

    // 2. Apply SMOTE (k=1 because we only have 2 minority points)
    Dataset balanced = apply_smote(data, 1);

    int new_min = 0;
    for(int l : balanced.labels) if(l == 0) new_min++;
    
    std::cout << "New Minority Count: ";
    std::cout << new_min << " (Expected: 4)\n";

    // 3. Assert the dataset is now perfectly balanced
    assert(new_min == 4);
    assert(balanced.labels.size() == 8);

    // 4. Verify the new 3D synthetic points fall within the bounding box
    // Because the minority points are (1,1,1) and (1.5,1.5,1.5), 
    // any synthetic point MUST have coordinates between 1.0 and 1.5.
    std::cout << "\nVerifying 3D Synthetic Points:\n";
    for (std::size_t i = 2; i < balanced.features.size(); ++i) {
        if (balanced.labels[i] == 0) {
            // Check all 3 dimensions
            assert(balanced.features[i][0] >= 1.0 && balanced.features[i][0] <= 1.5);
            assert(balanced.features[i][1] >= 1.0 && balanced.features[i][1] <= 1.5);
            assert(balanced.features[i][2] >= 1.0 && balanced.features[i][2] <= 1.5);
            
            std::cout << "Point: (" << balanced.features[i][0] << ", " 
                      << balanced.features[i][1] << ", " 
                      << balanced.features[i][2] << ") -> [PASS]\n";
        }
    }

    // 5. Edge Case: Balanced dataset (should return untouched)
    Dataset already_balanced;
    already_balanced.features = {{1,1}, {2,2}};
    already_balanced.labels = {0, 1};
    Dataset result = apply_smote(already_balanced, 1);
    assert(result.labels.size() == 2);
    std::cout << "\n[PASS] Handled already balanced dataset safely.\n";

    std::cout << "\nAll Day 3 Integration Tests Passed! ✅\n";
    return 0;
}