#include "Game.h"

// special members
Game::Game(): current_status( ACTIVE )
{spawn_apple();}

Game::~Game(){}

// getters
auto Game::get_current_speed() const -> double
{return current_speed;}

// snake
auto Game::get_snake_length() const -> int
{return snake.get_length();}

auto Game::get_snake() const -> snake_t
{return snake.get_body();}

auto Game::get_snake_head() const -> square_t
{return snake.get_head();}

auto Game::get_snake_tail() const -> square_t
{return snake.get_tail();}

auto Game::get_status() const -> status_t
{return current_status;}

auto Game::get_points_count() const -> int
{return points_counter.get_points_count();}

auto Game::get_direction() const -> direction_t
{return snake.get_direction();}

auto Game::get_difficulty() const -> difficulty_t
{return difficulty;}

auto Game::get_apple_position() const -> square_t
{return apple.get_position();}

// setters
auto Game::set_status(const status_t status) -> void
{current_status = status;}

auto Game::set_direction(const direction_t dir) -> bool
{return snake.set_direction(dir);}

auto Game::set_apple_position(const int x, const int y) -> void
{apple.set_position(x,y);}

auto Game::set_difficulty(const difficulty_t _difficulty) -> void
{
    difficulty = _difficulty;
    current_speed = settings::initial_speeds[difficulty];
}

// actions
auto Game::toggle_direction_clockwise() -> void
{
    switch ( get_direction() )
    {
        case LEFT:
            set_direction( UP );
            break;
        case UP:
            set_direction( RIGHT );
            break;
        case RIGHT:
            set_direction( DOWN );
            break;
        case DOWN:
            set_direction( LEFT );
            break;
        default: break;
    }
}

auto Game::move_snake() -> void
{snake.move_snake();}

auto Game::move_snake(const direction_t dir) -> void
{
    set_direction(dir);
    move_snake();
}

auto Game::pop_snake() -> void
{snake.pop();}

auto Game::empty_snake() -> void
{snake.empty_snake();}

auto Game::add_to_snake(const int x, const int y) -> void
{snake.add_to_snake(x,y);}

auto Game::increment_points_count() -> void
{return points_counter.increment_points_count();}

auto Game::eat_apple() -> void
{
    points_counter.eat_apple();

    int apples_consummed = points_counter.get_apple_points()
                                / settings::points_per_apple;

    if ( 0 == apples_consummed % settings::apples_per_speed_change )
        current_speed *= 1.4;

    if ( 0 == apples_consummed % settings::apples_per_extension )
        snake.extend();
}

auto Game::eat_apples(const int num) -> void
{
    for ( int i = 0; i < num; i++ )
        eat_apple();
}

auto Game::spawn_apple() -> void
{
    calculate_available_squares_for_apple_spawning();

    srand(time (NULL));

    int random = rand() % count_available_squares();

    apple.set_position( available_squares_for_apple_spawning[ random ] );
}

auto Game::spawn_apple(const int x, const int y) -> void
{apple.spawn(x,y);}

// checkers
auto Game::snake_is_eating_apple() const -> bool
{
    if ( get_snake_head() == apple.get_position() )
        return true;

    return false;
}

auto Game::snake_contains(const square_t square) const -> bool
{return snake.contains(square);}

auto Game::snake_has_collided_with_tail() const -> bool
{return snake.head_has_collided_with_tail();}

auto Game::game_is_completed() const -> bool
{return get_snake_length() == settings::total_squares;}

auto Game::fill_board_with_snake() -> void
{
    snake.empty_snake();
    for ( int i = 0; i <= settings::board_width; i++ )
        for ( int j = 0; j <= settings::board_width; j++ )
            snake.add_to_snake( i, j );
}

auto Game::get_board() -> int**
{
    int **board;

    const snake_t snake_body = snake.get_body();

    board = ( int** )malloc( sizeof( int * ) * ( settings::board_height + 1 ) );

    for ( int i = 0; i <= settings::board_height; i++ )
        board[ i ] = ( int* )malloc( sizeof( int ) * ( settings::board_width + 1 ) );

    for ( int i = 0; i <= settings::board_width; i++ )
        for ( int j = 0; j <= settings::board_height; j++ )
            board[i][j] = 0;

    std::for_each(snake_body.cbegin(), snake_body.cend(),
        [&]( const square_t& snake_body_section ){
        board[ first( snake_body_section ) ][ second( snake_body_section ) ] = 1;
    });

    square_t apple_position = get_apple_position();
    board[first(apple_position)][second(apple_position)] = 2;

    return board;
}

auto Game::free_board(int ** board) -> void
{
    for ( int i = 0; i <= settings::board_height; i++ )
        free( board[ i ] );
    free( board );
}

// stats
auto Game::count_available_squares() -> int
{return available_squares_for_apple_spawning.size();}

auto Game::calculate_available_squares_for_apple_spawning() -> void
{
    std::vector<square_t> squares;

    squares.resize( settings::total_squares );

    for ( int r = 0; r <= settings::board_width; r++ )
        for ( int c = 0; c <= settings::board_height; c++ )
            squares[ r*( settings::board_width + 1 ) + c ] = { r, c };

    for ( const square_t& square : get_snake() )
        squares[ first(square) * ( settings::board_width + 1 ) + second(square) ]
            = { settings::board_width + 1, settings::board_height + 1 };

    available_squares_for_apple_spawning.clear();
    available_squares_for_apple_spawning.reserve( squares.size() - snake.get_length() );

    auto partition_p = std::partition(squares.begin(), squares.end(),
        []( const square_t& square ){
            return square != std::tuple{ settings::board_width + 1, settings::board_height + 1 };
    });

    std::move( squares.begin(), partition_p, std::back_inserter( available_squares_for_apple_spawning ) );
}

