#include "Journey.h"

// special members
Journey::Journey(){}
Journey::~Journey(){}

// getters
auto Journey::get_status() const -> status_t
{return current_status;}

auto Journey::get_total_steps() const -> int
{return steps_one.size() + steps_two.size();}

auto Journey::get_steps_one_size() const -> int
{return steps_one.size();}

auto Journey::get_steps_two_size() const -> int
{return steps_two.size();}

// setters
auto Journey::set_status(const status_t new_status) -> void
{current_status = new_status;}

// actions
auto Journey::reset(const square_t start, const square_t finish) -> void
{
    calculate_journey( start, finish );
    current_status = ACTIVE;
}

auto Journey::calculate_journey(const square_t start, const square_t finish) -> void
{
    int x_delta = first(finish) - first(start);
    int y_delta = second(finish) - second(start);

    if ( x_delta > 0 )
        for ( int i = 0; i < x_delta; i++ )
            steps_one.push( RIGHT );

    if ( x_delta < 0 )
        for ( int i = 0; i < -x_delta; i++ )
            steps_one.push( LEFT );

    if ( y_delta > 0 )
        for ( int i = 0; i < y_delta; i++ )
            steps_two.push( DOWN );

    if ( y_delta < 0 )
        for ( int i = 0; i < -y_delta; i++ )
            steps_two.push( UP );
}

