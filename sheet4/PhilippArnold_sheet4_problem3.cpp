#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <time.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

const int   G_CONST_CARRIER = 5,
            G_CONST_BATTLESHIP = 4,
            G_CONST_CRUISER = 3,
            G_CONST_DESTROYER = 2,
            G_CONST_SUBMARINE = 1;
int         G_COUNTER = 0;

int rNG(int x)
{
    return 0 + rand() % x;
}

void setShipPosition(vector<vector<int>> *battlefieldGhost, const int *shipsize)
{
    
    while (true)
    {
        int m, n, u, d, l, r, check;
        int uu=0, dd=0, ll=0, rr=0;
        while (true)
        {
            m = rNG(10);
            n = rNG(10);
            if ((*battlefieldGhost)[m][n])
            {
                continue;
            }
            break;
        }
        
        while (true)
        {
            int dir; 
            check = 0;
            u = 0;
            d = 0;
            l = 0;
            r = 0;
            dir = rNG(4);
            if (dir == 0)
            {
                u = 1;
                uu = 1;
            }
            if (dir == 1)
            {
                d = 1;
                dd = 1;
            }
            if (dir == 2)
            {
                l = 1;
                ll = 1;
            }
            if (dir == 3)
            {
                r = 1;
                rr = 1;
            }
            for (int i = 1; i <= *shipsize; ++i)
            {
                if (u)
                {
                    if ((m - i) < 0 || (*battlefieldGhost)[m - i][n])
                    {
                        check = 1;
                        continue;
                    }
                }
                if (d)
                {
                    if ((m + i) > 9 || (*battlefieldGhost)[m + i][n])
                    {
                        check = 1;
                        continue;
                    }
                }
                if (l)
                {
                    if ((n - i) < 0 || (*battlefieldGhost)[m][n - i])
                    {
                        check = 1;
                        continue;
                    }
                }
                if (r)
                {
                    if ((n + i) > 9 || (*battlefieldGhost)[m][n + i])
                    {
                        check = 1;
                        continue;
                    }
                }
            }
            if (check)
            {
                continue;
            }
            else
            {
                break;
            }
        }
        if (uu&&dd&&ll&rr&&check)
        {
            continue;
        }
        else
        {
            for (int i = 0; i < *shipsize; ++i)
            {
                if (u)
                {
                    (*battlefieldGhost)[m - i][n] = 1;
                    ++G_COUNTER;
                }
                if (d)
                {
                    (*battlefieldGhost)[m + i][n] = 1;
                    ++G_COUNTER;
                }
                if (l)
                {
                    (*battlefieldGhost)[m][n - i] = 1;
                    ++G_COUNTER;
                }
                if (r)
                {
                    (*battlefieldGhost)[m][n + i] = 1;
                    ++G_COUNTER;
                }
            }
            break;
        }
    }
}

void initBattlefield(vector<vector<char>> *battlefield)
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            (*battlefield)[i][j] = '~';
        }
    }
}

void printBattlefield(vector<vector<char>> *battlefield)
{
    cout << " Y" <<endl;  
    for (int i = 0; i < 10; ++i)
    {
        cout << setw(2) << i << "  ";
        for (int j = 0; j < 10; ++j)
        {
            cout << (*battlefield)[i][j] << "  ";
        }
            cout << endl;
    }
    cout << " # ";
    for (int i = 0; i < 10; ++i)
    {
        cout << setw(2) << i << " ";
    }

    cout << " X " << endl;
}

void initBattlefieldGhost(vector<vector<int>> *battlefieldGhost)
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            (*battlefieldGhost)[i][j] = 0;
        }
    }
    setShipPosition(battlefieldGhost, &G_CONST_CARRIER);
    setShipPosition(battlefieldGhost, &G_CONST_BATTLESHIP);
    setShipPosition(battlefieldGhost, &G_CONST_CRUISER);
    setShipPosition(battlefieldGhost, &G_CONST_DESTROYER);
    setShipPosition(battlefieldGhost, &G_CONST_DESTROYER);
    setShipPosition(battlefieldGhost, &G_CONST_SUBMARINE);
    setShipPosition(battlefieldGhost, &G_CONST_SUBMARINE);
}

void takeInput(vector<vector<char>> *battlefield, vector<vector<int>> *battlefieldGhost)
{
    int x, y;
    cout << "Enter coordinates: " << endl;
    while (true)
    {
        cout << "X: ";
        cin >> x;

        if (cin.fail() || x < 0 || x > 9)     //check for valid input
        {
            cin.clear();    //clear output stream to avoid skipping future inputs
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Not a valid numerical. Try again." << endl;
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "Y: ";
        cin >> y;

        if (cin.fail() || y < 0 || y > 9)     //check for valid input
        {
            cin.clear();    //clear output stream to avoid skipping future inputs
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Not a valid numerical. Try again." << endl;
            continue;
        }
        break;
    }

    if ((*battlefieldGhost)[y][x] == 1)
    {
        (*battlefield)[y][x] = 'X';
        (*battlefieldGhost)[y][x] = 0;
        --G_COUNTER;
    }
    else
    {
        if ((*battlefield)[y][x] != 'X')
        {
            (*battlefield)[y][x] = 'O';
        }
    }
}

int main()
{
    srand(time(NULL));
    vector<vector<char>> battlefield(10, vector<char>(10));
    vector<vector<int>> battlefieldGhost(10, vector<int>(10));
    initBattlefield(&battlefield);
    initBattlefieldGhost(&battlefieldGhost);
    while (true)
    {
        printBattlefield(&battlefield);
        takeInput(&battlefield, &battlefieldGhost);
        system(CLEAR);
        if (!G_COUNTER)
        {
            cout << "YOU WIN!" << endl;
            break;
        }
    }
}