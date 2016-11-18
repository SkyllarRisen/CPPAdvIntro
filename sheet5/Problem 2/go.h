#ifndef GO_H
#define GO_H
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>


class Piece                 //Class defining your game pieces
{                           //Every Piece keeps track of its type, its group index, and its position.
private:
    int m_type;     
    int m_grpID;
    int m_x;
    int m_y;
    
    
public:                     //Public Interface
    Piece();
    int const *getType();
    void setType(int type);
    int const *getGrpID();
    void setGrpID(int ID);
    int const *getX();
    void setX(int x);
    int const *getY();
    void setY(int y);

};

class Board                 //Defines the board. Stores and allows the placement of pieces. Checks for and stores piece chains. 
{                           //Checks for liberties of said chains. Tracks the game score. Prints the board and game score.
private:
    std::vector<std::vector<Piece>> goBoard = std::vector<std::vector<Piece>>(7, std::vector<Piece>(7));
    std::vector<std::vector<Piece>> vecGrps;
    std::vector<Piece> placedPieces;
    void getLiberties();
    void getGroups();
    void reassignGrpID();
    int m_whiteScore, m_blackScore;
    int m_counter;
    void trimVec();
public:                     //Public Interface
    Board();
    void printBoard();
    void printGrpID();
    int placePiece(int x, int y, int type);
    Piece getPiece(int x, int y);
};



























#endif
