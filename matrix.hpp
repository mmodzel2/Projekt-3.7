/*
* Name: matrix.hpp
* Purpose: Matrix and solving equations
* @author mmodzel2
* @version 1.2 18-05-2017
*/

#ifndef _MATRIX_HPP
#define _MATRIX_HPP

#include "console.hpp"

#include <algorithm>
#include <iostream>

template <class type>
    class Matrix{
        private:
            type* coefficients_;
            unsigned long rows_;
            unsigned long columns_;
        public:
            Matrix();
            Matrix(unsigned long rows, unsigned long columns);
            Matrix(Matrix<type> &M);
            ~Matrix();

            Matrix(const Matrix<type> &M);
            unsigned long get_rows() const;
            unsigned long get_columns() const;

            int set(unsigned long row, unsigned long column, type value);
            type get(unsigned long row, unsigned long column) const;

            void expand(unsigned long rows, unsigned long columns);

            Matrix<type> operator+(const Matrix<type> &m) const;
            Matrix<type> &operator+=(const Matrix<type> &m);
            Matrix<type> operator-(const Matrix<type> &m) const;
            Matrix<type> &operator-=(const Matrix<type> &m);
            Matrix<type> operator*(const Matrix<type> &m) const;
            Matrix<type> &operator*=(const Matrix<type> &m);

            type det(char* n = nullptr, char* m = nullptr) const;
            unsigned long rank(char* n = nullptr, char* m = nullptr) const;

            Matrix<type>* adjugate() const;
            Matrix<type>* inverse() const;
            Matrix<type>* transpose() const;

            double* characteristic() const;

            char** get_minor(char* n = nullptr, char* m = nullptr, unsigned long matrix_ranks = 0) const;

            //functions for console interface
            static unsigned int Create_Matrix(Console* console, void** args);
            static unsigned int Add_Matrix(Console* console, void** args);
            static unsigned int Mul_Matrix(Console* console, void** args);
            static unsigned int Det_Matrix(Console* console, void** args);
            static unsigned int Rank_Matrix(Console* console, void** args);
            static unsigned int Look_Matrix(Console* console, void** args);
            static unsigned int Characteristic_Matrix(Console* console, void** args);
            static unsigned int Get_Matrix(Console* console, void** args);
            static unsigned int Set_Matrix(Console* console, void** args);
            static unsigned int Delete_Matrix(Console* console, void** args);
    };

template <class type>
    Matrix <type>::Matrix(){
            rows_ = 0;
            columns_ = 0;
            coefficients_ = nullptr;

    }
template <class type>
    Matrix<type>::Matrix(Matrix <type> &M){
            rows_ = M.get_rows();
            columns_ = M.get_columns();

            if (rows_ != 0 && columns_ != 0){ //copy context of second matrix
                    coefficients_ = new type[rows_*columns_];
                    for (unsigned long i = 0; i < rows_; i++){
                        for (unsigned long j = 0; j < columns_; j++){
                            coefficients_[(i*columns_)+j] = M.get(i,j); //copy coefficeint from second matrix
                        }
                    }
            }
    }
template <class type>
    Matrix<type>::Matrix(const Matrix<type> &M){
            rows_ = M.get_rows();
            columns_ = M.get_columns();

            if (rows_ != 0 && columns_ != 0){ //copy context of second matrix
                    coefficients_ = new type[rows_*columns_];
                    for (unsigned long i = 0; i < rows_; i++){
                        for (unsigned long j = 0; j < columns_; j++){
                            coefficients_[(i*columns_)+j] = M.get(i,j); //copy coefficeint from second matrix
                        }
                    }
            }
    }
template <class type>
    Matrix <type>::Matrix(unsigned long rows, unsigned long columns){
        rows_ = rows;
        columns_ = columns;
        if (rows == 0 || columns == 0) //null matrix
            coefficients_ = nullptr;
        else {
            coefficients_ = new type[rows*columns];

            for (unsigned long i = 0; i < rows; i++){
                for (unsigned long j = 0; j < columns; j++){
                    coefficients_[i*columns+j] = type(0);
                }
            }
        }
    }
template <class type>
    Matrix <type>::~Matrix(){
        if (coefficients_ != nullptr) delete[] coefficients_;
    }

