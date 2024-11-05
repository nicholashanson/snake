#include "Snake.h"
#include "settings.h"

// special members
Snake::Snake() : current_direction( LEFT ), units_to_extend( 0 )
{
    for ( int i = 1; i <= settings::initial_snake_length; i++ )
    {
        push( { settings::head_initial_x + settings::initial_snake_length - i,
                settings::head_initial_y } );
    }
}

Snake::~Snake(){}

// getters
auto Snake::get_length() const ->int
{return body.size();}

auto Snake::get_body() const -> snake_t
{return body;}

auto Snake::get_head() const -> square_t
{return body.back();}

auto Snake::get_tail() const -> square_t
{return body.front();}

auto Snake::get_direction() const -> direction_t
{return current_direction;}

// setters
auto Snake::set_direction(const direction_t new_direction) -> bool
{
    if ( current_direction == new_direction )
        return true;

    if ( current_direction % 2 == new_direction % 2 )
        return false;

    current_direction = new_direction;
    return true;
}

// checkers
auto Snake::head_has_collided_with_tail() const -> bool
{
    const square_t snake_head = get_head();
    return std::any_of( std::next( body.crbegin() ), body.crend(),
        [&]( const square_t& snake_tail_section ){
        return snake_head == snake_tail_section;
    });
}

auto Snake::contains(const square_t square) const -> bool
{
    return std::any_of(body.cbegin(), body.cend(),
        [&]( const square_t& snake_body_section ){
        return snake_body_section == square;
    });
}

// actions
auto Snake::pop() -> void
{body.pop_front();}

auto Snake::push(square_t square) -> void
{body.push_back(square);}

auto Snake::extend() -> void
{units_to_extend += settings::units_per_extension;}

void Snake::move_snake()
{
    // check if the snake is growing
    if ( 0 == units_to_extend )
        // snake is not growing so remove the end
        // of it's tail
        pop();
    // snake is growing
    else units_to_extend--;

    auto [ first, second ] = get_head();

    switch ( current_direction )
    {
        case LEFT:
            // snake is at left edge
            if ( 0 == first )
                // wrap to right edge
                push( { settings::board_width, second } );
            else
                push( { first - 1, second } );
            break;
        case RIGHT:
            // snake is at right edge
            if ( settings::board_width == first )
                // wrap to left edge
                push( { 0, second } );
            else
                push( { first + 1, second } );
            break;
        case UP:
            // snake is at top edge
            if ( 0 == second )
                // wrap to bottom edge
                push( { first, settings::board_height } );
            else
                push( { first, second - 1 } );
            break;
        case DOWN:
            // snake is at bottom edge
            if ( settings::board_height == second )
                // wrap to top edge
                push( { first, 0 } );
            else
                push( { first, second + 1 } );
            break;
        default: break;
    }
}

auto Snake::empty_snake() -> void
{body.clear();}

auto Snake::add_to_snake(const int x, const int y) -> void
{push( { x, y } );}
