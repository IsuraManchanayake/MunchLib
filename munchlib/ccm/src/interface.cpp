//
// Created by Isura Manchanayaka on 21/2/2024.
//

#include "interface.h"


std::pair<std::vector<double>, std::vector<double>>
cpp_ccm_coordination(
    const std::vector<double> &X1,
    const std::vector<double> &X2,
    size_t embed_size,
    size_t lag, const std::vector<uint64_t> &lib_lens
) {
    std::vector<size_t> lib_lens_size_t = std::vector<size_t>(lib_lens.begin(), lib_lens.end());
#define CHECK_EMBED_SIZE_AND_CALL(n) if(embed_size == (n)) { return cpp_ccm_coordination_core<(n)>(X1, X2, lag, lib_lens_size_t); }
    CHECK_EMBED_SIZE_AND_CALL(2)
    CHECK_EMBED_SIZE_AND_CALL(3)
    CHECK_EMBED_SIZE_AND_CALL(4)
    CHECK_EMBED_SIZE_AND_CALL(5)
    CHECK_EMBED_SIZE_AND_CALL(6)
    CHECK_EMBED_SIZE_AND_CALL(7)
    CHECK_EMBED_SIZE_AND_CALL(8)
    CHECK_EMBED_SIZE_AND_CALL(9)
    CHECK_EMBED_SIZE_AND_CALL(10)
    CHECK_EMBED_SIZE_AND_CALL(11)
    CHECK_EMBED_SIZE_AND_CALL(12)
    CHECK_EMBED_SIZE_AND_CALL(13)
    CHECK_EMBED_SIZE_AND_CALL(14)
    CHECK_EMBED_SIZE_AND_CALL(15)
    CHECK_EMBED_SIZE_AND_CALL(16)
    CHECK_EMBED_SIZE_AND_CALL(17)
    CHECK_EMBED_SIZE_AND_CALL(18)
    CHECK_EMBED_SIZE_AND_CALL(19)
    CHECK_EMBED_SIZE_AND_CALL(20)
    CHECK_EMBED_SIZE_AND_CALL(21)
    CHECK_EMBED_SIZE_AND_CALL(22)
    CHECK_EMBED_SIZE_AND_CALL(23)
    CHECK_EMBED_SIZE_AND_CALL(24)
    CHECK_EMBED_SIZE_AND_CALL(25)
    CHECK_EMBED_SIZE_AND_CALL(26)
    CHECK_EMBED_SIZE_AND_CALL(27)
    CHECK_EMBED_SIZE_AND_CALL(28)
    CHECK_EMBED_SIZE_AND_CALL(29)
    CHECK_EMBED_SIZE_AND_CALL(30)
    CHECK_EMBED_SIZE_AND_CALL(31)
    CHECK_EMBED_SIZE_AND_CALL(32)
    CHECK_EMBED_SIZE_AND_CALL(33)
    CHECK_EMBED_SIZE_AND_CALL(34)
    CHECK_EMBED_SIZE_AND_CALL(35)
    CHECK_EMBED_SIZE_AND_CALL(36)
    CHECK_EMBED_SIZE_AND_CALL(37)
    CHECK_EMBED_SIZE_AND_CALL(38)
    CHECK_EMBED_SIZE_AND_CALL(39)
    CHECK_EMBED_SIZE_AND_CALL(40)
    CHECK_EMBED_SIZE_AND_CALL(41)
    CHECK_EMBED_SIZE_AND_CALL(42)
    CHECK_EMBED_SIZE_AND_CALL(43)
    CHECK_EMBED_SIZE_AND_CALL(44)
    CHECK_EMBED_SIZE_AND_CALL(45)
    CHECK_EMBED_SIZE_AND_CALL(46)
    CHECK_EMBED_SIZE_AND_CALL(47)
    CHECK_EMBED_SIZE_AND_CALL(48)
    if(embed_size > 48 || embed_size < 2) {
        throw std::invalid_argument("Embed size is too large or too small.");
    }
    return {};
}