template <class type>
    unsigned long Matrix<type>::get_rows() const{
        return rows_;
    }

template <class type>
    unsigned long Matrix<type>::get_columns() const{
        return columns_;
    }

template <class type>
    int Matrix<type>::set(unsigned long row, unsigned long column, type value){
        if (row >= rows_ || column >= columns_) return 1; //setting value beyond matrix
        coefficients_[row*columns_+column] = value;
        return 0;
    }

template <class type>
    void Matrix <type>::expand(unsigned long rows, unsigned long columns){
        type* pointer;
        unsigned long k,l;

        if (rows == rows_ && columns == columns_) return; //matrix is the same size
        else if (rows == 0 || columns == 0){ //matrix has to be null
            if (coefficients_ != nullptr) delete[] coefficients_;
            rows_ = rows;
            columns_ = columns;
        } else { //matrix has to be expanded
            pointer = new type[rows*columns];
            for (unsigned long i = 0; i < rows; i++){
                for (unsigned long j = 0; j < columns; j++){
                    pointer[i*columns+j] = type(0); //zero matrix
                }
            }

            if (rows_ <= rows) k = rows_;
            else k = rows;
            if (columns_ <= columns) l = columns_;
            else l = columns;

            for (unsigned long i = 0; i < k; i++){
                for (unsigned long j = 0; j < l; j++){
                    pointer[i*columns+j] = coefficients_[i*columns_+j]; //copy coefficients from previous matrix
                }
            }

            delete[] coefficients_;
            coefficients_ = pointer;
            rows_ = rows;
            columns_ = columns;
        }
    }

template <class type>
    type Matrix<type>::get(unsigned long row, unsigned long column) const{
        if (row >= rows_ || column >= columns_) return type(0); //getting value beyond matrix
        return coefficients_[(row*columns_)+column];
    }

template <class type>
    Matrix<type> Matrix<type>::operator+(const Matrix<type> &m) const{
        Matrix<type> *temp = new Matrix <type> (this->rows_, this->columns_);
        if (this->rows_ == m.get_rows() && this->columns_ == m.get_columns()){ //check if matrixes are the same size
            for (unsigned long i = 0; i < this->rows_; i++){
                for (unsigned long j = 0; j < this->columns_; j++){
                    temp->set(i, j, this->get(i,j)+m.get(i,j));
                }
            }
        }
        return *temp;
    }

template <class type>
    Matrix<type> &Matrix<type>::operator+=(const Matrix<type> &m){
        if (this->rows_ == m.get_rows() && this->columns_ == m.get_columns()){ //check if matrixes are the same size
            for (unsigned long i = 0; i < this->rows_; i++){
                for (unsigned long j = 0; j < this->columns_; j++){
                    this->set(i, j, this->get(i,j)+m.get(i,j));
                }
            }
        }
        return *this;
    }

template <class type>
    Matrix<type> Matrix<type>::operator-(const Matrix<type> &m) const{
        Matrix<type> *temp = new Matrix <type> (this->rows_, this->columns_);
        if (this->rows_ == m.get_rows() && this->columns_ == m.get_columns()){ //check if matrixes are the same size
            for (unsigned long i = 0; i < this->rows_; i++){
                for (unsigned long j = 0; j < this->columns_; j++){
                    temp->set(i, j, this->get(i,j)-m.get(i,j));
                }
            }
        }
        return *temp;
    }

template <class type>
    Matrix<type> &Matrix<type>::operator-=(const Matrix<type> &m){
        if (this->rows_ == m.get_rows() && this->columns_ == m.get_columns()){ //check if matrixes are the same size
            for (unsigned long i = 0; i < this->rows_; i++){
                for (unsigned long j = 0; j < this->columns_; j++){
                    this->set(i, j, this->get(i,j)-m.get(i,j));
                }
            }
        }
        return *this;
    }

