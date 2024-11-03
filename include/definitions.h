#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#include <cstdlib>
#include <ctime>
#include <queue>
#include <deque>
#include <tuple>
#include <vector>
#include <algorithm>

typedef enum {
    LEFT = 1,
    RIGHT = 3,
    UP = 2,
    DOWN = 4
} direction_t;

typedef enum {
    OVER,
    PAUSED,
    ACTIVE
} status_t;

typedef enum {
    EASY,
    MEDIUM,
    HARD
} difficulty_t;

typedef std::tuple<int,int> square_t;
typedef std::deque<std::tuple<int,int>> snake_t;

#endif // DEFINITIONS_H
