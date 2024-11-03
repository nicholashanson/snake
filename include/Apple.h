#ifndef APPLE_H
#define APPLE_H
#include "definitions.h"

class Apple
{
    public:
        Apple();
        virtual ~Apple();

        // getters
        auto get_position() const -> square_t;

        // setters
        auto set_position(const square_t) -> void;
        auto set_position(const int, const int) -> void;

        // actions
        auto spawn(const int, const int) -> void;
    private:
        square_t position;
};

#endif
