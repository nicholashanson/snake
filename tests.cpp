#ifdef TEST
#include "Game.h"
#define BOOST_TEST_MODULE TestSuite
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(DifficultySettingTest)
{
    Game game;
    game.set_difficulty(EASY);
    BOOST_CHECK_EQUAL(game.get_difficulty(), EASY);
    game.set_difficulty(MEDIUM);
    BOOST_CHECK_EQUAL(game.get_difficulty(), MEDIUM);
    game.set_difficulty(HARD);
    BOOST_CHECK_EQUAL(game.get_difficulty(), HARD);
}

BOOST_AUTO_TEST_CASE(InitialPointsTest)
{
    Game game;
    BOOST_CHECK_EQUAL(game.get_points_count(), 0);
}

BOOST_AUTO_TEST_CASE(PointIncrementTest)
{
    Game game;
    game.increment_points_count();
    BOOST_CHECK_EQUAL(game.get_points_count(), settings::points_per_apple);
}

BOOST_AUTO_TEST_CASE(HeadInitialPositionTest)
{
    Game game;
    BOOST_CHECK_EQUAL(first( game.get_snake_head()), settings::head_initial_x);
    BOOST_CHECK_EQUAL(second(game.get_snake_head()), settings::head_initial_y);
}

BOOST_AUTO_TEST_CASE(SnakeInitialLengthTest)
{
    Game game;
    BOOST_CHECK_EQUAL(game.get_snake_length(), settings::initial_snake_length);
}


BOOST_AUTO_TEST_CASE(TailInitialPositionTest)
{
    Game game;
    BOOST_CHECK_EQUAL(first(game.get_snake_tail()), settings::head_initial_x + settings::initial_snake_length - 1);
    BOOST_CHECK_EQUAL(second(game.get_snake_tail()), settings::head_initial_y);
}

BOOST_AUTO_TEST_CASE(SnakContinuityTest)
{
    Game game;
    snake_t body = game.get_snake();
    for (int i = 1; i <= settings::initial_snake_length; i++)
        BOOST_CHECK_EQUAL(first(body[i-1]),
            settings::head_initial_x + settings::initial_snake_length - i);
}

BOOST_AUTO_TEST_CASE(HeadBeforeTailTest)
{
    Game game;
    BOOST_CHECK(first(game.get_snake_head()) < first(game.get_snake_tail()));
}

BOOST_AUTO_TEST_CASE(SnakeMoveLeftTest)
{
    Game game;
    game.move_snake();
    BOOST_CHECK_EQUAL(first(game.get_snake_head()),settings::head_initial_x-1);
}

BOOST_AUTO_TEST_CASE(SnakeMoveRightTest)
{
    Game game;
    game.set_direction(UP);
    game.move_snake();
    game.set_direction(RIGHT);
    game.move_snake();
    game.move_snake();
    BOOST_CHECK_EQUAL(first(game.get_snake_head()), settings::head_initial_x+2);
}

BOOST_AUTO_TEST_CASE(SnakeMoveUpTest)
{
    Game game;
    game.set_direction(UP);
    game.move_snake();
    game.move_snake();
    game.move_snake();
    BOOST_CHECK_EQUAL(second(game.get_snake_head()),settings::head_initial_y-3);
}

BOOST_AUTO_TEST_CASE(SnakeMoveDownTest)
{
    Game game;
    game.set_direction(DOWN);
    game.move_snake();
    game.move_snake();
    BOOST_CHECK_EQUAL(second(game.get_snake_head()),settings::head_initial_y+2);
}

BOOST_AUTO_TEST_CASE(HeadTailCollisionTest)
{
    Game game;
    BOOST_CHECK( !game.snake_has_collided_with_tail() );
    game.set_direction( UP );
    game.move_snake();
    game.set_direction( RIGHT );
    game.move_snake();
    game.set_direction( DOWN );
    game.move_snake();
    BOOST_CHECK( game.snake_has_collided_with_tail() );
}

BOOST_AUTO_TEST_CASE(AppleBoundsTest)
{
    Game game;
    game.spawn_apple();
    BOOST_CHECK(first(game.get_apple_position()) >= 0
                && first(game.get_apple_position()) <= settings::board_width);
    BOOST_CHECK(second(game.get_apple_position()) >= 0
                && second(game.get_apple_position()) <= settings::board_height);
}

BOOST_AUTO_TEST_CASE(AppleEatingTest)
{
    Game game;
    game.spawn_apple(settings::head_initial_x-1, settings::head_initial_y);
    game.move_snake();
    BOOST_CHECK( game.head_is_at_apple() );
}

BOOST_AUTO_TEST_CASE(LeftBoundaryTest)
{
    Game game;
    int i = settings::head_initial_x;
    for (int j = 0; j < i; j++)
        game.move_snake();
    BOOST_CHECK_EQUAL(first(game.get_snake_head()), 0);
    game.move_snake();
    BOOST_CHECK_EQUAL(first(game.get_snake_head()), settings::board_width);
}

