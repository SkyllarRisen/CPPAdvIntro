#include "go.h"


Board::Board()                                                                  //Default Constructor
{                                                                               //Sets default values for member variables.
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

Piece Board::getPiece(int x, int y)                                             //used to access Pieces in goBoard outside of member functions.
{
    return goBoard[x][y];
}

void Board::printBoard()                                                        //prints the board and current score
{                                                                               //could be altered to clear screen
    std::cout << "  ";                                                          //was kept in current state for easier evaluation (youre welcome)
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

void Board::printGrpID()                                                        //prints the group index of pieces, used for debug only
{                                                                               //currently not in use
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            std::cout << *goBoard[i][j].getGrpID() << " ";
        }
        std::cout << std::endl;
    }
}

int Board::placePiece(int x, int y, int type)                                   //takes and validates input 
{                                                       
    assert(x >= 0 && x < 7);
    assert(y >= 0 && y < 7);
    if (*goBoard[x][y].getType() == 0)
    {
        goBoard[x][y].setType(type);
        placedPieces.push_back(goBoard[x][y]);                                  //pushes placed pieces into vector "placedPieces"
        goBoard[x][y].setGrpID(m_counter);
        std::vector<Piece> temp;
        temp.push_back(goBoard[x][y]);
        vecGrps.push_back(temp);                                                //creates group for a placed piece.
        for(int i =0; i<=5;++i)                                                 //dirty bandaid fix for issues with groups not updating properly for bigger chains
            getGroups();                                                        //not good for performance but im sick of trying to fix it differently
        
        trimVec();                                                              //clears unused group vectors and deletes duplicate pieces
        reassignGrpID();                                                        //sets m_grpID to group vectors index
        getLiberties();                                                         //calculates liberties and removes captured piece chains
        return 0;
    }
    else
    {
        return 1;                                       
    }

}

void Board::trimVec()                                                           //used this function rather liberally. Some calls might be unnecessary. Better safe than sorry.
{
    for (int i = 0; i < vecGrps.size(); ++i)                                    //loops through all group vectors
    {
        if (vecGrps[i].size() == 0)                                             //erases if group vector empty
            vecGrps.erase(vecGrps.begin() + i);
        for (int j = 0; j < vecGrps[i].size(); ++j)                             //compares pieces in a group vector and erases duplicates
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
    for (int i = 0; i < vecGrps.size(); ++i)                                    //loops through all group vectors
    {
        for (int j = 0; j < vecGrps[i].size(); ++j)                             //loops through all pieces of a group vector and sets m_grpID to group vector index
        {
            goBoard[*vecGrps[i][j].getX()][*vecGrps[i][j].getY()].setGrpID(i);      
        }
    }
}

void Board::getLiberties()                              
{
    trimVec();
    reassignGrpID();
    for (int i = 0; i < vecGrps.size(); ++i)                                    //loops through all group vectors
    {
        int liberties=0;
        liberties = 0;
        for (int j = 0; j < vecGrps[i].size(); ++j)                             //loops through all pieces of a group vector and checks for adjacent free spaces, adds to liberties
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
        if (liberties == 0 && vecGrps[i].size() > 0)                            //checks if piece chain has no liberties
        {
            if (*vecGrps[i][0].getType() == 1)                                  //adds chain to score
                m_blackScore += vecGrps[i].size();
            if (*vecGrps[i][0].getType() == 2)
                m_whiteScore += vecGrps[i].size();
            for (int j = 0; j < vecGrps[i].size(); ++j)                         //removes captured piece chain from the board
            {
                goBoard[*vecGrps[i][j].getX()][*vecGrps[i][j].getY()].setGrpID(-1);
                goBoard[*vecGrps[i][j].getX()][*vecGrps[i][j].getY()].setType(0);
                for (int k = 0; k < placedPieces.size(); ++k)                   //removes captured pieces from placedPieces vector
                {
                                                                            
                    if (*placedPieces[k].getX() == *vecGrps[i][j].getX() && *placedPieces[k].getY() == *vecGrps[i][j].getY())
                    {
                        placedPieces.erase(placedPieces.begin() + k);
                    }
                }
            }
            vecGrps[i].erase(vecGrps[i].begin(), vecGrps[i].end());             //erases group vector of captured piece chain
        }
    }
    trimVec();
}


void Board::getGroups()                                                         //ehh, magic, dont touch? :D
{

    for (int i = 0; i < placedPieces.size(); ++i)                               //compares placed pieces
    {
        for (int j = 0; j < placedPieces.size(); ++j)
        {
            if (*placedPieces[i].getType() == *placedPieces[j].getType())       //checks for adjacent pieces of same type(color)
            {
                
                if (*placedPieces[i].getX() + 1 == *placedPieces[j].getX() && *placedPieces[i].getY() == *placedPieces[j].getY())
                {                                                               //pushes found match into other piece's vector group
                    vecGrps[*goBoard[*placedPieces[i].getX()][*placedPieces[i].getY()].getGrpID()].push_back(goBoard[*placedPieces[j].getX()][*placedPieces[j].getY()]);                    

                    for (int k = 0; k < vecGrps.size(); ++k)                    //erases piece from old vector group
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
                {                                                               //pushes found match into other piece's vector group
                    vecGrps[*goBoard[*placedPieces[i].getX()][*placedPieces[i].getY()].getGrpID()].push_back(goBoard[*placedPieces[j].getX()][*placedPieces[j].getY()]);
                    for (int k = 0; k < vecGrps.size(); ++k)                    //erases piece from old vector group
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
                reassignGrpID();                                                //updates m_grpID to new values
            }
        }
    }
}


Piece::Piece()                                                                  //empty default constructor, technically not needed
{

}

void Piece::setType(int type)                                                   //sets m_type to given value
{
    assert(type >= 0 && type <= 2);
    m_type = type;
    
}

void Piece::setGrpID(int ID)                                                    //sets m_grpID to given value
{
    m_grpID = ID;
}

void Piece::setX(int x)                                                         //sets m_x to given value
{
    m_x = x;
}

void Piece::setY(int y)                                                         //sets m_y to given value
{
    m_y = y;
}

int const *Piece::getType()                                                     //returns pointer to type of piece
{
    int const *m_typeptr = &m_type;
    return m_typeptr;
}

int const *Piece::getGrpID()                                                    //returns pointer to group index of piece
{
    int const *m_grpIDPtr = &m_grpID;
    return m_grpIDPtr;
}

int const *Piece::getX()                                                        //returns pointer to x coordinate of piece
{
    int const *m_xPtr = &m_x;
    return m_xPtr;
}

int const *Piece::getY()                                                        //returns pointer to y coordinate of piece
{
    int const *m_yPtr = &m_y;
    return m_yPtr;
}