template <class type>
    Matrix<type> Matrix<type>::operator*(const Matrix<type> &m) const{
        Matrix<type> *temp;
        if (this->columns_ != m.get_rows()) { //check size of rows and columns in both matrixes
                temp = new Matrix<type>;
                return *temp; //mul is not possible
        } else {
            type sum;
            temp = new Matrix <type> (this->rows_, this->columns_);
            for (unsigned long i = 0; i < this->rows_; i++){
                for (unsigned long j = 0; j < m.get_columns(); j++){
                    sum = type(0);
                    for (unsigned long k = 0; k < this->columns_; k++){
                        sum += (this->get(i,k)*m.get(k,j)); //count new coefficient
                    }
                    temp->set(i, j, sum);
                }
            }
            return *temp;
        }
    }

template <class type>
    Matrix<type> &Matrix<type>::operator*=(const Matrix<type> &m){
        type sum;
        if (this->columns_ == m.get_rows()) {
            Matrix<type> *temp = new Matrix <type> (*this); //create temporary matrix
            this->expand(this->rows_, m.get_columns()); //change size to appropriate
            for (unsigned long i = 0; i < temp->get_rows(); i++){
                for (unsigned long j = 0; j < m.get_columns(); j++){
                    sum = type(0);
                    for (unsigned long k = 0; k < temp->get_columns(); k++){
                        sum += (temp->get(i,k)*m.get(k,j)); //count new coefficient
                    }
                    this->set(i, j, sum);
                }
            }
            delete temp;
        }
            return *this;
    }

template <class type>
    type Matrix<type>::det(char* n, char* m) const{
        type determination = 0;
        unsigned long j = 0, g = 0, k[3][2] = {{0,0},{0,0},{0,0}};

        if (coefficients_ == nullptr) return 0;
        if (rows_ != columns_){ //matrix is not nxn
               if (n == nullptr || m == nullptr) return 0;
               for (unsigned long i = 0; i < rows_; i++)
                    if (n[i] == 0) j++;
               for (unsigned long i = 0; i < columns_; i++)
                    if (m[i] == 0) g++;
               if (j != g) return 0; //matrix with wrong size for calculate of determination
               j = 0;
               g = 0;
        }
        bool flag1 = 0, flag2 = 0;

        if (n == nullptr){ //create object to use in function
            n = new char[rows_];
            std::fill(n, n+rows_*sizeof(char), 0);
            flag1 = 1;
            }
        if (m == nullptr){
            m = new char[columns_];
            std::fill(m, m+columns_*sizeof(char), 0);
            flag2 = 1;
            }

        if (rows_ == columns_){
            for (unsigned long i = 0; i < rows_; i++){ //get first coefficients
                if (n[i] == 0){
                    if (j < 3) k[j][0] = i;
                    j++;
                }
                if (m[i] == 0){
                    if (g < 3) k[g][1] = i;
                    g++;
                }
            }
        } else {
            for (unsigned long i = 0; i < rows_; i++){ //get first coefficients
                if (n[i] == 0){
                    if (j < 3) k[j][0] = i;
                    j++;
                }
            }
            for (unsigned long i = 0; i < columns_; i++){
                if (m[i] == 0){
                    if (g < 3) k[g][1] = i;
                    g++;
                }
            }
        }

        if (j == 3){ //matrix 3x3 detected
            determination = coefficients_[(k[0][0]*columns_)+k[0][1]]*coefficients_[(k[1][0]*columns_)+k[1][1]]*coefficients_[(k[2][0]*columns_)+k[2][1]]+
            coefficients_[(k[1][0]*columns_)+k[0][1]]*coefficients_[(k[2][0]*columns_)+k[1][1]]*coefficients_[(k[0][0]*columns_)+k[2][1]]+
            coefficients_[(k[2][0]*columns_)+k[0][1]]*coefficients_[(k[0][0]*columns_)+k[1][1]]*coefficients_[(k[1][0]*columns_)+k[2][1]]-
            (coefficients_[(k[0][0]*columns_)+k[2][1]]*coefficients_[(k[1][0]*columns_)+k[1][1]]*coefficients_[(k[2][0]*columns_)+k[0][1]]+
            coefficients_[(k[1][0]*columns_)+k[2][1]]*coefficients_[(k[2][0]*columns_)+k[1][1]]*coefficients_[(k[0][0]*columns_)+k[0][1]]+
            coefficients_[(k[2][0]*columns_)+k[2][1]]*coefficients_[(k[0][0]*columns_)+k[1][1]]*coefficients_[(k[1][0]*columns_)+k[0][1]]);
        } else if (j == 2){ //matrix 2x2 detected
            determination = coefficients_[(k[0][0]*columns_)+k[0][1]]*coefficients_[(k[1][0]*columns_)+k[1][1]]-(coefficients_[(k[0][0]*columns_)+k[1][1]]*coefficients_[(k[1][0]*columns_)+k[0][1]]);
        } else if (j == 1) { //matrix 1x1 detected
            determination = coefficients_[(k[0][0]*columns_)+k[0][1]];
        } else { //matrix is bigger - use Laplace expansion
            g = 0;
            n[k[0][0]] = 1;
            for (unsigned long i = 0; i < columns_; i++)
                if (m[i] == 0) {
                    if (coefficients_[(k[0][0]*columns_)+i] == type(0)){
                        g++;
                        continue;
                    }

                    m[i] = 1;
                    if ((g%2)==1) determination-=coefficients_[(k[0][0]*columns_)+i]*det(n,m);
                    else determination+=coefficients_[(k[0][0]*columns_)+i]*det(n,m);
                    m[i] = 0;
                    g++;
                }
            n[k[0][0]] = 0;
        }

        if (flag1 == 1) delete[] n;
        if (flag2 == 1) delete[] m;
        return determination;
    }

