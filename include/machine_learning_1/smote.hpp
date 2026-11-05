#ifndef SMOTE_HPP
#define SMOTE_HPP

#include <vector>
#include <cmath>
#include <stdexcept>
#include <limits>
#include <algorithm>
#include <random>
#include "ml_error.hpp"

namespace ml1 {

// A simple structure to hold our dataset.
struct Dataset {
    std::vector<std::vector<double>> features; // The X values
    std::vector<int> labels;                   // The Y values (e.g., 0 or 1)
};

/**
 * Calculates the Euclidean distance between two feature vectors.
 */
inline double euclidean_distance(
    const std::vector<double>& a, 
    const std::vector<double>& b) 
{
    if (a.size() != b.size()) {
        throw InvalidInputError("Feature vectors must be the same size for distance calculation.");
    }

    double sum = 0.0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        double diff = a[i] - b[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}

/**
 * Finds the k-nearest neighbors for a specific point within a subset of data.
 * 
 * @param target_idx The index of the point we are finding neighbors for.
 * @param features The full feature matrix.
 * @param indices The indices of the minority class (we only search within these).
 * @param k The number of neighbors to find.
 * @return A vector of indices representing the k-nearest neighbors.
 */
inline std::vector<std::size_t> find_k_nearest_neighbors(
    std::size_t target_idx,
    const std::vector<std::vector<double>>& features,
    const std::vector<std::size_t>& minority_indices,
    std::size_t k)
{
    if (k >= minority_indices.size()) {
        throw InvalidInputError("k must be less than the number of minority samples.");
    }

    std::vector<std::pair<double, std::size_t>> distances;
    
    // Calculate distance to all OTHER minority points
    for (std::size_t idx : minority_indices) {
        if (idx == target_idx) continue; // Don't include the point itself
        double dist = euclidean_distance(features[target_idx], features[idx]);
        distances.push_back({dist, idx});
    }

    // Sort by distance (ascending)
    std::sort(distances.begin(), distances.end());

    // Extract the top k indices
    std::vector<std::size_t> neighbors;
    for (std::size_t i = 0; i < k; ++i) {
        neighbors.push_back(distances[i].second);
    }

    return neighbors;
}

/**
 * Generates synthetic data to balance a dataset using SMOTE.
 * 
 * @param data The original dataset.
 * @param k_neighbors The number of nearest neighbors to consider.
 * @return A new Dataset containing the original data + synthetic minority data.
 */
inline Dataset apply_smote(const Dataset& data, std::size_t k_neighbors = 5) {
    if (data.features.size() != data.labels.size()) {
        throw InvalidInputError("Features and labels size mismatch.");
    }
    if (data.features.empty()) {
        throw InvalidInputError("Dataset is empty.");
    }

    // 1. Separate indices by class (0 and 1)
    std::vector<std::size_t> minority_indices;
    std::vector<std::size_t> majority_indices;

    for (std::size_t i = 0; i < data.labels.size(); ++i) {
        if (data.labels[i] == 0) {
            minority_indices.push_back(i);
        } else {
            majority_indices.push_back(i);
        }
    }

    if (minority_indices.empty()) {
        throw InvalidInputError("No minority class (label 0) found in the dataset.");
    }
    if (majority_indices.size() <= minority_indices.size()) {
        // Dataset is already balanced or the majority is smaller
        return data; 
    }

    // Calculate how many synthetic points we need to generate
    std::size_t num_to_generate = majority_indices.size() - minority_indices.size();
    
    // Set up random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<std::size_t> neighbor_dist(0, k_neighbors - 1);
    std::uniform_real_distribution<double> lambda_dist(0.0, 1.0);

    // Create a copy of the original data to add to
    Dataset new_data = data;

    // 2. Generate the synthetic points
    for (std::size_t i = 0; i < num_to_generate; ++i) {
        // Pick a random minority point
        std::size_t random_minority_pos = i % minority_indices.size();
        std::size_t base_idx = minority_indices[random_minority_pos];

        // Find its neighbors
        std::vector<std::size_t> neighbors = find_k_nearest_neighbors(
            base_idx, data.features, minority_indices, k_neighbors);

        // Pick a random neighbor
        std::size_t random_neighbor_idx = neighbors[neighbor_dist(gen)];

        // Interpolate to create a new point
        std::vector<double> synthetic_point(data.features[base_idx].size());
        double lambda = lambda_dist(gen);

        for (std::size_t j = 0; j < synthetic_point.size(); ++j) {
            synthetic_point[j] = data.features[base_idx][j] + 
                                 lambda * (data.features[random_neighbor_idx][j] - data.features[base_idx][j]);
        }

        // Add the new point to our dataset
        new_data.features.push_back(synthetic_point);
        new_data.labels.push_back(0); // It belongs to the minority class
    }

    return new_data;
}

} // namespace ml1

#endif // SMOTE_HPP