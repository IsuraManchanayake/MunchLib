//
// Created by Isura Manchanayaka on 20/2/2024.
//

#pragma once

#include <vector>

std::vector<std::vector<double>> exp_weights(const std::vector<std::vector<double>> &X);
double pearson(const std::vector<double> &X, const std::vector<double> &Y);
template<typename T, template<typename...> typename VecType> T sum(const VecType<T> &X);
template<typename T, template<typename...> typename VecType> T mean(const VecType<T> &X);


// Templates ---

template<typename T, template<typename...> typename VecType> T sum(const VecType<T> &X) {
    auto sum = static_cast<T>(0);
    for(const auto &x: X) {
        sum += x;
    }
    return sum;
}

template<typename T, template<typename...> typename VecType> T mean(const VecType<T> &X) {
    return sum(X) / X.size();
}