template <class type>
    Matrix<type>* Matrix<type>::adjugate() const{
        char *n, *m;
        long int determination;
        if (coefficients_ == nullptr) return nullptr;
        if (rows_ != columns_ || rows_ == 0) return nullptr;

        n = new char[rows_];
        std::fill(n, n+rows_*sizeof(char), 0);

        m = new char[columns_];
        std::fill(m, m+columns_*sizeof(char), 0);

        Matrix<type> *matrix = new Matrix<type> (this->rows_, this->columns_);

        for (unsigned long i = 0; i < rows_; i++){
            n[i] = 1;
            for (unsigned long j = 0; j < columns_; j++){
                m[j] = 1;
                //count minor
                if ((i+j)%2 == 1) determination = (-1)*this->det(n,m);
                else determination = this->det(n,m);
                matrix->set(j,i, determination);
                m[j] = 0;
            }
            n[i] = 0;
        }

        delete[] n;
        delete[] m;
        return matrix;
    }

template <class type>
    Matrix<type>* Matrix<type>::inverse() const{
        char *n, *m;
        type determination, div;
        if (coefficients_ == nullptr) return nullptr;
        if (rows_ != columns_ || rows_ == 0) return nullptr;

        div = this->det();
        if (div == type(0)) return nullptr; //inverse matrix does not exist

        if (rows_ == 1){
            Matrix<type> *matrix = new Matrix<type> (this->rows_, this->columns_);
            matrix->set(0,0,this->get(0,0)/div);
            return matrix;
        }

        n = new char[rows_];
        std::fill(n, n+rows_*sizeof(char), 0);

        m = new char[columns_];
        std::fill(m, m+columns_*sizeof(char), 0);

        Matrix<type> *matrix = new Matrix<type> (this->rows_, this->columns_);

        for (unsigned long i = 0; i < rows_; i++){
            n[i] = 1;
            for (unsigned long j = 0; j < columns_; j++){
                m[j] = 1;
                //count determination of minor
                if ((i+j)%2 == 1) determination = type(-1)*this->det(n,m);
                else determination = this->det(n,m);
                matrix->set(j,i, determination/div); //set transposed value in invered matrix
                m[j] = 0;
            }
            n[i] = 0;
        }

        delete[] n;
        delete[] m;
        return matrix;
    }

template <class type>
    Matrix<type>* Matrix<type>::transpose() const{
        if (coefficients_ == nullptr) return nullptr;

        Matrix<type> *matrix = new Matrix<type> (columns_, rows_);

        for (unsigned long i = 0; i < rows_; i++)
            for (unsigned long j = 0; j < columns_; j++)
                matrix->set(j,i,this->coefficients_[(i*this->columns_)+j]); //copy coefficient to transposed matrix
        return matrix;
    }

