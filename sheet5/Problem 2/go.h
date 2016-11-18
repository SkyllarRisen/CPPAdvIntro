#ifndef GO_H
#define GO_H
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert>


class Piece
{
private:
    int m_type;
    int m_grpID;
    int m_x;
    int m_y;
    
    
public:
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

class Board
{
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
public:
    Board();
    void printBoard();
    void printGrpID();
    int placePiece(int x, int y, int type);
    Piece getPiece(int x, int y);
};



























#endif
