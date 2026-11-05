#include <iostream>
#include <vector>
#include "machine_learning_1/train_test_split.hpp"

int main() {
    std::cout<< "=== Train/test split Example (Integer anf foat support) ===\n";

    //testing with integer datatype like hoous IDs or simply counts double prices
    std::vector<int> house_ids = {101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
    std::vector<double> house_prices = {150.5, 180.4, 210.7, 250.6, 310.3, 390.2, 410.5, 296.3, 551.3, 896.1};

    try {
        double test_ratio = 0.2;
        auto [train_split, test_split] = ml_library::TrainTestSplitter::splitPaired(house_ids, house_prices, test_ratio, 42);
    
        std::cout << "[INFO] paired split successfully!\n";
        std::cout << " -> total samples: " << house_ids.size() << "\n"; 
        std::cout << "Training Samples: " << train_split.train_data.size() << "\n";
        std::cout << "Testing Samples:  " << test_split.test_data.size() << "\n";


    std::cout << "Training house IDs: ";
    for(int id : train_split.train_data){
        std:: cout << id << " ";
    }
    
    std::cout << "\n\n";
    
    std::cout << "Testing house IDs: ";
    for(int id : test_split.test_data){
        std:: cout << id << " ";
    }
    std::cout << "\n\n";
}
    catch (const std::exception& e){
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}