template <class type>
    double* Matrix<type>::characteristic() const{ //Faddeev–LeVerrier algorithm
        if (coefficients_ == nullptr) return nullptr;
        if (rows_ != columns_ || rows_ == 0) return nullptr;

        double* a = new double[rows_+1];
        type* tr = new type[rows_]; //trace of matrix

        Matrix<type> *matrix = new Matrix<type> (this->columns_, this->rows_);

        for (unsigned long i = 0; i < rows_; i++){
            a[i] = type(0);
            tr[i] = type(0);

            for (unsigned long j = 0; j < columns_; j++)
                matrix->set(i,j,coefficients_[(i*columns_)+j]);
        }

        a[rows_] = 1;

        for (unsigned long i = 0; i < rows_; i++){
            for (unsigned long j = 0; j < rows_; j++){
                tr[i] += matrix->get(j,j);
            }
            if (i != rows_-1) (*matrix)*=(*this);
        }

        for (unsigned long i = 1; i <= this->rows_; i++){
              for (unsigned long j = 0; j < i; j++){
                    a[rows_-i] += a[rows_-j]*tr[i-j-1];
              }
              a[rows_-i] = ((double)((-1.0)*a[rows_-i]))/(double)i;
        }

        if((rows_%2) == 1)
                for (unsigned long i = 0; i <= rows_; i++) a[i] *= -1;

        delete matrix;
        return a;
    }

template <class type>
    unsigned long Matrix<type>::rank(char* n, char* m) const{
        bool flag1 = 0, flag2 = 0;
        unsigned long k = 0, l = 0;
        unsigned long ranks = 0, temp_ranks;

        if (coefficients_ == nullptr) return 0;

        if (n == nullptr){ //create object for function - blocks will be used for selecting rows and columns in matrix that won't be used in calculation
            n = new char[rows_];
            std::fill(n, n+rows_*sizeof(char), 0);
            flag1 = 1;
            }
        if (m == nullptr){
            m = new char[columns_];
            std::fill(m, m+columns_*sizeof(char), 0);
            flag2 = 1;
            }

        for (unsigned long i = 0; i < rows_; i++)
            if (n[i] == 1) k++; //calculate deleted rows

        if (rows_ != columns_){ //check if matrix is not nxn
            for (unsigned long i = 0; i < columns_; i++)
                if (m[i] == 1) l++; //calculate deleted columns

            if (rows_-k != columns_-l){ //matrix has to be divided
                if (rows_ > columns_){
                    for (unsigned long i = 0; i < rows_; i++) //choose row to remove
                        if (n[i] == 0){
                            n[i] = 1;
                            temp_ranks = this->rank(n,m);
                            if (temp_ranks > ranks) ranks = temp_ranks;
                            if (ranks == columns_) break;
                            n[i] = 0;
                        }

                } else { // k < l
                    for (unsigned long i = 0; i < columns_; i++) //choose columns to remove
                        if (m[i] == 0){
                            m[i] = 1;
                            temp_ranks = this->rank(n,m);
                            if (temp_ranks > ranks) ranks = temp_ranks;
                            if (ranks == rows_) break;
                            m[i] = 0;
                        }
                }
                if (flag1 == 1) delete[] n;
                if (flag2 == 1) delete[] m;
                return ranks;
            }
        } else l = k;

        if (det(n,m) != type(0)){ //found minor
                if (rows_ >= columns_) ranks = rows_-k;
                else ranks = columns_-l;
        } else if (rows_ == k || columns_ == l) ranks = 0;
        else {
            for (unsigned long i = 0; i < rows_; i++){
                if (n[i] == 0){
                    n[i] = 1;
                    for (unsigned long j = 0; j < columns_; j++){
                        if (m[j] == 0){
                            m[j] = 1;
                            temp_ranks = rank(n,m);
                            if (temp_ranks > ranks) ranks = temp_ranks;
                            m[j] = 0;
                            if (rows_ >= columns_) {
                                if (ranks == rows_-k-1) break;
                            } else {
                                if (ranks == columns_-l-1) break;
                            }
                        }
                    }
                    n[i] = 0;
                    if (rows_ >= columns_) {
                        if (ranks == rows_-k-1) break;
                    } else {
                        if (ranks == columns_-l-1) break;
                    }
                }
            }
        }

        if (flag1 == 1) delete[] n;
        if (flag2 == 1) delete[] m;
        return ranks;
    }

