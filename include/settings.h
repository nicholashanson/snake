#include <array>

namespace settings {
    const int points_per_apple = 1;
    const int apples_per_speed_change = 3;
    const int units_per_extension = 1;
    const int apples_per_extension = 1;
    const double speed_increase_factor = 1.4;
    const int bounus_timer_val = 60;
    const std::array<double, 3> initial_speeds = {1, 3, 5};
    const int bonus_points_per_second_factor = 1;
    const int initial_snake_length = 5;
    const int board_width = 9;
    const int board_height = 9;
    const int square_size = 20;
    constexpr int total_squares = ( settings::board_width + 1 ) * ( settings::board_height + 1 );
    const int unit_growth_per_apple = 1;
    constexpr int head_initial_x = board_width / 2 - initial_snake_length / 2;
    const int head_initial_y = board_height / 2;
    constexpr int window_width = (board_width + 1) * square_size;
    constexpr int window_height = (board_height + 1) * square_size;
}


