/*
* Name: equation.cpp
* Purpose: Matrix and solving equations
* @author mmodzel2
* @version 1.2 1-05-2017
*/

#ifndef _EQUATION_HPP
#define _EQUATION_HPP

#include <string>
#include <sstream>

#include "console.hpp"
#include "matrix.hpp"

template <class type>
    Matrix<type> equation_independent(Matrix<type> A, Matrix<type> B){
        Matrix<double> *I = A.inverse();
        if (I == nullptr) return A; //matrix is independent

        return ((*I)*B);
    }

template <class type>
    std::stringstream* equation(Matrix<type> A, Matrix<type> B){
        unsigned long i, j, k = 0, l = 0, p = 0;
        type *s, *x;
        char** minor;
        std::stringstream* str;
        unsigned long rank_A, rank_AB;
        char* mn;
        char* mm;

        if (A.get_rows() > A.get_columns()) {
                A.expand(A.get_rows(),A.get_rows());
                //B.expand(A.get_rows(),1);
                return equation<type>(A,B);
        }

        Matrix<type> *AB = new Matrix<type> (A);

        AB->expand(A.get_rows(),A.get_columns()+1); //expand matrix to A|B

        for (unsigned long i = 0; i < A.get_rows(); i++)
            AB->set(i, A.get_columns(), B.get(i,0));

        std::cout << "RankAB..." << std::endl;
        rank_AB = AB->rank(); //calculate rank of expanded matrix
        std::cout << "rank_AB: " << rank_AB << std::endl;

        if (rank_AB == 0){ //matrix with zero coefficients
            str = new std::stringstream[B.get_rows()];

            for (i = 0; i < B.get_rows(); i++){
                str[i].str("");
                str[i] << "x" << i;
            }
            delete AB;
            return str;
        }

        //create object for function - blocks will be used for selecting rows and columns in matrix that won't be used in finding minor
        mn = new char[A.get_rows()];
        std::fill(mn, mn+A.get_rows()*sizeof(char), 0);

        mm = new char[A.get_columns()];
        std::fill(mm, mm+A.get_columns()*sizeof(char), 0);

        rank_A = A.rank(mn,mm);
        delete AB;

        if (rank_AB != rank_A){ //Rouch�Capelli theorem
            delete[] mn;
            delete[] mm;
            return nullptr;
        }

        std::cout << "RankA..." << rank_A << std::endl;
        std::cout << "Minor..." << std::endl;
        minor = A.get_minor(mn,mm,rank_A); //get minor in which solutions are independent
        std::cout << "Minor found..." << std::endl;

        if (minor != nullptr){
            for (i = 0; i < A.get_rows(); i++)
                if (minor[0][i] == 0) k++;

            Matrix<type> *m = new Matrix<type> (k,k); //create matrix with independent solutions
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

            std::cout << "Inverse..." << std::endl;
            Matrix<type> *inv = m->inverse(); //inverse independent solution
            assert (inv != nullptr);

                /* Show matrix - for test purpose */
                for (unsigned int i = 0; i < inv->get_rows(); i++){
                    for (unsigned int j = 0; j < inv->get_columns(); j++)
                        std::cout << inv->get(i,j) << " ";
                    std::cout << std::endl;
                }

            delete m;

            k = A.get_columns() - k;

            std::cout << "Calculating..." << std::endl;

            s = new type [l*(k+1)];
            x = new type [l*(k+1)];

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
                               s[l*(k+1)+p] = type(-1)*A.get(i,j);
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

            str = new std::stringstream[A.get_columns()];

            for (i = 0, l = 0; i < A.get_columns(); i++){
                if (minor[1][i] == 0){
                    str[i].str(""); //clean stringstream
                    //create solutions in stringstream
                    for (j = 0, p = 0; j < A.get_columns(); j++){
                         if (minor[1][j] == 1){
                                if (x[l*(k+1)+p] != type(0))
                                    str[i] << x[l*(k+1)+p] << "*x" << j << "+";
                                p++;
                         }
                         if (p == k){
                                if (x[l*(k+1)+p] != type(0)) str[i] << x[l*(k+1)+p];
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
                } else str[i] << "x" << i;
            }

            delete inv;
            delete[] s;
            delete[] x;

            delete[] mn;
            delete[] mm;
            delete[] minor;

            return str;
        }

        return nullptr;
    }

Matrix<double> equation_independent(Matrix<double> A, Matrix<double> B);
std::stringstream* equation(Matrix<double> A, Matrix<double> B);

unsigned int matrix_equation(Console* console, void** args);



#endif // _EQUATION_HPP
