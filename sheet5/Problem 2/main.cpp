#include "go.h"
#include <iostream>
#include <vector>
#include <cassert>
#include <time.h>

using namespace std;

void playerLines(Board &Board1, int& player)
{
    vector<Piece> pieceList(0);
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (*(Board1.getPiece(i, j)).getType() == 0)
            {
                if (i > 0 && *(Board1.getPiece(i - 1, j)).getType() == player)
                    pieceList.push_back(Board1.getPiece(i, j));
                else if (i < 6 && *(Board1.getPiece(i + 1, j)).getType() == player)
                    pieceList.push_back(Board1.getPiece(i, j));
                else if (j > 0 && *(Board1.getPiece(i, j - 1)).getType() == player)
                    pieceList.push_back(Board1.getPiece(i, j));
                else if (j < 6 && *(Board1.getPiece(i, j + 1)).getType() == player)
                    pieceList.push_back(Board1.getPiece(i, j));
            }
        }
    }
    int rngVal = rand() % pieceList.size();
    Board1.placePiece(*pieceList[rngVal].getX(), *pieceList[rngVal].getY(), player);
    cout << "Player " << player << " placed Piece at " << *pieceList[rngVal].getY()+1 << " " << *pieceList[rngVal].getX()+1 << endl;
}

void playerOpponentAdj(Board &Board1, int& player)
{
    int oppPlayer;
    if (player == 1)
        oppPlayer = 2;
    if (player == 2)
        oppPlayer = 1;
    vector<vector<Piece>> pieceList = vector<vector<Piece>> (3, vector<Piece>(0));
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            int pieceCount = -1;
            if (*(Board1.getPiece(i, j)).getType() == 0)
            {
                if (i > 0 && *(Board1.getPiece(i - 1, j)).getType() == oppPlayer)
                    ++pieceCount;

                if (i < 6 && *(Board1.getPiece(i + 1, j)).getType() == oppPlayer)
                    ++pieceCount;

                if (j > 0 && *(Board1.getPiece(i, j - 1)).getType() == oppPlayer)
                    ++pieceCount;

                if (j < 6 && *(Board1.getPiece(i, j + 1)).getType() == oppPlayer)
                    ++pieceCount;

            }
            if (pieceCount >= 0 && pieceCount < 3)
                pieceList[pieceCount].push_back(Board1.getPiece(i, j));
        }
    }
    for (int i = 0; i < pieceList[2].size(); ++i)
    {
        if (*pieceList[2][i].getX() == 0 || *pieceList[2][i].getX() == 6 || *pieceList[2][i].getY() == 0 || *pieceList[2][i].getY() == 6)
            pieceList[2].erase(pieceList[2].begin() + i);
    }
    for (int i = 0; i < pieceList[1].size(); ++i)
    {
        if (*pieceList[1][i].getX() == 0 && *pieceList[1][i].getY() == 0 || *pieceList[1][i].getX() == 6 && *pieceList[1][i].getY() == 0 || *pieceList[1][i].getY() == 6 && *pieceList[1][i].getX() == 0 || *pieceList[1][i].getY() == 6 && *pieceList[1][i].getX() == 6)
            pieceList[1].erase(pieceList[1].begin() + i);
    }

    if (!pieceList[2].empty())
    {
        int rngVal = rand() % pieceList[2].size();
        Board1.placePiece(*pieceList[2][rngVal].getX(), *pieceList[2][rngVal].getY(), player);
        cout << "Player " << player << " placed Piece at " << *pieceList[2][rngVal].getY() + 1 << " " << *pieceList[2][rngVal].getX() + 1 << endl;
        //cout << "3 adjacent Pieces." << endl;
    }
    else if (!pieceList[1].empty())
    {
        int rngVal = rand() % pieceList[1].size();
        Board1.placePiece(*pieceList[1][rngVal].getX(), *pieceList[1][rngVal].getY(), player);
        cout << "Player " << player << " placed Piece at " << *pieceList[1][rngVal].getY() + 1 << " " << *pieceList[1][rngVal].getX() + 1 << endl;
        //cout << "2 adjacent Pieces." << endl;
    }
    else if (!pieceList[0].empty())
    {
        int rngVal = rand() % pieceList[0].size();
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
    for (int i = 0; i < 10;)
    {
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
    for (int i = 0; i < 10; ++i)
    {
        Board1.printBoard();
        cout << endl << endl;
        playerLines(Board1, player1);
        Board1.printBoard();
        cout << endl << endl;
        playerOpponentAdj(Board1, player2);
    }
    Board1.printBoard();
}