template <class type>
    char** Matrix<type>::get_minor(char* n, char* m, unsigned long matrix_ranks) const{
        unsigned long k = 0, l = 0;
        char** ret = nullptr;
        char** temp;

        if (coefficients_ == nullptr) return ret;

        if (n == nullptr){ //create object for function - blocks will be used for selecting rows and columns in matrix that won't be used in finding minor
            n = new char[rows_];
            std::fill(n, n+rows_*sizeof(char), 0);
            }
        if (m == nullptr){
            m = new char[columns_];
            std::fill(m, m+columns_*sizeof(char), 0);
            }

        if (matrix_ranks == 0){
            matrix_ranks = rank(n,m);
            if (matrix_ranks == 0) {
                delete[] n;
                delete[] m;
                return nullptr;
            }
        }

        for (unsigned long i = 0; i < rows_; i++)
            if (n[i] == 1) k++;

        if (rows_ != columns_){ //check if matrix is not nxn
            for (unsigned long i = 0; i < columns_; i++)
                if (m[i] == 1) l++; //calculate deleted columns
        } else l = k;

        if (det(n,m) != type(0)) {
            ret = new char* [2];
            ret[0] = n;
            ret[1] = m;
        } else if (matrix_ranks >= rows_-k || matrix_ranks >= columns_-l) ret = nullptr;
        else {
            for (unsigned long i = 0; i < rows_; i++){
                if (n[i] == 0){
                    n[i] = 1;
                    for (unsigned long j = 0; j < columns_; j++){
                        if (m[j] == 0){
                            m[j] = 1;
                            temp = get_minor(n,m,matrix_ranks);
                            if (temp != nullptr) {
                                    ret = temp;
                                    break;
                            }
                            m[j] = 0;
                        }
                    }
                    if (temp != nullptr) break;
                    n[i] = 0;
                }
            }
        }
        return ret;
    }

//functions for use with console interface
template <class type>
    unsigned int Matrix<type>::Create_Matrix(Console* console, void** args){
        if (args[0] == nullptr || args[1] == nullptr || args[2] == nullptr || args[3] == nullptr) return 1;
        if (*((unsigned int*)(args[1])) == 0){
            (console->get_stream()) << "Bad matrix parameters. Cannot create new matrix." << std::endl;
            return 1;
        }
        if (*((unsigned int*)(args[2])) == 0){
            (console->get_stream()) << "Bad matrix parameters. Cannot create new matrix." << std::endl;
            return 1;
        }
        if (*((unsigned int*)(args[1]))*(*((unsigned int*)(args[2]))) != *((unsigned int*)(args[3]))){
            (console->get_stream()) << "Bad matrix parameters. Cannot create new matrix." << std::endl;
            return 1;
        }

        Matrix<type> *m = new Matrix<type>(*((unsigned int*)(args[1])),*((unsigned int*)(args[2])));
        unsigned int ret = console->register_variable((const char *)args[0], m);
        if (ret == 1 || m == nullptr){
            if (m != nullptr) delete m;
            (console->get_stream()) << "Lack of free memory. Matrix cannot be created." << std::endl;
            return 2;
        } else if (ret == 3) {
            delete m;
            (console->get_stream()) << "Variable name reserved. Cannot create matrix with given variable name." << std::endl;
            return 1;
        }

        unsigned long k = 0;
        for (unsigned long i = 0; i < *((unsigned int*)(args[1])); i++){
            for (unsigned long j = 0; j < *((unsigned int*)(args[2])); j++){
                m->set(i,j,*((double*)(args[4+k])));
                k++;
            }
        }

        (console->get_stream()) << "Matrix has been created." << std::endl;
        return 0;
    }

template <class type>
    unsigned int Matrix<type>::Add_Matrix(Console* console, void** args){
        if (args[0] == nullptr || args[1] == nullptr){
                (console->get_stream()) << "Matrix with given name does not exist." << std::endl;
                return 1;
        }

        Matrix<type> *m = (Matrix<type> *)args[0];
        Matrix<type> *n = (Matrix<type> *)args[1];

        if (m->get_columns() != n->get_columns() || m->get_rows() != n->get_rows()){
            (console->get_stream()) << "Matrix with wrong size." << std::endl;
            return 1;
        }
        (*m)+=(*n);

        return 0;
    }

