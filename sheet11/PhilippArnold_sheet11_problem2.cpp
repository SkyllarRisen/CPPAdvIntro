#include <armadillo>
#include <iostream>


int main()
{
    
    arma::Mat<double> A(30, 30);                                                            //initializes matrix A
    arma::Col<double> b(30);                                                                //initializes vector b

    A.randn();                                                                              //fills both with random elements
    b.randn();
    // a)
    std::cout << "det(A) = " << arma::det(A) << std::endl;                                  //calculates determinant of matrix A
    std::cout << "tr(A) = " << arma::trace(A) << std::endl;                                 //calculates trace of matrix A

    // b)                                                                   
    std::cout << "|b| = " << arma::norm(b) << std::endl;                                    //calculates modulus of vector b

    // c) 
    arma::Col<double> X = arma::solve(A, b);                                                //solves equation
    std::cout << "|b-A*x| = " << arma::norm(b - A * X) << std::endl;                        //validates solution
}