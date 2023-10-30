//
// Created by joonyeol on 23. 10. 30.
//

#ifndef EECBS_UTILS_H
#define EECBS_UTILS_H

#include "Environment.h"
#include "common.h"

class Utils {
 public:
  static inline int getManhattanDistance(int loc1, int loc2, const Environment* env) {
    int loc1_x = getRowCoordinate(loc1, env);
    int loc1_y = getColCoordinate(loc1, env);
    int loc2_x = getRowCoordinate(loc2, env);
    int loc2_y = getColCoordinate(loc2, env);
    return abs(loc1_x - loc2_x) + abs(loc1_y - loc2_y);
  }

  static inline int getManhattanDistance(const pair<int, int>& loc1, const pair<int, int>& loc2) {
    return abs(loc1.first - loc2.first) + abs(loc1.second - loc2.second);
  }

  static inline int getRowCoordinate(int id, const Environment* env) { return id / env->cols; }
  static inline int getColCoordinate(int id, const Environment* env) { return id % env->cols; }
  static inline bool validMove(int curr, int next, const Environment* env) {
    if (next < 0 || next >= env->map.size()) return false;
    if (env->map[next]) return false;
    return Utils::getManhattanDistance(curr, next, env) < 2;
  };

  static list<int> getNeighbors(int curr, const Environment* env) {
    list<int> neighbors;
    int candidates[4] = {curr + 1, curr - 1, curr + env->cols, curr - env->cols};
    for (int next : candidates) {
      if (validMove(curr, next, env)) neighbors.emplace_back(next);
    }
    return neighbors;
  };

  static int getDegree(int loc, const Environment* env) {
    assert(loc >= 0 && loc < env->map.size() && !env->map[loc]);
    int degree = 0;
    if (0 <= loc - env->cols && !env->map[loc - env->cols]) degree++;
    if (loc + env->cols < env->map.size() && !env->map[loc + env->cols]) degree++;
    if (loc % env->cols > 0 && !env->map[loc - 1]) degree++;
    if (loc % env->cols < env->cols - 1 && !env->map[loc + 1]) degree++;
    return degree;
  }

  static inline pair<int, int> getCoordinate(int id, const Environment* env) {
    return make_pair(id / env->cols, id % env->cols);
  }

  static inline int linearizeCoordinate(int row, int col, const Environment* env) {
    return (env->cols * row + col);
  }
};

#endif  // EECBS_UTILS_H