BOOST_AUTO_TEST_CASE(RightBoundaryTest)
{
    Game game;
    game.set_direction(UP);
    game.move_snake();
    game.set_direction(RIGHT);
    int i = settings::board_width - settings::head_initial_x;
    for (int j = 0; j < i; j++)
        game.move_snake();
    BOOST_CHECK_EQUAL(first(game.get_snake_head()), settings::board_width);
    game.move_snake();
    BOOST_CHECK_EQUAL(first(game.get_snake_head()), 0);
}

BOOST_AUTO_TEST_CASE(UpperBoundaryTest)
{
    Game game;
    game.set_direction(UP);
    int i = settings::head_initial_y;
    for (int j = 0; j < i; j++)
        game.move_snake();
    BOOST_CHECK_EQUAL(second(game.get_snake_head()), 0);
    game.move_snake();
    BOOST_CHECK_EQUAL(second(game.get_snake_head()), settings::board_height);
}

BOOST_AUTO_TEST_CASE(LowerBoundaryTest)
{
    Game game;
    game.set_direction(DOWN);
    int i = settings::board_height - settings::head_initial_y;
    for (int j = 0; j < i; j++)
        game.move_snake();
    BOOST_CHECK_EQUAL(second(game.get_snake_head()), settings::board_height);
    game.move_snake();
    BOOST_CHECK_EQUAL(second(game.get_snake_head()), 0);
}

BOOST_AUTO_TEST_CASE(InitialSpeedTest)
{
    Game game;
    game.set_difficulty(EASY);
    BOOST_CHECK( game.get_current_speed()
                 == settings::initial_speeds[EASY]);
}

BOOST_AUTO_TEST_CASE(SpeedIncreaseTest)
{
    Game game;
    game.set_difficulty(EASY);
    int speed = game.get_current_speed();
    for (int i = 0; i < settings::apples_per_speed_change; i++)
        game.eat_apple();
    BOOST_CHECK_EQUAL(game.get_current_speed(), settings::speed_increase_factor*speed);
}

BOOST_AUTO_TEST_CASE(NoReverseTest)
{
    Game game;
    game.set_direction(RIGHT);
    BOOST_CHECK_EQUAL(game.get_direction(), LEFT);
    game.set_direction(UP);
    game.set_direction(DOWN);
    BOOST_CHECK_EQUAL(game.get_direction(), UP);
    game.set_direction(RIGHT);
    game.set_direction(LEFT);
    BOOST_CHECK_EQUAL(game.get_direction(), RIGHT);
    game.set_direction(DOWN);
    game.set_direction(UP);
    BOOST_CHECK_EQUAL(game.get_direction(), DOWN);
}

// 23. SnakeExtensionTest
BOOST_AUTO_TEST_CASE(SnakeExtensionTest)
{
    Game game;
    game.eat_apples(settings::apples_per_extension);
    for (int i = 0; i < settings::units_per_extension; i++)
        game.move_snake();
    BOOST_CHECK_EQUAL(game.get_snake_length(), settings::initial_snake_length + settings::units_per_extension);
}

// 24. AppleBodyCollisionTest
BOOST_AUTO_TEST_CASE(AppleBodyCollisionTest)
{
    Game game;
    game.empty_snake();
    for (int i = 0; i <= settings::board_width; i++)
        for (int j = 0; j <= settings::board_height; j++)
            if (i != 0 || j !=0 )
                game.add_to_snake(i,j);
    game.spawn_apple();
    BOOST_CHECK(game.get_apple_position() == std::make_tuple(0,0));
}

// 25. GameCompletionTest
BOOST_AUTO_TEST_CASE(GameCompletionTest)
{
    Game game;
    game.fill_board_with_snake();
    BOOST_CHECK( game.game_is_completed() );
}


// 26. BoardArrayContentTest
BOOST_AUTO_TEST_CASE(BoardArrayContentTest)
{
    Game game;
    int **board = game.get_board();
    bool valid_content = true;
    for (int i = 0; i <= settings::board_height; i++)
        for (int j = 0; j <= settings::board_width; j++)
        {
            int current = board[i][j];
            if (current != 0 && current != 1 && current != 2)
                valid_content = false;
        }
    game.free_board(board);
    BOOST_CHECK(valid_content);
}

// 27. CheckBoardNoSnakeTest
BOOST_AUTO_TEST_CASE(CheckBoardNoSnakeTest)
{
    Game game;
    int **board = game.get_board();
    bool snake_found = false;
    for (int i = 0; i <= settings::board_height; i++)
        for (int j = 0; j <= settings::board_width; j++)
            if (board[i][j] == 1) snake_found = true;
    game.free_board(board);
    BOOST_CHECK(snake_found);
}

