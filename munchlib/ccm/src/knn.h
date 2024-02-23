//
// Created by Isura Manchanayaka on 20/2/2024.
//

#pragma once

#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>

template<size_t E>
struct KNN {
    using EType = std::array<double, E>;
    using CIter = typename std::vector<EType>::const_iterator;

    size_t n_neighbors;
    CIter X_begin;
    CIter X_end;

    KNN(size_t n_neighbors, CIter X_begin, CIter X_end);
    std::pair<std::vector<std::vector<double>>, std::vector<std::vector<size_t>>> k_neighbors(const std::vector<EType> &X_test) const;
};

template<size_t E>
KNN<E>::KNN(size_t n_neighbors, CIter X_begin, CIter X_end) : n_neighbors(n_neighbors), X_begin(X_begin), X_end(X_end) {}

template<size_t E>
std::pair<std::vector<std::vector<double>>, std::vector<std::vector<size_t>>>
KNN<E>::k_neighbors(const std::vector<EType> &X_test) const {
    assert(this->n_neighbors <= std::distance(this->X_begin, this->X_end));

    std::vector<std::vector<double>> distances(X_test.size());
    std::vector<std::vector<size_t>> indices(X_test.size());

    for (size_t i = 0; i < X_test.size(); ++i) {
        using DistIndexPair = std::pair<double, size_t>;
        auto comp = [](const DistIndexPair& left, const DistIndexPair& right) { return left.first < right.first; };
        std::priority_queue<DistIndexPair, std::vector<DistIndexPair>, decltype(comp)> maxHeap(comp);

        size_t j = 0;
        for (auto it = X_begin; it != X_end; ++it, ++j) {
            double dist = 0.0;
            for (size_t k = 0; k < E; ++k) {
                double diff = X_test[i][k] - (*it)[k];
                dist += diff * diff;
            }

            if (maxHeap.size() < n_neighbors) {
                maxHeap.emplace(dist, j);
            } else if (dist < maxHeap.top().first) {
                maxHeap.pop();
                maxHeap.emplace(dist, j);
            }
        }

        distances[i].resize(n_neighbors);
        indices[i].resize(n_neighbors);
        for (int k = n_neighbors - 1; k >= 0; --k) {
            distances[i][k] = std::sqrt(maxHeap.top().first);
            indices[i][k] = maxHeap.top().second;
            maxHeap.pop();
        }
    }

    return {distances, indices};

//    std::vector<std::vector<double>> distances(X_test.size(), std::vector<double>(this->n_neighbors));
//    std::vector<std::vector<size_t>> indices(X_test.size(), std::vector<size_t>(this->n_neighbors));
//    for(size_t i = 0; i < X_test.size(); ++i) {
//        std::vector<std::pair<double, size_t>> dist_idx;
//        dist_idx.reserve(std::distance(this->X_begin, this->X_end));
//        for(size_t j = 0, s = std::distance(this->X_begin, this->X_end); j < s; ++j) {
//            auto other = *(this->X_begin + j);
//            auto dist = 0.0;
//            for(size_t k = 0; k < E; ++k) {
//                auto diff = X_test[i][k] - other[k];
//                dist += diff * diff;
//            }
//            dist_idx.emplace_back(dist, j);
//        }
//        std::nth_element(dist_idx.begin(), dist_idx.begin() + this->n_neighbors, dist_idx.end());
//        std::sort(dist_idx.begin(), dist_idx.begin() + this->n_neighbors);
//        for(size_t j = 0; j < this->n_neighbors; ++j) {
//            distances[i][j] = std::sqrt(dist_idx[j].first);
//            indices[i][j] = dist_idx[j].second;
//        }
//    }
//    return {distances, indices};
}
