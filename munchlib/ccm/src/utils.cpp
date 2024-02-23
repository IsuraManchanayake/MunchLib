//
// Created by Isura Manchanayaka on 20/2/2024.
//

#include "utils.h"

std::vector<std::vector<double>> exp_weights(const std::vector<std::vector<double>> &X) {
    const auto n = X.size();
    const auto m = X[0].size();
    std::vector<double> norms(X.size());
    for(size_t i = 0; i < n; ++i) {
        norms[i] = X[i][0] + 0.00001f;
    }
    std::vector<std::vector<double>> W(n, std::vector<double>(m));
    for(size_t i = 0; i < n; ++i) {
        for(size_t j = 0; j < m; ++j) {
            W[i][j] = std::exp(-X[i][j] / norms[i]);
        }
        auto denom = 0.;
        for(double num : W[i]) {
            denom += num;
        }
        for(size_t j = 0; j < m; ++j) {
            W[i][j] /= denom;
        }
    }
    return W;
}

double pearson(const std::vector<double> &X, const std::vector<double> &Y) {
    const auto n = X.size();
    double sum_x = 0;
    double sum_y = 0;
    double sum_x_sq = 0;
    double sum_y_sq = 0;
    double sum_xy = 0;
    for(size_t i = 0; i < n; ++i) {
        sum_x += X[i];
        sum_y += Y[i];
        sum_x_sq += X[i] * X[i];
        sum_y_sq += Y[i] * Y[i];
        sum_xy += X[i] * Y[i];
    }
    const auto nf = static_cast<double>(n);
    double numerator = sum_xy - (sum_x * sum_y / nf);
    double denominator = std::sqrt((sum_x_sq - (sum_x * sum_x / nf)) * (sum_y_sq - (sum_y * sum_y / nf)));
    if(denominator == 0) {
        return 0;
    }
    return numerator / denominator;
}
