#include <armadillo>
#include <iostream>

int main()
{
    arma::Mat<double> A(3, 3);                                                                      //initializes needed vectors and matrix
    arma::Col<double> x(3);
    arma::Col<double> b(3);
    A << -5 << -4 << 2 << arma::endr << -2 << -2 << 2 << arma::endr << 4 << 2 << 2 << arma::endr;
    x(0) = 1;
    x(1) = -1;
    x(2) = 4;
    b(0) = 7;
    b(1) = 8;
    b(2) = 10;

    //a)
    arma::Col<double> b2 = A*x;                                                                     
    b.print();                                                                                      //b=b2?
    b2.print();                                                                                     //true

    //b)
    A(0, 0) = -5.001;                                                                               //changes first element of A
    arma::Col<double> b3 = A*x;                                                                     //new result vector b3
    b3.print();

    //c)
    b3(0) = b3(0)*1.01;                                                                             //adds 1% to first entry of b3
    b3.print();
    arma::Col<double> x2 = solve(A, b3);                                                            //solves linear equations for new solution vector x2
    x2.print();
}