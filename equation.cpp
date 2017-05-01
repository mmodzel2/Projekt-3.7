/*
* Name: equation.cpp
* Purpose: Matrix and solving equations
* @author mmodzel2
* @version 1.2 1-05-2017
*/

#include <assert.h>

#include "equation.hpp"

//functions to use with console interface
unsigned int matrix_equation(Console* console, void** args){
    if (args[0] == nullptr || args[1] == nullptr){
        (console->get_stream()) << "Matrix with given name does not exist." << std::endl;
        return 1;
    }

    std::stringstream *sstream = equation<double>(*((Matrix<double> *)args[0]), *((Matrix<double> *)args[1]));

    if (sstream != nullptr){
        for (unsigned long i = 0; i < ((Matrix<double> *)args[0])->get_columns(); i++) (console->get_stream()) << "x" << i << " = " << sstream[i].str() << std::endl;
    } else (console->get_stream()) << "No solution" << std::endl;

    return 0;
}


