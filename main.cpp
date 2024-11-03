//#define TEST
#ifndef TEST
#include "raylib.h"
#include "ui_settings.h"
#include "Journey.h"

void draw_apple(int i, int j)
{
    DrawRectangle( i*UISettings::square_size,
                   j*UISettings::square_size,
                   UISettings::square_size,
                   UISettings::square_size, RED);
}

void draw_snake(int i, int j)
{
    DrawRectangle( i*UISettings::square_size,
                   j*UISettings::square_size,
                   UISettings::square_size,
                   UISettings::square_size, BLUE);
}

void for_each_member(int **board, int condition, void (*func)(int,int)){
    for ( int i = 0; i <= settings::board_height; i++ )
        for ( int j = 0; j <= settings::board_width; j++ )
            if ( board[i][j] == condition )
                func(i,j);
}

int main(void)
{
    Game game;
    Journey journey( game.get_snake_head(), game.get_apple_position() );

    InitWindow(settings::window_width,
               settings::window_height,
               "Snake");
    SetTargetFPS(2);

    while ( OVER != game.get_status() )
    {
        int **board = game.get_board();

        BeginDrawing();
        ClearBackground(BLACK);
        for_each_member(board, 2, draw_apple);
        for_each_member(board, 1, draw_snake);
        EndDrawing();

        if ( ACTIVE == journey.get_status() ){
            journey.fetch_next_step( &game );
        }
        else if ( OVER == journey.get_status() ){
            journey.reset( game.get_snake_head(), game.get_apple_position() );
        }
        game.move_snake();
        game.free_board(board);
        if ( game.snake_has_collided_with_tail() )
            game.set_status(OVER);
        if ( game.snake_is_eating_apple() ){
            game.eat_apple();
            game.spawn_apple();
        }
    }
    CloseWindow();
}

#endif

