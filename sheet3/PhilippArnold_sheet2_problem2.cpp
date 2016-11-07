#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>


void divWithRem(int a, int b)
{
    using namespace std;
    int h = a / b;      //auxiliar variable, careful, compiler/c++ version dependant result with negative numbers
    cout << a << " / " << b << " = " << h;
    cout << ", remainder: " << a%b << endl;
}

double myfunc(double a, double b)
{
    return a*a + b*b;
}

int main()
{
    using namespace std;
    int myArray[5]{ 1, 3, 5, 7, 9 };        //(a)
    for (int i = 0; i < 5; i++)
    {
        cout << "myArray[" << i << "] = " << myArray[i] << endl;
    }
    
    double f, x;        //(b)
    x = 1.0000;     
    f = sin(x);     //x in radian
    printf("sin( %.4f ) = %.4f \n", x, f);
    divWithRem(7, 2);
    double result = myfunc(5, 2);
    cout << result << endl;
}