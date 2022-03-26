
#include "globals.h"
#include "GameState.h"

//Use a for loop to iterate through the spaces in the array and then use that to check score

void playMove(GameState &game_state)
{
    int sum;

    //This is to play the move and check if its a valid move
    if (game_state.get_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn()) == 0 && game_state.get_turn() == true)
    {
        game_state.set_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn(), 1);
        game_state.set_turn(false);
        game_state.set_moveValid(true);
    }
    else if (game_state.get_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn()) == 0 && game_state.get_turn() == false)
    {
        game_state.set_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn(), -1);
        game_state.set_turn(true);
        game_state.set_moveValid(true);
    }
    else if (game_state.get_gameBoard(game_state.get_selectedRow(), game_state.get_selectedColumn()) != 0)
    {
        game_state.set_moveValid(false);
    }

    //i for row j for col
    for (int i = 0; i <= 2; i++)
    {
        sum=0;
        for (int j = 0; j <= 2; j++)
        {
            sum = game_state.get_gameBoard(i, j) + sum;
        }
        if (sum == -3 || sum == 3)
        {
            if (i == 0)
            {
                game_state.set_winCode(1);
                game_state.set_gameOver(true);
            }
            else if (i == 1)
            {
                game_state.set_winCode(2);
                game_state.set_gameOver(true);
            }
            else
            {
                game_state.set_winCode(3);
                game_state.set_gameOver(true);
            }
            break;
        }
    }
    //k for column and l for row
    for (int k = 0; k <= 2; k++)
    {
        sum=0;
        for (int l = 0; l <= 2; l++)
        {
            sum = game_state.get_gameBoard(l, k) + sum;
        }
        if (sum == -3 || sum == 3)
        {
            if (k == 0)
            {
                game_state.set_winCode(4);
                game_state.set_gameOver(true);
            }
            else if (k == 1)
            {
                game_state.set_winCode(5);
                game_state.set_gameOver(true);
            }
            else
            {
                game_state.set_winCode(6);
                game_state.set_gameOver(true);
            }
            break;
        }
    }
    sum = 0;
    for (int m = 0; m <= 2; m++)
    {
        sum = game_state.get_gameBoard(m, m) + sum;
        if (sum == -3 || sum == 3)
        {
            game_state.set_winCode(7);
            game_state.set_gameOver(true);
        }
    }
    sum = 0;
    for (int n = 0; n <= 2; n++)
    {
        sum = game_state.get_gameBoard(2 - n, n) + sum;
        if (sum == -3 || sum == 3)
        {
            game_state.set_winCode(8);
            game_state.set_gameOver(true);
        }
    }
    
    if (game_state.get_winCode() == 0)
    {
        game_state.set_gameOver(true);
        for (int x = 0; x <= 2; x++)
        {
            for (int y = 0; y <= 2; y++)
            {
                if (game_state.get_gameBoard(x, y) == 0)
                {
                    game_state.set_gameOver(false);
                }
            }

        } 
    }
}
