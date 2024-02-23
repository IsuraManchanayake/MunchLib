//
// Created by Isura Manchanayaka on 20/2/2024.
//

#include "tests.h"
#include "fruchterman.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>


void test_calculate_fruchterman_reingold_layout() {
    std::cout << "\033[1;32m";
    std::cout << "[" << __FUNCTION__  << "]\n";
    std::cout << "\033[0m";
    const std::string node_table_path = "/Users/imanchanayak/credbank/node_table_w_topic_credbank_400.csv";
    const std::string edge_table_path = "/Users/imanchanayak/credbank/edge_table_w_topic_credbank_400.csv";

    std::vector<uint64_t> node_ids;
    std::ifstream node_table_f(node_table_path);
    std::string line;
    std::getline(node_table_f, line); // Skip the first line
    while (std::getline(node_table_f, line)) {
        std::istringstream iss(line);
        uint64_t node_id;
        iss >> node_id;
        node_ids.push_back(node_id);
    }

    std::vector<std::pair<uint64_t, uint64_t>> edge_id_pairs;
    std::ifstream edge_table_f(edge_table_path);
    std::getline(edge_table_f, line); // Skip the first line
    while (std::getline(edge_table_f, line)) {
        std::istringstream iss(line);
        uint64_t source, target;
        iss >> source;
        iss.ignore();
        iss >> target;
        edge_id_pairs.emplace_back(source, target);
    }

    const auto &begin = std::chrono::steady_clock::now();
    const auto positions = cpp_calculate_fruchterman_reingold_layout(node_ids, edge_id_pairs, 1.f, 10000.f, 10.f, 100);
    const auto &end = std::chrono::steady_clock::now();
    std::cout << "Time elapsed = " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000) << " ms\n";
}