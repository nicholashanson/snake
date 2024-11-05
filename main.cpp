#ifndef TEST
#include "raylib.h"
#include "ui_settings.h"
#include "Game.h"

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
    game.set_journey();

    InitWindow(settings::window_width,
               settings::window_height,
               "Snake");
    SetTargetFPS(4);

    while ( OVER != game.get_status() )
    {
        game.advance_game();

        if ( IsKeyPressed ( KEY_SPACE ) )
            if ( PAUSED == game.get_status() )
                game.set_status( ACTIVE );
            else
                game.set_status( PAUSED );

        int **board = game.get_board();

        BeginDrawing();
        ClearBackground(BLACK);
        for_each_member(board, 2, draw_apple);
        for_each_member(board, 1, draw_snake);
        EndDrawing();

        game.free_board(board);
    }
    CloseWindow();
}

#endif
