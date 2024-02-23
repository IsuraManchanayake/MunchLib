//
// Created by Isura Manchanayaka on 20/2/2024.
//

#pragma once

#include <vector>
#include <utility>
#include <random>
#include <chrono>

struct Random {
  std::mt19937 generator;
  std::uniform_real_distribution<double> distribution;
  
  explicit Random(unsigned seed=std::chrono::system_clock::now().time_since_epoch().count());
  double gen();
  void seed(unsigned seed);
};

struct Vec2 {
  double x;
  double y;
  
  Vec2();
  Vec2(double x, double y);
};

struct Node {
  uint64_t id;
  Vec2 pos;
  Vec2 disp;
  
  explicit Node(uint64_t id);
};


std::vector<std::pair<double, double>> cpp_calculate_fruchterman_reingold_layout(
        const std::vector<uint64_t> &nodes,
        const std::vector<std::pair<uint64_t, uint64_t>> &edges,
        double speed, double area, double gravity, uint64_t iter);
