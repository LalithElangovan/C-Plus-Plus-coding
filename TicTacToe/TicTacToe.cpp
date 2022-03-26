#include <iostream>
#include <string>
using namespace std;

#include "globals.h"
#include "GameState.h"

// Function prototype for playMove
void playMove(GameState &);

// The main function
int main()
{

    /**********************************************************************************/
    /* Create an initialized game state object                                        */
    /**********************************************************************************/
    GameState game_state;

    // Read two integers from the user that represent the row and column
    // the player would like to place an X or an O in
    // You can assume there will be no formatting errors in the input
    int i, j;
    int row;
    int col;
    while (!game_state.get_gameOver())
    {
        cout << "Enter row and column of a grid cell: ";
        cin >> row >> col;

        // Check that the read row and column values are valid grid coordinates
        if ((row < 0) || (row > 2) || (col < 0) || (col > 2))
        {
            cout << "Invalid board coordinates " << row << " " << col << endl
                 << endl;
            continue;
        }
        // The coordinates are valid; set the selectedRow and selectedColumn
        // members of the game state to the read values
        // Again, the corresponding mutators of GameState must be first
        // implemented before this works
        // ECE244 Student: add your code here
        game_state.set_selectedRow(row);
        game_state.set_selectedColumn(col);

        cout << "Selected row " <<' '<< row << ' '<< "and column " << ' '<< col << endl;

        // Call playMove
        playMove(game_state);
        //playMove


        cout << "Game state after playMove:" << endl;
        cout << "Board: " << endl;
        for (j = 0; j <= 2; j++)
        {
            cout<<"   ";
            for (i = 0; i <= 2; i++)
            {
                if(game_state.get_gameBoard(j, i)==1)
                cout << "X ";
                else if(game_state.get_gameBoard(j, i)==0)
                    cout << "B ";
                else if(game_state.get_gameBoard(j, i)==-1)
                    cout << "O ";
            }
            cout<<'\n';
        }
        if (game_state.get_moveValid()==1)
        cout << "moveValid: true "<< endl;
        else if (game_state.get_moveValid()==0)
        cout << "moveValid: false "<< endl;

        if (game_state.get_gameOver()==1)
        cout << "gameOver: true "<< endl;
        else if (game_state.get_gameOver()==0)
        cout << "gameOver: false "<< endl;
        cout << "winCode: " << game_state.get_winCode() << endl<< endl;
        
    }

    return 0;
}
