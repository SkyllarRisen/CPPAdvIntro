#include <iostream>
#include <vector>

using namespace std;

void getInt(int *i, int x)                                                                      //read integer
{
    while(true)
    {
        if (x == 1) { cout << "Number of rows M: "; }                                           //additional argument for reuseability of the function
        else if (x == 2) { cout << "Number of columns N: "; }
        else if (x == 3) { cout << "Number of row you want to print: "; }
        cin >> *i;
        if (cin.fail())                                                                         //check for bad input
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Try again. ";
            continue;
        }
        break;
    }
}



void defineMatrix(int *m, int *n)                                                               //define Matrix dimensions
{
    cout << "Please define the MxN matrix you want to work with:" << endl;
    getInt(m,1);
    getInt(n,2);
}

void readNumber(double *x)                                                                      //read double
{
    while (true)
    {
        cin >> *x;           
        if (cin.fail())                                                                         //check for bad input
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Try again: ";
            continue;
        }
        break;
    }
}

void fillMatrix(vector<vector<double>> *matrix)                                                 //selects the matrix element, then calls readNumber
{
    
    for (int m = 0; m < (*matrix).size(); ++m)
    {
        for (int n = 0; n < (*matrix)[m].size(); ++n)
        {
            cout << "Enter a number (" << m+1 << "," << n+1 << "): ";
            readNumber(&(*matrix)[m][n]);
        }
    }
}

void multiplyWithConstant(vector<vector<double>> *matrix)                                       //multiplies with constant
{
    double x;
    cout << "Enter a constant: ";
    readNumber(&x);
    for (int m = 0; m < (*matrix).size(); ++m)
    {
        for (int n = 0; n < (*matrix)[m].size(); ++n)
        {
            (*matrix)[m][n] *=x;
        }
    }
}

void printMatrix(vector<vector<double>> *matrix)                                                //prints the matrix
{
    for (int m = 0; m < (*matrix).size(); ++m)
    {
        for (int n = 0; n < (*matrix)[m].size(); ++n)
        {
            cout << (*matrix)[m][n] << " ";
        }
        cout << endl;
    }
}

void printRow(vector<vector<double>> *matrix)                                                   //prints the selected row of the matrix
{
    int m;
    while (true)
    {
        getInt(&m, 3);
        if (m<1 || m>(*matrix).size())
        {
            cout << "Enter a number between 1 and " << (*matrix).size() << "." << endl;
            continue;
        }
        break;
    }
    for (int n = 0; n < (*matrix)[m-1].size(); ++n)
    {
        cout << (*matrix)[m-1][n] << " ";
    }
    cout << endl;
}

int main()                                                                                      //function calls and variable declarations
{
    int m, n;
    defineMatrix(&m, &n);
    vector<vector<double>> matrix(m,vector<double>(n));
    fillMatrix(&matrix);
    multiplyWithConstant(&matrix);
    printMatrix(&matrix);
    printRow(&matrix);
}

