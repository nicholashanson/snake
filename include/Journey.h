#ifndef JOURNEY_H
#define JOURNEY_H
#include "definitions.h"
#include "macros.h"

class Journey
{
    public:
        Journey();
        virtual ~Journey();

        // getters
        auto get_status() const -> status_t;
        auto get_total_steps() const -> int;
        auto get_steps_one_size() const -> int;
        auto get_steps_two_size() const -> int;

        // setters
        auto set_status(const status_t) -> void;

        // actions
        auto reset(square_t,square_t) -> void;
        auto calculate_journey(const square_t,const square_t) -> void;

    private:
        square_t destination;
        status_t current_status;
    public:
        std::queue<direction_t> steps_one;
        std::queue<direction_t> steps_two;
};

#endif // JOURNEY_H
