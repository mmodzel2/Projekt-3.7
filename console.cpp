/*
* Name: console.cpp
* Purpose: Console command interface
* @author mmodzel2
* @version 1.0 20-04-2017
*/

#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>

#include "console.hpp"

using namespace std;

Console::Console(std::ostream &os){
    this->instructions_ = nullptr;
    this->variables_ = nullptr;

    this->instructions_count_ = 0;
    this->variables_count_ = 0;

    this->os_ = &os;
}

Console::~Console(){
    for (unsigned int i = 0; i < this->instructions_count_; i++){
        delete[] this->instructions_[i]->instruction_;
        if (this->instructions_[i]->arg_count_ != 0) delete this->instructions_[i]->arg_;
        delete this->instructions_[i];
    }

    for (unsigned int i = 0; i < this->variables_count_; i++){
        delete[] this->variables_[i]->name_;
        delete this->variables_[i];
    }

    delete[] this->instructions_;
    delete[] this->variables_;
}

void Console::parse(const char* instruction){
    unsigned int length, arg_c = 0, n = 0;
    char* instr;
    char* args_char;
    short* args_short;
    int* args_int;
    long int* args_long;
    unsigned char* args_uchar;
    unsigned short* args_ushort;
    unsigned int* args_uint;
    unsigned long int* args_ulong;
    float* args_float;
    double* args_double;

    unsigned int args_char_count = 0;
    unsigned int args_short_count = 0;
    unsigned int args_int_count = 0;
    unsigned int args_long_count = 0;
    unsigned int args_uchar_count = 0;
    unsigned int args_ushort_count = 0;
    unsigned int args_uint_count = 0;
    unsigned int args_ulong_count = 0;
    unsigned int args_float_count = 0;
    unsigned int args_double_count = 0;

    void** args = nullptr;
    unsigned int args_c = 0;

    length = strlen(instruction);
    if (length == 0){
        (this->get_stream()) << "Wrong instruction." << endl;
        return;
    }

    instr = new char[length+1];
    if (instr == nullptr) {
        (this->get_stream()) << "Out of memory. Free memory to parse instruction." << endl;
        return; //lack of memory - error
    }

    instr[length] = 0;

    strcpy(instr, instruction);

    for (unsigned int i = 0; i < length; i++)
        if (instr[i] == ' ') {
            arg_c++;
            instr[i] = 0;
            if (instr[i+1] == '\"' || instr[i+1] == '\''){
                i++;
                instr[i] = 0;
                while (1){
                    if (instr[i] == '\"' || instr[i] == '\''){
                        if (instr[i+1] == 0 || instr[i+1] == ' ') break;
                        else {
                            (this->get_stream()) << "Bad instruction." << endl;
                            return;
                        }
                    }
                    i++;
                    if (i >= length) {
                            (this->get_stream()) << "Bad instruction." << endl;
                            return;
                    }
                }
                instr[i] = 0;
            }
        }

    if (arg_c != 0){
        args_char = new char[arg_c];
        args_short = new short[arg_c];
        args_int = new int[arg_c];
        args_long = new long int[arg_c];
        args_uchar = new unsigned char[arg_c];
        args_ushort = new unsigned short[arg_c];
        args_uint = new unsigned int[arg_c];
        args_ulong = new unsigned long int[arg_c];
        args_float = new float[arg_c];
        args_double = new double[arg_c];

        args = new void*[arg_c+1];

        if (args_char == nullptr || args_short == nullptr || args_int == nullptr || args_long == nullptr || args_uchar == nullptr || \
            args_ushort == nullptr || args_uint == nullptr || args_ulong == nullptr || args_float == nullptr || args_double == nullptr || args == nullptr) {
                (this->get_stream()) << "Out of memory. Free memory to parse instruction." << endl;
                return; //lack of memory - error
        }

        for (unsigned int i = 0; i < arg_c; i++) args[i] = nullptr;
    }

    for (unsigned int i = 0; i < this->instructions_count_; i++){
        if (strcmp(this->instructions_[i]->instruction_, instr) == 0){
            if (arg_c == this->instructions_[i]->arg_count_ || this->instructions_[i]->unlimited_ == 1){
                if (arg_c == 0){
                    this->instructions_[i]->func_(this, args);

                    delete[] instr;
                    return;
                } else {
                    while(1){
                        while(*(char *)(instr+n) != 0 && (n < length)) n++;

                        n++;
                        if (*(char *)(instr+n) == 0) n++;
                        if (n >= length) break;

                        if (this->instructions_[i]->arg_[args_c] == 0){
                            sscanf((char *)(instr+n), "%c", &args_char[args_char_count]);
                            args[args_c++] = &args_char[args_char_count++];
                        } else if (this->instructions_[i]->arg_[args_c] == 1){
                            sscanf((char *)(instr+n), "%hd", &args_short[args_short_count]);
                            args[args_c++] = &args_short[args_short_count++];
                        } else if (this->instructions_[i]->arg_[args_c] == 2){
                            sscanf((char *)(instr+n), "%d", &args_int[args_int_count]);
                            args[args_c++] = &args_int[args_int_count++];
                        } else if (this->instructions_[i]->arg_[args_c] == 3){
                            sscanf((char *)(instr+n), "%ld", &args_long[args_long_count]);
                            args[args_c++] = &args_long[args_long_count++];
                        } else if (this->instructions_[i]->arg_[args_c] == 4){
                            sscanf((char *)(instr+n), "%c", &args_uchar[args_uchar_count]);
                            args[args_c++] = &args_uchar[args_uchar_count++];
                        } else if (this->instructions_[i]->arg_[args_c] == 5){
                            sscanf((char *)(instr+n), "%hu", &args_ushort[args_ushort_count]);
                            args[args_c++] = &args_ushort[args_ushort_count++];
                        } else if (this->instructions_[i]->arg_[args_c] == 6){
                            sscanf((char *)(instr+n), "%u", &args_uint[args_uint_count]);
                            args[args_c++] = &args_uint[args_uint_count++];
                        } else if (this->instructions_[i]->arg_[args_c] == 7){
                            sscanf((char *)(instr+n), "%lu", &args_ulong[args_ulong_count]);
                            args[args_c++] = &args_ulong[args_ulong_count++];
                        } else if (this->instructions_[i]->arg_[args_c] == 8){
                            args[args_c++] = (void *)(instr+n);
                        } else if (this->instructions_[i]->arg_[args_c] == 9){
                            sscanf((char *)(instr+n), "%f", &args_float[args_float_count]);
                            args[args_c++] = &args_float[args_float_count++];
                        } else if (this->instructions_[i]->arg_[args_c] == 10){
                            sscanf((char *)(instr+n), "%lf", &args_double[args_double_count]);
                            args[args_c++] = &args_double[args_double_count++];
                        } else if (this->instructions_[i]->arg_[args_c] == 11){
                            args[args_c++] = this->get_variable((const char *)(instr+n));
                        } else if (this->instructions_[i]->arg_[args_c] == 12){
                            args_uint[args_uint_count] = arg_c - args_c;
                            args[args_c++] = &args_uint[args_uint_count++];
                            while(1){
                                sscanf((char *)(instr+n), "%c", &args_char[args_char_count]);
                                args[args_c++] = &args_char[args_char_count++];

                                while(*(char *)(instr+n) != 0 && (n < length)) n++;

                                n++;
                                if (*(char *)(instr+n) == 0) n++;
                                if (n >= length) break;
                            }
                            break;
                        } else if (this->instructions_[i]->arg_[args_c] == 13){
                            args_uint[args_uint_count] = arg_c - args_c;
                            args[args_c++] = &args_uint[args_uint_count++];
                            while(1){
                                sscanf((char *)(instr+n), "%hd", &args_short[args_short_count]);
                                args[args_c++] = &args_short[args_short_count++];

                                while(*(char *)(instr+n) != 0 && (n < length)) n++;

                                n++;
                                if (*(char *)(instr+n) == 0) n++;
                                if (n >= length) break;
                            }
                            break;
                        } else if (this->instructions_[i]->arg_[args_c] == 14){
                            args_uint[args_uint_count] = arg_c - args_c;
                            args[args_c++] = &args_uint[args_uint_count++];
                            while(1){
                                sscanf((char *)(instr+n), "%d", &args_int[args_int_count]);
                                args[args_c++] = &args_int[args_int_count++];

                                while(*(char *)(instr+n) != 0 && (n < length)) n++;

                                n++;
                                if (*(char *)(instr+n) == 0) n++;
                                if (n >= length) break;
                            }
                            break;
                        } else if (this->instructions_[i]->arg_[args_c] == 15){
                            args_uint[args_uint_count] = arg_c - args_c;
                            args[args_c++] = &args_uint[args_uint_count++];
                            while(1){
                                sscanf((char *)(instr+n), "%ld", &args_long[args_long_count]);
                                args[args_c++] = &args_long[args_long_count++];

                                while(*(char *)(instr+n) != 0 && (n < length)) n++;

                                n++;
                                if (*(char *)(instr+n) == 0) n++;
                                if (n >= length) break;
                            }
                            break;
                        } else if (this->instructions_[i]->arg_[args_c] == 16){
                            args_uint[args_uint_count] = arg_c - args_c;
                            args[args_c++] = &args_uint[args_uint_count++];
                            while(1){
                                sscanf((char *)(instr+n), "%c", &args_uchar[args_uchar_count]);
                                args[args_c++] = &args_uchar[args_uchar_count++];

                                while(*(char *)(instr+n) != 0 && (n < length)) n++;

                                n++;
                                if (*(char *)(instr+n) == 0) n++;
                                if (n >= length) break;
                            }
                            break;
                        } else if (this->instructions_[i]->arg_[args_c] == 17){
                            args_uint[args_uint_count] = arg_c - args_c;
                            args[args_c++] = &args_uint[args_uint_count++];
                            while(1){
                                sscanf((char *)(instr+n), "%hu", &args_ushort[args_ushort_count]);
                                args[args_c++] = &args_ushort[args_ushort_count++];

                                while(*(char *)(instr+n) != 0 && (n < length)) n++;

                                n++;
                                if (*(char *)(instr+n) == 0) n++;
                                if (n >= length) break;
                            }
                            break;
                        } else if (this->instructions_[i]->arg_[args_c] == 18){
                            args_uint[args_uint_count] = arg_c - args_c;
                            args[args_c++] = &args_uint[args_uint_count++];
                            while(1){
                                sscanf((char *)(instr+n), "%u", &args_uint[args_uint_count]);
                                args[args_c++] = &args_uint[args_uint_count++];

                                while(*(char *)(instr+n) != 0 && (n < length)) n++;

                                n++;
                                if (*(char *)(instr+n) == 0) n++;
                                if (n >= length) break;
                            }
                            break;
                        } else if (this->instructions_[i]->arg_[args_c] == 19){
                            args_uint[args_uint_count] = arg_c - args_c;
                            args[args_c++] = &args_uint[args_uint_count++];
                            while(1){
                                sscanf((char *)(instr+n), "%lu", &args_ulong[args_ulong_count]);
                                args[args_c++] = &args_ulong[args_ulong_count++];

                                while(*(char *)(instr+n) != 0 && (n < length)) n++;

                                n++;
                                if (*(char *)(instr+n) == 0) n++;
                                if (n >= length) break;
                            }
                            break;
                        } else if (this->instructions_[i]->arg_[args_c] == 20){
                            args_uint[args_uint_count] = arg_c - args_c;
                            args[args_c++] = &args_uint[args_uint_count++];
                            while(1){
                                args[args_c++] = (void *)(instr+n);

                                while(*(char *)(instr+n) != 0 && (n < length)) n++;

                                n++;
                                if (*(char *)(instr+n) == 0) n++;
                                if (n >= length) break;
                            }
                            break;
                        } else if (this->instructions_[i]->arg_[args_c] == 21){
                            args_uint[args_uint_count] = arg_c - args_c;
                            args[args_c++] = &args_uint[args_uint_count++];
                            while(1){
                                sscanf((char *)(instr+n), "%f", &args_float[args_float_count]);
                                args[args_c++] = &args_float[args_float_count++];

                                while(*(char *)(instr+n) != 0 && (n < length)) n++;

                                n++;
                                if (*(char *)(instr+n) == 0) n++;
                                if (n >= length) break;
                            }
                            break;
                        } else if (this->instructions_[i]->arg_[args_c] == 22){
                            args_uint[args_uint_count] = arg_c - args_c;
                            args[args_c++] = &args_uint[args_uint_count++];
                            while(1){
                                sscanf((char *)(instr+n), "%lf", &args_double[args_double_count]);
                                args[args_c++] = &args_double[args_double_count++];

                                while(*(char *)(instr+n) != 0 && (n < length)) n++;

                                n++;
                                if (*(char *)(instr+n) == 0) n++;
                                if (n >= length) break;
                            }
                            break;
                        } else if (this->instructions_[i]->arg_[args_c] == 23){
                            args_uint[args_uint_count] = arg_c - args_c;
                            args[args_c++] = &args_uint[args_uint_count++];
                            while(1){
                                args[args_c++] = this->get_variable((const char *)(instr+n));

                                while(*(char *)(instr+n) != 0 && (n < length)) n++;

                                n++;
                                if (*(char *)(instr+n) == 0) n++;
                                if (n >= length) break;
                            }
                            break;
                        } else args_c++;
                    }
                    this->instructions_[i]->func_(this, args);

                    delete[] args;

                    delete[] args_char;
                    delete[] args_short;
                    delete[] args_int;
                    delete[] args_long;
                    delete[] args_uchar;
                    delete[] args_ushort;
                    delete[] args_uint;
                    delete[] args_ulong;

                    delete[] instr;
                    return;
                }
            }
        }
    }
    (this->get_stream()) << "Wrong instruction." << endl;
    delete[] instr;
}
unsigned int Console::register_instruction(unsigned int (*func)(Console*,void**), const char* instruction, unsigned int n, ...){ //n - count of arguments, after n id of type (unsigned int)
    Instruction** i;
    unsigned int length;

    va_list va;

    length = strlen(instruction);
    if (length == 0) return 2; //too short string

    i = (Instruction**)realloc(this->instructions_, (sizeof (Instruction*))*(this->instructions_count_+1));
    if (i == nullptr) return 1; //lack of memory - error

    this->instructions_ = i;

    this->instructions_[this->instructions_count_] = new Instruction;
    if (this->instructions_[this->instructions_count_] == nullptr) return 1; //lack of memory - error

    this->instructions_[this->instructions_count_]->instruction_ = new char[length+1];
    this->instructions_[this->instructions_count_]->instruction_[length] = 0;

    strcpy(this->instructions_[this->instructions_count_]->instruction_, instruction);

    this->instructions_[this->instructions_count_]->arg_count_ = n;
    this->instructions_[this->instructions_count_]->unlimited_ = 0;
    if (n != 0){
        this->instructions_[this->instructions_count_]->arg_ = new char[n];
        if (this->instructions_[this->instructions_count_]->arg_ == nullptr) {
            delete this->instructions_[this->instructions_count_];
            this->instructions_[this->instructions_count_] = nullptr;
            return 1; //lack of memory - error
        }

        va_start(va,n);

        for (unsigned int i = 0; i < n; i++){
            this->instructions_[this->instructions_count_]->arg_[i] = va_arg(va,unsigned int);
            if (this->instructions_[this->instructions_count_]->arg_[i] >= 12) this->instructions_[this->instructions_count_]->unlimited_ = 1;
        }

        va_end(va);
    }

    this->instructions_[this->instructions_count_]->func_ = func;

    this->instructions_count_++;
    return 0; //success
}

