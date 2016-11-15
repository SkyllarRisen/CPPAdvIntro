#include "go.h"


Board::Board()
{
    {
        for (int i = 0; i < 7; ++i)
            for (int j = 0; j < 7; ++j)
            {
                (goBoard[i][j]).setType(0);
                (goBoard[i][j]).setX(i);
                (goBoard[i][j]).setY(j);
                (goBoard[i][j]).setGrpID(-1);
                m_counter = 0;
                
            }
    }
}

void Board::printBoard()
{
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            std::cout << *goBoard[i][j].getType() << " ";
        }
        std::cout << std::endl;
    }
}

void Board::printGrpID()
{
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            std::cout << *goBoard[i][j].getGrpID() << " ";
        }
        std::cout << std::endl;
    }
}

int Board::placePiece(int& x, int& y, int& type)
{
    assert(x >= 0 && x < 7);
    assert(y >= 0 && y < 7);
    if (*goBoard[x][y].getType() == 0)
    {
        goBoard[x][y].setType(type);
        placedPieces.push_back(goBoard[x][y]);
        goBoard[x][y].setGrpID(m_counter);
        std::vector<Piece> temp;
        temp.push_back(goBoard[x][y]);
        vecGrps.push_back(temp);
        getGroups();
        return 0;
    }
    else
    {
        return 1;
    }

}

void Board::trimVec()
{
    for (int i = 0; i < vecGrps.size(); ++i)
    {
        if (vecGrps[i].size() == 0)
            vecGrps.erase(vecGrps.begin() + i);
    }
}

void Board::reassignGrpID()
{
    for (int i = 0; i < vecGrps.size(); ++i)
    {
        for (int j = 0; j < vecGrps[i].size(); ++j)
        {
            goBoard[*vecGrps[i][j].getX()][*vecGrps[i][j].getY()].setGrpID(i);
        }
    }
}


void Board::getGroups()
{

    for (int i = 0; i < placedPieces.size(); ++i)
    {
        for (int j = 0; j < placedPieces.size(); ++j)
        {
            if (*placedPieces[i].getType() == *placedPieces[j].getType() && i != j)
            {
                
                if (*placedPieces[i].getX() + 1 == *placedPieces[j].getX() && *placedPieces[i].getY() == *placedPieces[j].getY())
                {
                    std::cout << *placedPieces[i].getX() << " " << *placedPieces[i].getY() << " " << m_counter << " " << *placedPieces[i].getGrpID() << std::endl;
                    std::cout << *placedPieces[j].getX() << " " << *placedPieces[j].getY() << " " << m_counter << " " << *placedPieces[j].getGrpID() << std::endl;
                    vecGrps[*goBoard[*placedPieces[i].getX()][*placedPieces[i].getY()].getGrpID()].push_back(goBoard[*placedPieces[j].getX()][*placedPieces[j].getY()]);
                    for (int k = 0; k < vecGrps.size(); ++k)
                    {
                        for (int l = 0; l < vecGrps[k].size(); ++l)
                        {
                            if (k != *goBoard[*placedPieces[i].getX()][*placedPieces[i].getY()].getGrpID() && *vecGrps[k][l].getX() == *placedPieces[j].getX() && *vecGrps[k][l].getY() == *placedPieces[j].getY())
                            {
                                vecGrps[k].erase(vecGrps[k].begin() + l);
                            }
                        }
                    }
                }
                else if (*placedPieces[i].getX() == *placedPieces[j].getX() && *placedPieces[i].getY() + 1 == *placedPieces[j].getY())
                {
                    std::cout << *placedPieces[i].getX() << " " << *placedPieces[i].getY() << " " << m_counter << " " << *placedPieces[i].getGrpID() << std::endl;
                    std::cout << *placedPieces[j].getX() << " " << *placedPieces[j].getY() << " " << m_counter << " " << *placedPieces[j].getGrpID() << std::endl;
                    vecGrps[*goBoard[*placedPieces[i].getX()][*placedPieces[i].getY()].getGrpID()].push_back(goBoard[*placedPieces[j].getX()][*placedPieces[j].getY()]);
                    for (int k = 0; k < vecGrps.size(); ++k)
                    {
                        for (int l = 0; l < vecGrps[k].size(); ++l)
                        {
                            if (k != *goBoard[*placedPieces[i].getX()][*placedPieces[i].getY()].getGrpID() && *vecGrps[k][l].getX() == *placedPieces[j].getX() && *vecGrps[k][l].getY() == *placedPieces[j].getY())
                            {
                                vecGrps[k].erase(vecGrps[k].begin()+l);
                            }
                        }
                    }
                }
                trimVec();
                reassignGrpID();




/*            std::cout << "im here." << std::endl;
            if (*placedPieces[i].getType()==*placedPieces[j].getType() && i!=j)
            {
                if (*placedPieces[i].getX() + 1 == *placedPieces[j].getX() && *placedPieces[i].getY() == *placedPieces[j].getY())
                {
                    std::cout << *placedPieces[i].getX() << " " << *placedPieces[i].getY() << " " << m_counter << " " << *placedPieces[i].getGrpID() << std::endl;
                    std::cout << *placedPieces[j].getX() << " " << *placedPieces[j].getY() << " " << m_counter << " " << *placedPieces[j].getGrpID() << std::endl;
                    goBoard[*placedPieces[j].getX()][*placedPieces[j].getY()].setGrpID(*goBoard[*placedPieces[i].getX()][*placedPieces[i].getY()].getGrpID());

                }
                else if (*placedPieces[i].getX() == *placedPieces[j].getX() && *placedPieces[i].getY() + 1 == *placedPieces[j].getY())
                {
                    std::cout << *placedPieces[i].getX() << " " << *placedPieces[i].getY() << " " << m_counter << " " << *placedPieces[i].getGrpID() << std::endl;
                    std::cout << *placedPieces[j].getX() << " " << *placedPieces[j].getY() << " " << m_counter << " " << *placedPieces[j].getGrpID() << std::endl;
                    goBoard[*placedPieces[j].getX()][*placedPieces[j].getY()].setGrpID(*goBoard[*placedPieces[i].getX()][*placedPieces[i].getY()].getGrpID());
                }*/
            }
        }
    }
    //if (*placedPieces[i].getX() == *placedPieces[j].getX() && *placedPieces[i].getY() == *placedPieces[j].getY() && i != j)
      //  placedPieces.erase(placedPieces.begin() + j);
}


Piece::Piece()
{

}

void Piece::setType(int type)
{
    assert(type >= 0 && type <= 2);
    m_type = type;
    
}

void Piece::setGrpID(int ID)
{
    m_grpID = ID;
}

void Piece::setX(int x)
{
    m_x = x;
}

void Piece::setY(int y)
{
    m_y = y;
}

int const *Piece::getType()
{
    int const *m_typeptr = &m_type;
    return m_typeptr;
}

int const *Piece::getGrpID()
{
    int const *m_grpIDPtr = &m_grpID;
    return m_grpIDPtr;
}

int const *Piece::getX()
{
    int const *m_xPtr = &m_x;
    return m_xPtr;
}

int const *Piece::getY()
{
    int const *m_yPtr = &m_y;
    return m_yPtr;
}

