#include "Journey.h"

// special members
Journey::Journey(square_t start, square_t finish): current_status( ACTIVE )
{calculate_journey(start, finish);}

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

// actions
auto Journey::fetch_next_step(Game *game) -> direction_t
{
    direction_t next_step;
    if ( !steps_one.empty()
         && game->set_direction( steps_one.front() ) ){
        next_step = steps_one.front();
        steps_one.pop();
    }
    else {
        game->set_direction( steps_two.front() );
        next_step = steps_two.front();
        steps_two.pop();
    }
    if ( steps_one.empty()
         && steps_two.empty())
        current_status = OVER;
    return next_step;
}

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

