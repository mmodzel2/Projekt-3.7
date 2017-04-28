/*
* Name: equation.cpp
* Purpose: Matrix and solving equations
* @author mmodzel2
* @version 1.0 20-04-2017
*/

#include <assert.h>

#include "equation.hpp"

Matrix<double> equation_independent(Matrix<double> A, Matrix<double> B){
    Matrix<double> *I = A.inverse();
    if (I == nullptr) return A; //matrix is independent

    return ((*I)*B);
}

std::stringstream* equation(Matrix<double> A, Matrix<double> B){
    unsigned long i, j, k = 0, l = 0, p = 0;
    double *s, *x;
    char** minor;
    std::stringstream* str;
    unsigned long rank_AB;

    Matrix<double> *AB = new Matrix<double> (A);

    AB->expand(A.get_rows(),A.get_columns()+1); //expand matrix to A|B

    for (unsigned long i = 0; i < A.get_rows(); i++)
        AB->set(i, A.get_columns(), B.get(i,0));

    rank_AB = AB->rank(); //calculate rank of expanded matrix
    if (rank_AB == 0){ //matrix with zero coefficients
        str = new std::stringstream[B.get_rows()];

        for (i = 0; i < B.get_rows(); i++){
            str[i].str("");
            str[i] << "x" << i;
        }
        delete AB;
        return str;
    }

    if (rank_AB != A.rank()){ //Rouché–Capelli theorem
        delete AB;
        return nullptr;
    }
    delete AB;

    minor = A.get_minor(); //get minor in which solutions are independent

    if (minor != nullptr){
        for (i = 0; i < A.get_rows(); i++)
            if (minor[0][i] == 0) k++;
        Matrix<double> *m = new Matrix<double> (k,k); //create matrix with independent solutions
        for (i = 0; i < A.get_rows(); i++){
            if (minor[0][i] == 0){
                for (j = 0, p = 0; j < A.get_columns(); j++){
                        if (minor[1][j] == 0){
                            m->set(l,p,A.get(i,j));
                            p++;
                        }
                }
                l++;
            }
        }

        Matrix<double> *inv = m->inverse(); //inverse independent solution
        assert (inv != nullptr);

        delete m;

        k = A.get_columns() - k;

        s = new double [l*(k+1)];
        x = new double [l*(k+1)];

        for (i = 0, p = 0; i < A.get_rows(); i++)
            if (minor[0][i] == 0) {
                for (j = 0; j <= k; j++) x[p*(k+1)+j] = 0;
                s[p*(k+1)+k] = B.get(i,0);
                p++;
            }

        for (i = 0, l = 0; i < A.get_rows(); i++){
            if (minor[0][i] == 0){
                for (j = 0, p = 0; j < A.get_columns(); j++){
                     if (minor[1][j] == 1){
                           s[l*(k+1)+p] = (-1)*A.get(i,j);
                           p++;
                     }
                }
                l++;
            }
        }

        for (i = 0; i < inv->get_rows(); i++){
            for (j = 0; j < inv->get_columns(); j++){
                for (l = 0; l <= k; l++){
                    x[i*(k+1)+l] += inv->get(i,j)*s[j*(k+1)+l];
                }

            }
        }

        str = new std::stringstream[B.get_rows()];

        for (i = 0, l = 0; i < A.get_rows(); i++){
            if (minor[1][i] == 0){
                str[i].str(""); //clean stringstream
                //create solutions in stringstream
                for (j = 0, p = 0; j < A.get_columns(); j++){
                     if (minor[1][j] == 1){
                            if (x[l*(k+1)+p] != 0) str[i] << x[l*(k+1)+p] << "*x" << j << "+";
                            p++;
                     }
                     if (p == k){
                            if (x[l*(k+1)+p] != 0) str[i] << x[l*(k+1)+p];
                                else {
                                    if (str[i].str().empty()){ //if no values in stringstream add 0
                                        str[i] << 0;
                                    } else { //if zero on the end remove "+"
                                        str[i].seekp(-1,std::ios_base::end);
                                        str[i] << " ";
                                    }
                            }
                            break;
                        }
                }
                l++;
            } else {
                str[i] << "x" << i;
            }
        }

        delete inv;
        delete[] s;
        delete[] x;

        return str;
    }

    return nullptr;
}

//functions to use with console interface
unsigned int matrix_equation(Console* console, void** args){
    if (args[0] == nullptr || args[1] == nullptr){
        (console->get_stream()) << "Matrix with given name does not exist." << std::endl;
        return 1;
    }

    std::stringstream *sstream = equation(*((Matrix<double> *)args[0]), *((Matrix<double> *)args[1]));
    if (sstream != nullptr){
        for (unsigned long i = 0; i < ((Matrix<double> *)args[0])->get_columns(); i++) (console->get_stream()) << "x" << i << " = " << sstream[i].str() << std::endl;
    } else (console->get_stream()) << "No solution" << std::endl;

    return 0;
}
