#ifndef JOURNEY_H
#define JOURNEY_H

#include "Game.h"

class Journey
{
    public:
        Journey(square_t,square_t);
        virtual ~Journey();

        // getters
        auto get_status() const -> status_t;
        auto get_total_steps() const -> int;
        auto get_steps_one_size() const -> int;
        auto get_steps_two_size() const -> int;

        // actions
        auto reset(square_t,square_t) -> void;
        auto fetch_next_step(Game*) -> direction_t;
        auto calculate_journey(square_t,square_t) -> void;

    private:
        square_t destination;
        status_t current_status;

        std::queue<direction_t> steps_one;
        std::queue<direction_t> steps_two;
};

#endif // JOURNEY_H