template <class type>
    unsigned int Matrix<type>::Mul_Matrix(Console* console, void** args){
        if (args[0] == nullptr || args[1] == nullptr){
                (console->get_stream()) << "Matrix with given name does not exist." << std::endl;
                return 1;
        }

        Matrix<type> *m = (Matrix<type> *)args[0];
        Matrix<type> *n = (Matrix<type> *)args[1];

        if (n->get_rows() != m->get_columns()){
            (console->get_stream()) << "Matrix with wrong size." << std::endl;
            return 1;
        }
        (*m)*=(*n);

        return 0;
    }

template <class type>
    unsigned int Matrix<type>::Det_Matrix(Console* console, void** args){
        if (args[0] == nullptr){
                (console->get_stream()) << "Matrix with given name does not exist." << std::endl;
                return 1;
        }

        (console->get_stream()) << "Det: " << ((Matrix<type> *)args[0])->det() << std::endl;

        return 0;
    }

template <class type>
    unsigned int Matrix<type>::Rank_Matrix(Console* console, void** args){
        if (args[0] == nullptr){
                (console->get_stream()) << "Matrix with given name does not exist." << std::endl;
                return 1;
        }

        (console->get_stream()) << "Rank: " << ((Matrix<type> *)args[0])->rank() << std::endl;

        return 0;
    }

template <class type>
    unsigned int Matrix<type>::Look_Matrix(Console* console, void** args){
        if (args[0] == nullptr){
                (console->get_stream()) << "Matrix with given name does not exist." << std::endl;
                return 1;
        }

        Matrix<type> *m = (Matrix<type> *)args[0];
        for (unsigned long i = 0; i < m->get_rows(); i++){
            for (unsigned long j = 0; j < m->get_columns(); j++){
                (console->get_stream()) << m->get(i,j) << " ";
            }
            (console->get_stream()) << std::endl;
        }

        return 0;
    }

template <class type>
    unsigned int Matrix<type>::Characteristic_Matrix(Console* console, void** args){
        unsigned long i = 0;
        if (args[0] == nullptr){
                (console->get_stream()) << "Matrix with given name does not exist." << std::endl;
                return 1;
        }

        double* c = ((Matrix<type> *)args[0])->characteristic();
        if (c == nullptr){
            (console->get_stream()) << "Matrix is not nxn." << std::endl;
            return 1;
        }
        if (((Matrix<type> *)args[0])->get_rows() != 1){
            for (i = 0; i < ((Matrix<type> *)args[0])->get_rows()-2; i++){
                (console->get_stream()) << c[i] << "x^" << i << "+";
            }
        }
        (console->get_stream()) << c[i++] << "x" << "+";
        (console->get_stream()) << c[i] << std::endl;

        return 0;
    }

template <class type>
    unsigned int Matrix<type>::Get_Matrix(Console* console, void** args){
        if (args[0] == nullptr){
                (console->get_stream()) << "Matrix with given name does not exist." << std::endl;
                return 1;
        }

        (console->get_stream()) << ((Matrix<type> *)args[0])->get(*((unsigned long*)args[1]),*((unsigned long*)args[1])) << std::endl;

        return 0;
    }

template <class type>
    unsigned int Matrix<type>::Set_Matrix(Console* console, void** args){
        if (args[0] == nullptr){
                (console->get_stream()) << "Matrix with given name does not exist." << std::endl;
                return 1;
        }

        ((Matrix<type> *)args[0])->set(*((unsigned long*)args[1]),*((unsigned long*)args[1]),*((double*)args[2]));

        return 0;
    }

template <class type>
    unsigned int Matrix<type>::Delete_Matrix(Console* console, void** args){
        if (args[0] == nullptr){
                (console->get_stream()) << "Matrix with given name does not exist." << std::endl;
                return 1;
        }

        console->remove_variable(args[0]);
        delete ((Matrix<type> *)args[0]);

        (console->get_stream()) << "Matrix removed." << std::endl;

        return 0;
    }



#endif
