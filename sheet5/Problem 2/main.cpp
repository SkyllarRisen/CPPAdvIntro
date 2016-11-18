#include "go.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <time.h>

using namespace std;

void playerLines(Board &Board1, int& player)                                                    //simulates player1 
{
    vector<Piece> pieceList(0);
    for (int i = 0; i < 7; ++i)                                                                 //loops through all positions
    {                                                                                           //
        for (int j = 0; j < 7; ++j)                                                             //
        {
            if (*(Board1.getPiece(i, j)).getType() == 0)                                        //checks if position is empty
            {
                if (i > 0 && *(Board1.getPiece(i - 1, j)).getType() == player)                  //checks if there is an adjacent
                    pieceList.push_back(Board1.getPiece(i, j));                                 //piece of same type
                else if (i < 6 && *(Board1.getPiece(i + 1, j)).getType() == player)             //if it finds a match
                    pieceList.push_back(Board1.getPiece(i, j));                                 //pushes piece to vector pieceList
                else if (j > 0 && *(Board1.getPiece(i, j - 1)).getType() == player)             //
                    pieceList.push_back(Board1.getPiece(i, j));                                 //
                else if (j < 6 && *(Board1.getPiece(i, j + 1)).getType() == player)             //
                    pieceList.push_back(Board1.getPiece(i, j));                                 //
            }
        }
    }
    int rngVal = rand() % pieceList.size();                                                     //generates random index
    Board1.placePiece(*pieceList[rngVal].getX(), *pieceList[rngVal].getY(), player);            //places random piece of pieceList
    cout << "Player " << player << " placed Piece at " << *pieceList[rngVal].getY()+1 << " " << *pieceList[rngVal].getX()+1 << endl;
}

void playerOpponentAdj(Board &Board1, int& player)                                              //simulates player2
{
    int oppPlayer;                                                                              //sets ID of opposing player
    if (player == 1)
        oppPlayer = 2;
    if (player == 2)
        oppPlayer = 1;
    vector<vector<Piece>> pieceList = vector<vector<Piece>> (3, vector<Piece>(0));              //vector of 3 vectors to store pieces
                                                                                                //each vector contains pieces with the
                                                                                                //same number of adjacent pieces of
                                                                                                //the opponent

    for (int i = 0; i < 7; ++i)                                                                 //loops through all positions
    {                                                                                           //
        for (int j = 0; j < 7; ++j)                                                             //
        {
            int pieceCount = -1;
            if (*(Board1.getPiece(i, j)).getType() == 0)                                        //checks if position is empty
            {
                if (i > 0 && *(Board1.getPiece(i - 1, j)).getType() == oppPlayer)               //increments pieceCount if adjacent 
                    ++pieceCount;                                                               //position contains an opposing piece
                if (i < 6 && *(Board1.getPiece(i + 1, j)).getType() == oppPlayer)               //
                    ++pieceCount;                                                               //
                if (j > 0 && *(Board1.getPiece(i, j - 1)).getType() == oppPlayer)               //
                    ++pieceCount;                                                               //
                if (j < 6 && *(Board1.getPiece(i, j + 1)).getType() == oppPlayer)               //
                    ++pieceCount;                                                               //
            }
            if (pieceCount >= 0 && pieceCount < 3)                                              //ignores positions with 4 adjacent
                pieceList[pieceCount].push_back(Board1.getPiece(i, j));                         //opposing pieces (no suicide moves)
        }
    }
    for (int i = 0; i < pieceList[2].size(); ++i)                                               //checks border conditions for 3 adjacent
    {                                                                                           //pieces
        if (*pieceList[2][i].getX() == 0 || *pieceList[2][i].getX() == 6 || *pieceList[2][i].getY() == 0 || *pieceList[2][i].getY() == 6)
            pieceList[2].erase(pieceList[2].begin() + i);
    }
    for (int i = 0; i < pieceList[1].size(); ++i)                                               //checks border conditions for 2 adjacent
    {                                                                                           //pieces
        if (*pieceList[1][i].getX() == 0 && *pieceList[1][i].getY() == 0 || *pieceList[1][i].getX() == 6 && *pieceList[1][i].getY() == 0 || *pieceList[1][i].getY() == 6 && *pieceList[1][i].getX() == 0 || *pieceList[1][i].getY() == 6 && *pieceList[1][i].getX() == 6)
            pieceList[1].erase(pieceList[1].begin() + i);
    }
                                                                                                //not necessary for 1 adjacent piece


    if (!pieceList[2].empty())                                                                  //if positions with 3 adjacent pieces exist
    {                                                                                           //places random piece of pieceList[2]
        int rngVal = rand() % pieceList[2].size();                                              //(vector of pieces with 3 adjacent pieces)
        Board1.placePiece(*pieceList[2][rngVal].getX(), *pieceList[2][rngVal].getY(), player);
        cout << "Player " << player << " placed Piece at " << *pieceList[2][rngVal].getY() + 1 << " " << *pieceList[2][rngVal].getX() + 1 << endl;
        //cout << "3 adjacent Pieces." << endl;
    }
    else if (!pieceList[1].empty())                                                             //if positions with 2 adjacent pieces exist
    {                                                                                           //places random piece of pieceList[1]
        int rngVal = rand() % pieceList[1].size();                                              //(vector of pieces with 2 adjacent pieces)
        Board1.placePiece(*pieceList[1][rngVal].getX(), *pieceList[1][rngVal].getY(), player);
        cout << "Player " << player << " placed Piece at " << *pieceList[1][rngVal].getY() + 1 << " " << *pieceList[1][rngVal].getX() + 1 << endl;
        //cout << "2 adjacent Pieces." << endl;
    }
    else if (!pieceList[0].empty())                                                             //if positions with 1 adjacent piece exist
    {                                                                                           //places random piece of pieceList[1]
        int rngVal = rand() % pieceList[0].size();                                              //(vector of pieces with 1 adjacent piece)
        Board1.placePiece(*pieceList[0][rngVal].getX(), *pieceList[0][rngVal].getY(), player);
        cout << "Player " << player << " placed Piece at " << *pieceList[0][rngVal].getY() + 1 << " " << *pieceList[0][rngVal].getX() + 1 << endl;
        //cout << "1 adjacent Piece." << endl;
    }
}

int main()                                                                                      
{
    srand(time(NULL));
    int player1 = 1, player2 = 2;
    Board Board1;
    for (int i = 0; i < 10;)                                                                    //simulates first 10 turns for each player
    {                                                                                           //randomly, without rules
        int x = rand() % 7;
        int y = rand() % 7;
        if(Board1.placePiece(x, y, player1))
            continue;
        x = rand() % 7;
        y = rand() % 7;
        if (Board1.placePiece(x, y, player2))
            continue;
        ++i;
    }
    for (int i = 0; i < 10; ++i)                                                                //calls both player simulations 
    {                                                                                           //wasnt sure if i was supposed to do c)
        Board1.printBoard();                                                                    //on their own boards or on the same board,
        cout << endl << endl;                                                                   //did the second. probably rather easy to do
        playerLines(Board1, player1);                                                           //the first instead.
        Board1.printBoard();
        cout << endl << endl;
        playerOpponentAdj(Board1, player2);
    }
    Board1.printBoard();
}