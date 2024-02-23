//
// Created by Isura Manchanayaka on 20/2/2024.
//

#pragma once

#include "knn.h"
#include "embed.h"
#include "utils.h"


template<size_t E>
struct CCM {
    using EType = std::array<double, E>;

    std::vector<EType> X1_train;
    std::vector<EType> X2_train;
    std::vector<EType> X1_test;
    std::vector<EType> X2_test;
    std::vector<std::vector<EType>> X1_pred;
    std::vector<std::vector<EType>> X2_pred;

    CCM(const std::vector<EType> &X1_train, const std::vector<EType> &X2_train, const std::vector<EType> &X1_test, const std::vector<EType> &X2_test);
    void predict(const std::vector<size_t> &lib_lens);
    [[nodiscard]] std::pair<std::vector<double>, std::vector<double>> score() const;
};

template<size_t E>
CCM<E>::CCM(
        const std::vector<EType> &X1_train,
        const std::vector<EType> &X2_train,
        const std::vector<EType> &X1_test,
        const std::vector<EType> &X2_test)
        : X1_train(X1_train), X2_train(X2_train), X1_test(X1_test), X2_test(X2_test), X1_pred(), X2_pred() {}

template<size_t E>
void CCM<E>::predict(const std::vector<size_t> &lib_lens) {
    this->X1_pred.clear();
    this->X2_pred.clear();
    for(const auto &lib_len: lib_lens) {
        std::vector<EType> X1_p(this->X1_test.size());
        std::vector<EType> X2_p(this->X2_test.size());
        KNN<E> knn_1(E + 1, this->X1_train.cbegin(), this->X1_train.cbegin() + lib_len);
        KNN<E> knn_2(E + 1, this->X2_train.cbegin(), this->X2_train.cbegin() + lib_len);
        auto [distances_1, indices_1] = knn_1.k_neighbors(this->X1_test);
        auto [distances_2, indices_2] = knn_2.k_neighbors(this->X2_test);

        const auto W1 = exp_weights(distances_1);
        const auto W2 = exp_weights(distances_2);

        for(size_t i = 0; i < this->X1_test.size(); ++i) {
            for(size_t j = 0; j < E; ++j) {
                X1_p[i][j] = 0;
                X2_p[i][j] = 0;
                for(size_t k = 0; k <= E; ++k) {  // E + 1 is the number of neighbors
                    X1_p[i][j] += W2[i][k] * this->X1_train[indices_2[i][k]][j];
                    X2_p[i][j] += W1[i][k] * this->X2_train[indices_1[i][k]][j];
                }
            }
        }
        this->X1_pred.push_back(X1_p);
        this->X2_pred.push_back(X2_p);
    }
}

template<size_t E>
std::pair<std::vector<double>, std::vector<double>> CCM<E>::score() const {
    std::vector<double> scores_1;
    std::vector<double> scores_2;

    for(size_t i = 0, s = this->X1_pred.size(); i < s; ++i) {
        std::vector<double> sc1(E, 0);
        std::vector<double> sc2(E, 0);
        const auto x1_p = this->X1_pred[i];
        const auto x2_p = this->X2_pred[i];
        for(size_t j = 0; j < E; ++j) {
            std::vector<double> p1;
            std::vector<double> p2;
            p1.reserve(x1_p.size());
            p2.reserve(x2_p.size());
            for(size_t k = 0, s_ = x1_p.size(); k < s_; ++k) {
                p1.push_back(x1_p[k][j]);
                p2.push_back(x2_p[k][j]);
            }
            std::vector<double> obs1(this->X1_test.size());
            std::vector<double> obs2(this->X2_test.size());
            for(size_t k = 0, s_ = this->X1_test.size(); k < s_; ++k) {
                obs1[k] = this->X1_test[k][j];
                obs2[k] = this->X2_test[k][j];
            }
            sc1[j] = pearson(p1, obs1);
            sc2[j] = pearson(p2, obs2);
        }
        scores_1.push_back(mean(sc1));
        scores_2.push_back(mean(sc2));
    }
    return {scores_1, scores_2};
}