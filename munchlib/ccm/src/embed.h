//
// Created by Isura Manchanayaka on 20/2/2024.
//

#pragma once

#include <vector>
#include <array>


template<size_t embed_size>
std::vector<std::array<double, embed_size>> embed(size_t lag, const std::vector<double> &X) {
    std::vector<std::array<double, embed_size>> features(
            X.size() - lag * (embed_size - 1),
            std::array<double, embed_size>{}
    );
    for(size_t i = 0, s = features.size(); i < s; ++i) {
        for(size_t j = 0; j < embed_size; ++j) {
            features[i][j] = X[i + j * lag];
        }
    }
    return features;
}
