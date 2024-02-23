//
// Created by Isura Manchanayaka on 21/2/2024.
//

#pragma once

#include "ccm.h"
#include "embed.h"

#include <utility>
#include <vector>
#include <exception>


std::pair<std::vector<double>, std::vector<double>>
cpp_ccm_coordination(
    const std::vector<double> &X1,
    const std::vector<double> &X2,
    size_t embed_size,
    size_t lag, const std::vector<uint64_t> &lib_lens
);

template<size_t E>
std::pair<std::vector<double>, std::vector<double>>
cpp_ccm_coordination_core(
    const std::vector<double> &X1,
    const std::vector<double> &X2,
    size_t lag, const std::vector<size_t> &lib_lens
) {
    assert(X1.size() == X2.size() && "X1 and X2 must have the same size");
    const auto X1_embed = embed<E>(lag, X1);
    const auto X2_embed = embed<E>(lag, X2);
    const auto split_len = static_cast<size_t>(0.75 * static_cast<double>(X1_embed.size()));
    const auto X1_train = std::vector<std::array<double, E>>(X1_embed.cbegin(), X1_embed.cbegin() + split_len);
    const auto X2_train = std::vector<std::array<double, E>>(X2_embed.cbegin(), X2_embed.cbegin() + split_len);
    const auto X1_test = std::vector<std::array<double, E>>(X1_embed.cbegin() + split_len, X1_embed.cend());
    const auto X2_test = std::vector<std::array<double, E>>(X2_embed.cbegin() + split_len, X2_embed.cend());
    CCM<E> ccm(X1_train, X2_train, X1_test, X2_test);
    ccm.predict(lib_lens);
    return ccm.score();
}
