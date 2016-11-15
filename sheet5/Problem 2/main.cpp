#include "go.h"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int main()
{
    int player1 = 1, player2 = 2;
    Board Board1;
    Board1.printBoard();
    Board1.printGrpID();
    while (true)
    {
        while (true)
        {
            int x, y;
            cin >> x;
            cin >> y;
            --x;
            --y;
            if (Board1.placePiece(x, y, player1))
                continue;
            break;
        }
        Board1.printBoard();
        Board1.printGrpID();
        while (true)
        {
            int x, y;
            cin >> x;
            cin >> y;
            --x;
            --y;
            if (Board1.placePiece(x, y, player2))
                continue;
            break;
        }
        Board1.printBoard();
        Board1.printGrpID();
    }
}