unsigned int Console::register_variable(const char* name, void* pointer){
    Variable** v;
    unsigned int length;

    length = strlen(name);
    if (length == 0) return 2; //too short string

    for (unsigned int i = 0; i < this->variables_count_; i++)
        if (strcmp(this->variables_[i]->name_, name) == 0) return 3; //variable with the same name exists

    v = (Variable**)realloc(this->variables_, (sizeof (Variable*))*(this->variables_count_+1));
    if (v == nullptr) return 1; //lack of memory - error

    this->variables_ = v;

    this->variables_[this->variables_count_] = new Variable;
    if (this->variables_[this->variables_count_] == nullptr) return 1; //lack of memory - error

    this->variables_[this->variables_count_]->name_ = new char[length+1];
    this->variables_[this->variables_count_]->name_[length] = 0;

    strcpy(this->variables_[this->variables_count_]->name_, name);

    this->variables_[this->variables_count_]->pointer_ = pointer;

    this->variables_count_++;
    return 0; //success
}

void* Console::get_variable(const char* name){
    for (unsigned int i = 0; i < this->variables_count_; i++){
        if (strcmp(this->variables_[i]->name_, name) == 0) return this->variables_[i]->pointer_;
    }
    return nullptr;
}

const char* Console::get_variable(void* pointer){
    for (unsigned int i = 0; i < this->variables_count_; i++){
        if (this->variables_[i]->pointer_ == pointer) return this->variables_[i]->name_;
    }
    return nullptr;
}

void Console::remove_variable(void* pointer){
    for (unsigned int i = 0; i < this->variables_count_; i++){
        if (this->variables_[i]->pointer_ == pointer) {
                delete[] this->variables_[i]->name_;
                delete this->variables_[i];
                this->variables_[i] = nullptr;

                this->variables_[i] = nullptr;
                this->variables_count_--;

                for(unsigned int n = this->variables_count_; n > i; n--){
                    this->variables_[n-1] = this->variables_[n];
                    this->variables_[n] = nullptr;
                }

                break;
        }
    }
}

void Console::remove_variable(const char* name){
    for (unsigned int i = 0; i < this->variables_count_; i++){
        if (strcmp(this->variables_[i]->name_, name) == 0) {
                delete[] this->variables_[i]->name_;
                delete this->variables_[i];
                this->variables_[i] = nullptr;

                this->variables_[i] = nullptr;
                this->variables_count_--;

                for(unsigned int n = this->variables_count_; n > i; n--){
                    this->variables_[n-1] = this->variables_[n];
                    this->variables_[n] = nullptr;
                }

                break;
        }
    }
}

std::ostream & Console::get_stream(){
    return (*(this->os_));
}
