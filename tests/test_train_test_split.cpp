#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include "ml_library/train_test_split.hpp"

void testSplitWithDifferentTypes(){
    //testing with float and short to prove universsal numerical support
    std::vector<float> features = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f};
    std::vector<short> targets = {10, 20, 30, 40, 50, 60};

    auto[train_res, test_res] = ml_library::TrainTestSplitter::splitPaired(features, targets, 0.33, 123);
    assert(train_res.train_data.size() + test_res.train_data.size() == 6);
    std::cout << "[PASS] Milti-type numerical concept test passed successfully! \n";
}
    int main(){
        std::cout << "Runnning train/test Split test Suite... \n";
        testSplitWithDifferentTypes;
        std::cout << "All train/test split tests passed! \n";
        return 0; 
}
    