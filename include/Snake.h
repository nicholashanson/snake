#ifndef SNAKE_H
#define SNAKE_H
#include "definitions.h"

class Snake
{
    public:

        // special members
        Snake();
        virtual ~Snake();

        // getters
        auto get_length() const -> int;
        auto get_body() const -> snake_t;
        auto get_head() const -> square_t;
        auto get_tail() const -> square_t;
        auto get_direction() const -> direction_t;

        // setters
        auto set_direction(const direction_t) -> bool;

        // checkers
        auto contains(const square_t) const -> bool;
        auto head_has_collided_with_tail() const -> bool;

        // actions
        auto pop() -> void;
        auto push(square_t) -> void;
        auto extend() -> void;
        auto move_snake() -> void;
        auto empty_snake() -> void;
        auto add_to_snake(const int,const int) -> void;
    private:

        direction_t current_direction;

        snake_t body;

        int units_to_extend;
};

#endif // SNAKE_H

