#include <iostream>

using namespace std;        /*DISCLAIMER: This program represents a solution based on the specifications given.
                                          Its in no way the most elegant or most practical solution. I'd recommend
                                          using std::vector class containers as a substitute for C-Style Arrays.
                                          That way you could scale the dimension of the scalarproduct based on the 
                                          vectors given, and thats just one of the advantages.*/
//b)
int myfunc(int &x, int &y)  //returns product of 2 integers by reference
{
    return x*y;
}

int myfuncPointer(int *x, int *y)   //returns product of 2 integers with 2 pointers as arguments
{
    return *x * *y;
}
//c)
double scalarProduct(double *arr1, double *arr2, const int *dim)    //returns the scalar product of 2 double arrays of dimension dim
{
    double spResult=0;
    for (int i = 0; i < *dim; ++i)
    {
        spResult += *(arr1+i) * *(arr2+i);
    }
    return spResult;
}
//d)
void outerProduct(double *arr1, double *arr2, double *result)   //returns the vector product of 2 arrays to another array given as an argument
{
    *result = *(arr1+1) * *(arr2+2) - *(arr1+2) * *(arr2+1);
    *(result+1) = *(arr1 + 2) * *(arr2) - *(arr1) * *(arr2 + 2);
    *(result+2) = *(arr1) * *(arr2 + 1) - *(arr1 + 1) * *(arr2);
}

int main()
{
    int *pointer1, array1[10], x=5, y=2;    //i refuse to comment this
    const int dim = 3;
    double *pointer2, array2[10];
    long double *pointer3, array3[10];
    pointer1 = array1;
    pointer2 = array2;
    pointer3 = array3;
    cout << pointer1 << "\t" << *pointer1 << endl << pointer2 << "\t" << *pointer2 << endl << pointer3 << "\t" << *pointer3 << endl;    //a)
    cout << ++pointer1 << "\t" << *pointer1 << endl << ++pointer2 << "\t" << *pointer2 << endl << ++pointer3 << "\t" << *pointer3 << endl;  //a)
    cout << myfunc(x, y) << endl;   //b)
    cout << myfuncPointer(&x, &y) << endl;  //b)
    double arr1[dim]{ 1,2,3 }, arr2[dim]{ 4,5,6 };  //c)
    double kpArr1[3]{ 1,3,5 }, kpArr2[3]{ 2,4,6 }, kpResult[3]; //d)
    cout << scalarProduct(arr1, arr2, &dim) << endl;    //c)    
    outerProduct(kpArr1, kpArr2, kpResult); //d)
    for (int i = 0; i < 3; ++i)     //d)
    {
        cout << i << ": " <<kpResult[i] << endl;
    }
}