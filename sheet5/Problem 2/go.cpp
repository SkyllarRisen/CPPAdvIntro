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
                m_whiteScore = 0;
                m_blackScore = 0;
            }
    }
}

Piece Board::getPiece(int x, int y)
{
    return goBoard[x][y];
}

void Board::printBoard()
{
    std::cout << "  ";
    for (int j = 0; j < 7; ++j)
        std::cout << j + 1 << " ";
    std::cout << "\t" << "Score White(o): " << m_whiteScore << "\t" <<"Score Black(#): " << m_blackScore <<std::endl;
    for (int i = 0; i < 7; ++i)
    {
        std::cout << i + 1 << " ";
        for (int j = 0; j < 7; ++j)
        {
            if (*goBoard[i][j].getType() == 0)
                std::cout << (char)254 << " ";
            if(*goBoard[i][j].getType()==1)
                std::cout << "o ";
            if (*goBoard[i][j].getType() == 2)
                std::cout << "# ";
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

int Board::placePiece(int x, int y, int type)
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
        for(int i =0; i<=5;++i)
            getGroups();
        
        trimVec();
        reassignGrpID();
        getLiberties();
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
        for (int j = 0; j < vecGrps[i].size(); ++j)
        {
            for (int k = 0; k < vecGrps[i].size(); ++k)
            {
                if (j != k && (*vecGrps[i][j].getX()) == (*vecGrps[i][k].getX()) && (*vecGrps[i][j].getY()) == (*vecGrps[i][k].getY()))
                {                   
                    vecGrps[i].erase(vecGrps[i].begin() + k);
                }
            }
        }
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

void Board::getLiberties()
{
    trimVec();
    reassignGrpID();
    for (int i = 0; i < vecGrps.size(); ++i)
    {
        int liberties=0;
        liberties = 0;
        for (int j = 0; j < vecGrps[i].size(); ++j)
        {
            if (*vecGrps[i][j].getX()> 0 && *goBoard[*vecGrps[i][j].getX() - 1][*vecGrps[i][j].getY()].getType() == 0)
                ++liberties;
            if (*vecGrps[i][j].getX()< 6 && *goBoard[*vecGrps[i][j].getX() + 1][*vecGrps[i][j].getY()].getType() == 0)
                ++liberties;
            if (*vecGrps[i][j].getY()> 0 && *goBoard[*vecGrps[i][j].getX()][*vecGrps[i][j].getY() - 1].getType() == 0)
                ++liberties;
            if (*vecGrps[i][j].getY()< 6 && *goBoard[*vecGrps[i][j].getX()][*vecGrps[i][j].getY() + 1].getType() == 0)
                ++liberties;
        }
        if (liberties == 0 && vecGrps[i].size() > 0)
        {
            if (*vecGrps[i][0].getType() == 1)
                m_blackScore += vecGrps[i].size();
            if (*vecGrps[i][0].getType() == 2)
                m_whiteScore += vecGrps[i].size();
            for (int j = 0; j < vecGrps[i].size(); ++j)
            {
                goBoard[*vecGrps[i][j].getX()][*vecGrps[i][j].getY()].setGrpID(-1);
                goBoard[*vecGrps[i][j].getX()][*vecGrps[i][j].getY()].setType(0);
                for (int k = 0; k < placedPieces.size(); ++k)
                {

                    if (*placedPieces[k].getX() == *vecGrps[i][j].getX() && *placedPieces[k].getY() == *vecGrps[i][j].getY())
                    {
                        placedPieces.erase(placedPieces.begin() + k);
                    }
                }
            }
            vecGrps[i].erase(vecGrps[i].begin(), vecGrps[i].end());
        }
    }
    trimVec();
}


void Board::getGroups()
{

    for (int i = 0; i < placedPieces.size(); ++i)
    {
        for (int j = 0; j < placedPieces.size(); ++j)
        {
            if (*placedPieces[i].getType() == *placedPieces[j].getType())
            {
                
                if (*placedPieces[i].getX() + 1 == *placedPieces[j].getX() && *placedPieces[i].getY() == *placedPieces[j].getY())
                {                   
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
            }
        }
    }
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

