#ifndef GAME_H
#define GAME_H
#include "PointsCounter.h"
#include "Journey.h"
#include "Snake.h"
#include "Apple.h"
#include "settings.h"
#include "macros.h"

class Game
{
    public:

        // special members
        Game();
        virtual ~Game();

        // getters
        auto get_speed() const -> double;
        auto get_snake() const -> snake_t;
        auto get_status() const -> status_t;
        auto get_snake_length() const -> int;
        auto get_points_count() const -> int;
        auto get_snake_head() const -> square_t;
        auto get_snake_tail() const -> square_t;
        auto get_current_speed() const -> double;
        auto get_direction() const -> direction_t;
        auto get_difficulty() const -> difficulty_t;
        auto get_apple_position() const -> square_t;

        // setters
        auto set_status(status_t) -> void;
        auto set_direction(direction_t) -> bool;
        auto set_apple_position(int,int) -> void;
        auto set_difficulty(difficulty_t) -> void;
        auto set_journey() -> void;

        // actions
        auto advance_game() -> void;
        auto advance_journey() -> void;

        // snake
        auto move_snake() -> void;
        auto move_snake(direction_t) -> void;
        auto pop_snake() -> void;
        auto empty_snake() -> void;
        auto add_to_snake(const int,const int) -> void;
        auto toggle_direction_clockwise() -> void;

        // points
        auto increment_points_count() -> void;

        // apple
        auto eat_apple() -> void;
        auto eat_apples(int) -> void;
        auto spawn_apple() -> void;
        auto spawn_apple(const int,const int) -> void;

        // checkers
        auto snake_is_eating_apple() const -> bool;
        auto snake_contains(const square_t) const -> bool;
        auto snake_has_collided_with_tail() const -> bool;
        auto game_is_completed() const -> bool;

        auto fill_board_with_snake() -> void;
        auto get_board() -> int**;
        auto free_board() -> void;
        auto free_board(int**) -> void;

        auto count_available_squares() -> int;
        auto calculate_available_squares_for_apple_spawning() -> void;
    #ifndef TEST
    private:
    #endif
        double current_speed;
        status_t current_status;
        difficulty_t difficulty;

        Snake snake;
        Apple apple;
        PointsCounter points_counter;

        Journey current_journey;

        std::vector<square_t> available_squares_for_apple_spawning;
};

#endif // GAME_H
