#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <string>
#include <ctime>

using namespace std;

void takeInput(int& input)
{
    while (true)
    {
        cout << "Enter a number between 1 and 100: ";
        cin >> input;
        if (cin.fail())
        {
            cout << "Not a numerical. Try again." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        if (input > 100 || input < 1)
        {
            cout << "Not a number between 1 and 100. Try again." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        break;
    }
}

void problemOneF()
{ 
    int input=0, rngNum;
    rngNum = 1 + rand() % 100;
    while (input != rngNum)
    {
        takeInput(input);
        if (input > rngNum)
        {
            cout << "Too high." << endl;
            continue;
        }
        if (input < rngNum)
        {
            cout << "Too low." << endl;
            continue;
        }
        if (input == rngNum)
        {
            cout << "You guessed right!" << endl;
            break;
        }
    }
}

int problemOneE()
{
    int count = 3;
    while (true)
    {
        string passwordInput;
        cout << "Enter Password: ";
        getline(cin, passwordInput);
        if (passwordInput == "aAbBcCdD91")
            return 0;
        else
        {
            --count;
            if (count == 0)
                return 1;
            cout << "Wrong password. You have " << count << " tries left." << endl;
        }
    }
}

int problemOneD(int& const n, int& const k)
{
    int nfac=1, kfac=1, nminuskfac=1;
    for (int i = 1; i <= n; ++i)
        nfac *= i;
    for (int i = 1; i <= k; ++i)
        kfac *= i;
    for (int i = 1; i <= (n-k); ++i)
        nminuskfac *= i;
    return nfac / (kfac*nminuskfac);
}

/*void problemOneC(int& const upperLimit)                           //solution as specified by the problem
{                                                                   //
    int factorial = 1;                                              //
    int i = 2;                                                      //
    while (true)                                                    //
    {                                                               //
        if (factorial*i > upperLimit)                               //
            break;                                                  //
        factorial *= i;                                             //
        i++;                                                        //
    }                                                               //
    cout << factorial << endl << endl;                              //
}*/                                                                 //

void problemOneC(int& const upperLimit)                             //easier solution without having to use
{                                                                   //break;
    int factorial=1;                                                //
    for(int i=1;factorial*i < upperLimit;i++)                       //
    {                                                               //
        factorial *= i;                                             //
    }                                                               //
    cout << factorial << endl << endl;                              //
}                                                                   //

void printCheck(vector<int> &adrVec)
{
    for (int i=0; i < adrVec.size(); i++)
        cout << adrVec.at(i) << " ";
    cout << endl << endl;
}

void problemOneB(vector<int> &adrVec)
{
    for (int i = 0; i < adrVec.size();)
    {
        cout << adrVec.at(i) << " ";
        i += 2;
    }
    cout << endl << endl;
}

void problemOneA(vector<int> &adrVec)
{
    for (int i = 1; i < adrVec.size();)
    {
        adrVec.at(i) = 0;
        i += 2;
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    vector<int> vector1 { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    int limit1 = 50, n = 5, k=2;
    assert(n >= k);
    printCheck(vector1);
    problemOneA(vector1);
    printCheck(vector1);
    problemOneB(vector1);
    problemOneC(limit1);
    cout << problemOneD(n, k) << endl;
    problemOneF();
    if (!problemOneE())
    {
        cout << "Welcome to nothing. Program will exit now." << endl;
        return 0;
    }
    else
    {
        cout << "No tries left. Program will exit now." << endl;
        return 0;
    }
    return 0;
}