// 28. CheckBoardNoAppleTest
BOOST_AUTO_TEST_CASE(CheckBoardNoAppleTest)
{
    Game game;
    int **board = game.get_board();
    bool apple_found = false;
    for (int i = 0; i <= settings::board_height; i++)
        for (int j = 0; j <= settings::board_width; j++)
            if (board[i][j] == 1) apple_found = true;
    game.free_board(board);
    BOOST_CHECK(apple_found);
}

// 29. CheckSnakeLengthTest
BOOST_AUTO_TEST_CASE(CheckSnakeLengthTest)
{
    Game game;
    int **board = game.get_board();
    int snake_length = 0;
    for (int i = 0; i <= settings::board_height; i++)
        for (int j = 0; j <= settings::board_width; j++)
            if (board[i][j] == 1) snake_length++;
    game.free_board(board);
    BOOST_CHECK_EQUAL(snake_length, settings::initial_snake_length);
}

// 30. OnlyOneAppleBoardTest
BOOST_AUTO_TEST_CASE(OnlyOneAppleBoardTest)
{
    Game game;
    int **board = game.get_board();
    int number_of_apples = 0;
    for (int i = 0; i <= settings::board_height; i++)
        for (int j = 0; j <= settings::board_width; j++)
            if (board[i][j] == 2) number_of_apples++;
    game.free_board(board);
    BOOST_CHECK_EQUAL(number_of_apples, 1);
}

BOOST_AUTO_TEST_CASE(DirectionToggleClockwiseTest)
{
    Game game;
    game.toggle_direction_clockwise();
    BOOST_CHECK_EQUAL(game.get_direction(), UP);
    game.toggle_direction_clockwise();
    BOOST_CHECK_EQUAL(game.get_direction(), RIGHT);
    game.toggle_direction_clockwise();
    BOOST_CHECK_EQUAL(game.get_direction(), DOWN);
    game.toggle_direction_clockwise();
    BOOST_CHECK_EQUAL(game.get_direction(), LEFT);
}

BOOST_AUTO_TEST_CASE(JourneyLengthTest)
{
    Game game;
    game.set_apple_position(settings::head_initial_x-2, settings::head_initial_y-2);
    game.set_journey();
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_one_size(), 2);
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_two_size(), 2);
}

BOOST_AUTO_TEST_CASE(JourneyStepsOneEmptyTest)
{
    Game game;
    game.set_apple_position(settings::head_initial_x, settings::head_initial_y-2);
    game.set_journey();
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_one_size(), 0);
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_two_size(), 2);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), UP);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), UP);
}

BOOST_AUTO_TEST_CASE(JourneyStepsTwoEmptyTest)
{
    Game game;
    game.set_apple_position(settings::head_initial_x-2, settings::head_initial_y);
    game.set_journey();
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_one_size(), 2);
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_two_size(), 0);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), LEFT);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), LEFT);
}

BOOST_AUTO_TEST_CASE(TopLeftJourneyDirectionTest)
{
    Game game;
    game.set_apple_position(settings::head_initial_x-2, settings::head_initial_y-2);
    game.set_journey();
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), LEFT);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), LEFT);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), UP);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), UP);
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_one_size(), 0);
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_two_size(), 0);
}

BOOST_AUTO_TEST_CASE(BottomLeftJourneyDirectionTest)
{
    Game game;
    game.set_apple_position(settings::head_initial_x-2, settings::head_initial_y+2);
    game.set_journey();
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), LEFT);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), LEFT);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), DOWN);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), DOWN);
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_one_size(), 0);
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_two_size(), 0);
}

BOOST_AUTO_TEST_CASE(TopRightJourneyDirectionTest)
{
    Game game;
    game.set_apple_position(settings::head_initial_x+2, settings::head_initial_y-2);
    game.set_journey();
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), UP);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), RIGHT);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), RIGHT);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), UP);
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_one_size(), 0);
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_two_size(), 0);
}

BOOST_AUTO_TEST_CASE(BottomRightJourneyDirectionTest)
{
    Game game;
    game.set_apple_position(settings::head_initial_x+2, settings::head_initial_y+2);
    game.set_journey();
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), DOWN);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), RIGHT);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), RIGHT);
    game.advance_journey();
    BOOST_CHECK_EQUAL(game.get_direction(), DOWN);
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_one_size(), 0);
    BOOST_CHECK_EQUAL(game.current_journey.get_steps_two_size(), 0);
}

BOOST_AUTO_TEST_CASE(TotalAvailableSquareTest)
{
    Game game;
    game.calculate_available_squares_for_apple_spawning();
    BOOST_CHECK_EQUAL(game.count_available_squares(),
                      settings::total_squares - settings::initial_snake_length);
}

#endif
