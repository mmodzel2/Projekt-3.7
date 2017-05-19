/*
* Name: console.hpp
* Purpose: Matrix and solving equations
* @author mmodzel2
* @version 1.1 18-05-2017
*/

#ifndef _CONSOLE_HPP
#define _CONSOLE_HPP

#include <iostream>
#include <cstring>

class Console;

typedef struct {
    char* instruction_;
    char* arg_;
    unsigned int arg_count_;
    unsigned int (*func_)(Console*, void** args);
    bool unlimited_;
} Instruction;

typedef struct {
    char* name_;
    void* pointer_;
} Variable;

class Console{
    private:
        Instruction** instructions_;
        Variable** variables_;

        unsigned int instructions_count_;
        unsigned int variables_count_;

        std::ostream* os_;

    public:
        Console(std::ostream &os);
        ~Console();

        void parse(const char* instruction);
        unsigned int register_instruction(unsigned int (*func)(Console*,void**), const char* instruction, unsigned int n, ...);
        unsigned int register_variable(const char* name, void* pointer);
        void* get_variable(const char* name);
        const char* get_variable(void* pointer);
        void remove_variable(const char* name);
        void remove_variable(void* pointer);

        std::ostream & get_stream();
};

#endif // _CONSOLE_HPP
