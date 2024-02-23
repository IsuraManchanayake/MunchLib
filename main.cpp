#include "munchlib/fruchterman/src/tests.h"
#include "munchlib/ccm/src/tests.h"


int main() {
//    test_calculate_fruchterman_reingold_layout();
//    test_embeds();
//    test_exp_weights();
//    test_pearson();
//    test_knn();
//    test_ccm();
    test_cpp_ccm_coordination("data/ccm/x1.txt", "data/ccm/x2.txt");

    return 0;
}
