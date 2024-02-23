//
// Created by Isura Manchanayaka on 20/2/2024.
//

#include "fruchterman.h"

#include <cmath>
#include <cassert>
#include <random>

// Random
Random::Random(unsigned seed)
    : generator(seed), distribution(0, 1) {}
double Random::gen() {
  return distribution(generator);
}
void Random::seed(unsigned seed) {
  generator.seed(seed);
}


// Vec2
Vec2::Vec2(): x(0.0), y(0.0) {}
Vec2::Vec2(double x, double y): x(x), y(y) {}

// Node
Node::Node(uint64_t id): id(id), pos(), disp() {}


// Method
std::vector<std::pair<double, double>> cpp_calculate_fruchterman_reingold_layout(const std::vector<uint64_t> &node_ids, const std::vector<std::pair<uint64_t, uint64_t>> &edge_id_pairs, double speed, double area, double gravity, uint64_t iter) {
  static const double SPEED_DIVISOR = 800;
  static const double AREA_MULTIPLICATOR = 10000;
  
  Random random(0);
  std::vector<Node> nodes;
  nodes.reserve(node_ids.size());
  for(const auto node_id: node_ids) {
    nodes.emplace_back(node_id);
    nodes.back().pos = {random.gen() * area, random.gen() * area};
  }
  
  std::vector<std::pair<Node &, Node &>> edges;
  edges.reserve(edge_id_pairs.size());
  for(const auto &edge_id_pair: edge_id_pairs) {
    Node *n_f = nullptr;
    Node *n_t = nullptr;
    for(auto &n: nodes) {
      if(n.id == edge_id_pair.first) {
        n_f = &n;
        break;
      }
    }
    for(auto &n: nodes) {
      if(n.id == edge_id_pair.second) {
        n_t = &n;
        break;
      }
    }
    assert(n_f != nullptr);
    assert(n_t != nullptr);
    edges.emplace_back(*n_f, *n_t);
  }
  double max_displace = std::sqrt(AREA_MULTIPLICATOR * area) / 10.0;
  double k = std::sqrt((AREA_MULTIPLICATOR * area) /
                       (1.0 + static_cast<double>(nodes.size())));
  
  for(uint64_t i = 0; i < iter; ++i) {
    for (auto &n: nodes) {
      n.disp.x = 0.0;
      n.disp.y = 0.0;
    }

    for(auto &n1: nodes) {
      for(const auto &n2: nodes) {
        if(n1.id != n2.id) {
          double x_dist = n1.pos.x - n2.pos.x;
          double y_dist = n1.pos.y - n2.pos.y;
          double dist = std::hypot(x_dist, y_dist);
          if(dist > 0) {
            double repulsive_f = k * k / dist;
            n1.disp.x += x_dist / dist * repulsive_f;
            n1.disp.y += y_dist / dist * repulsive_f;
          }
        }
      }
    }

    for(const auto &e: edges) {
      auto &n_f = e.first;
      auto &n_t = e.second;

      double x_dist = n_f.pos.x - n_t.pos.x;
      double y_dist = n_f.pos.y - n_t.pos.y;
      double dist = std::hypot(x_dist, y_dist);

      double attractive_f = dist * dist / k;

      if(dist > 0) {
        n_f.disp.x -= x_dist / dist * attractive_f;
        n_f.disp.y -= y_dist / dist * attractive_f;
        n_t.disp.x += x_dist / dist * attractive_f;
        n_t.disp.y += y_dist / dist * attractive_f;
      }
    }

    for(auto &n: nodes) {
      double d = std::hypot(n.pos.x, n.pos.y);
      double gf = 0.01f * k * gravity * d;
      n.disp.x -= gf * n.pos.x / d;
      n.disp.y -= gf * n.pos.y / d;
    }

    for(auto &n: nodes) {
      n.disp.x *= speed / SPEED_DIVISOR;
      n.disp.y *= speed / SPEED_DIVISOR;
    }

    for(auto &n: nodes) {
      double dist = std::hypot(n.disp.x, n.disp.y);
      if(dist > 0) {
        double limited_dist = std::min(max_displace * speed / SPEED_DIVISOR, dist);
        n.pos.x += n.disp.x / dist * limited_dist;
        n.pos.y += n.disp.y / dist * limited_dist;
      }
    }
  }

  std::vector<std::pair<double, double>> positions;
  positions.reserve(nodes.size());
  for(const auto &n: nodes) {
      positions.emplace_back(n.pos.x, n.pos.y);
  }
  
  return positions;
}
