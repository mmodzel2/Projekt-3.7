#include <stdlib.h>

#include "electronics.hpp"



unsigned int create_capacitity(Console* console, void** args){
    Capacitity<double>* c;

    if (args[0] == nullptr){
        (console->get_stream()) << "Error while creating capacitity element." << std::endl;
        return 1;
    }

    try {
        c = new Capacitity<double>(*((double *)args[1]));
    } catch(std::bad_alloc){
        (console->get_stream()) << "Error while creating capacitity element." << std::endl;
        return 1;
    }

    unsigned int ret = console->register_variable((const char *)args[0], c);
    if (ret == 1){
        delete c;
        (console->get_stream()) << "Lack of free memory. Capacitity element cannot be created." << std::endl;
        return 2;
    } else if (ret == 3) {
        delete c;
        (console->get_stream()) << "Variable name reserved. Cannot create capacitity element with given variable name." << std::endl;
        return 1;
    }

    (console->get_stream()) << "Element created." << std::endl;

    return 0;
}

unsigned int create_inductance(Console* console, void** args){
    Inductance<double>* l;

    if (args[0] == nullptr){
        (console->get_stream()) << "Error while creating inductance element." << std::endl;
        return 1;
    }

    try {
        l = new Inductance<double>(*((double *)args[1]));
    } catch(std::bad_alloc){
        (console->get_stream()) << "Error while creating inductance element." << std::endl;
        return 1;
    }

    unsigned int ret = console->register_variable((const char *)args[0], l);
    if (ret == 1){
        delete l;
        (console->get_stream()) << "Lack of free memory. Inductance element cannot be created." << std::endl;
        return 2;
    } else if (ret == 3) {
        delete l;
        (console->get_stream()) << "Variable name reserved. Cannot create inductance element with given variable name." << std::endl;
        return 1;
    }

    (console->get_stream()) << "Element created." << std::endl;

    return 0;
}

unsigned int create_voltage_supply(Console* console, void** args){
    Voltage_source<double>* v;

    if (args[0] == nullptr){
        (console->get_stream()) << "Error while creating voltage supply element." << std::endl;
        return 1;
    }

    try {
        v = new Voltage_source<double>(*((double *)args[1]));
    } catch(std::bad_alloc){
        (console->get_stream()) << "Error while creating voltage supply element." << std::endl;
        return 1;
    }

    unsigned int ret = console->register_variable((const char *)args[0], v);
    if (ret == 1){
        delete v;
        (console->get_stream()) << "Lack of free memory. Voltage supply element cannot be created." << std::endl;
        return 2;
    } else if (ret == 3) {
        delete v;
        (console->get_stream()) << "Variable name reserved. Cannot create voltage supply element with given variable name." << std::endl;
        return 1;
    }

    (console->get_stream()) << "Element created." << std::endl;

    return 0;
}

unsigned int create_divoltage_supply(Console* console, void** args){
    Voltage_disource<double>* v;
    if (args[0] == nullptr || args[2] == nullptr){
        (console->get_stream()) << "Bad arguments." << std::endl;
        return 1;
    }

    const char* s = (const char*)args[2];

    if (s[0] != 'I'){
        (console->get_stream()) << "Bad current source." << std::endl;
    }

    try {
        v = new Voltage_disource<double>(*((double *)args[1]), s);
    } catch(std::bad_alloc){
        (console->get_stream()) << "Error while creating voltage supply element." << std::endl;
        return 1;
    }

    unsigned int ret = console->register_variable((const char *)args[0], v);
    if (ret == 1){
        delete v;
        (console->get_stream()) << "Lack of free memory. Voltage supply element cannot be created." << std::endl;
        return 2;
    } else if (ret == 3) {
        delete v;
        (console->get_stream()) << "Variable name reserved. Cannot create voltage supply element with given variable name." << std::endl;
        return 1;
    }

    (console->get_stream()) << "Element created." << std::endl;

    return 0;
}

unsigned int create_duvoltage_supply(Console* console, void** args){
    Voltage_dusource<double>* v;

    if (args[0] == nullptr || args[2] == nullptr){
        (console->get_stream()) << "Bad arguments." << std::endl;
        return 1;
    }

    const char* s = (const char*)args[2];

    if (s[0] != 'U'){
        (console->get_stream()) << "Bad current source." << std::endl;
    }

    try {
        v = new Voltage_dusource<double>(*((double *)args[1]), s);
    } catch(std::bad_alloc){
        (console->get_stream()) << "Error while creating voltage supply element." << std::endl;
        return 1;
    }

    unsigned int ret = console->register_variable((const char *)args[0], v);
    if (ret == 1){
        delete v;
        (console->get_stream()) << "Lack of free memory. Voltage supply element cannot be created." << std::endl;
        return 2;
    } else if (ret == 3) {
        delete v;
        (console->get_stream()) << "Variable name reserved. Cannot create voltage supply element with given variable name." << std::endl;
        return 1;
    }

    (console->get_stream()) << "Element created." << std::endl;

    return 0;
}

unsigned int create_current_supply(Console* console, void** args){
    Current_source<double>* j;

    if (args[0] == nullptr){
        (console->get_stream()) << "Error while creating current supply element." << std::endl;
        return 1;
    }

    try {
        j = new Current_source<double>(*((double *)args[1]));
    } catch(std::bad_alloc){
        (console->get_stream()) << "Error while creating current supply element." << std::endl;
        return 1;
    }

    unsigned int ret = console->register_variable((const char *)args[0], j);
    if (ret == 1){
        delete j;
        (console->get_stream()) << "Lack of free memory. Current supply element cannot be created." << std::endl;
        return 2;
    } else if (ret == 3) {
        delete j;
        (console->get_stream()) << "Variable name reserved. Cannot create current supply element with given variable name." << std::endl;
        return 1;
    }

    (console->get_stream()) << "Element created." << std::endl;

    return 0;
}

unsigned int create_dicurrent_supply(Console* console, void** args){
    Current_disource<double>* j;
    if (args[0] == nullptr || args[2] == nullptr){
        (console->get_stream()) << "Bad arguments." << std::endl;
        return 1;
    }

    const char* s = (const char*)args[2];

    if (s[0] != 'I'){
        (console->get_stream()) << "Bad current source." << std::endl;
    }

    try {
        j = new Current_disource<double>(*((double *)args[1]), s);
    } catch(std::bad_alloc){
        (console->get_stream()) << "Error while creating voltage supply element." << std::endl;
        return 1;
    }

    unsigned int ret = console->register_variable((const char *)args[0], j);
    if (ret == 1){
        delete j;
        (console->get_stream()) << "Lack of free memory. Voltage supply element cannot be created." << std::endl;
        return 2;
    } else if (ret == 3) {
        delete j;
        (console->get_stream()) << "Variable name reserved. Cannot create voltage supply element with given variable name." << std::endl;
        return 1;
    }

    (console->get_stream()) << "Element created." << std::endl;

    return 0;
}

unsigned int create_ducurrent_supply(Console* console, void** args){
    Current_dusource<double>* j;

    if (args[0] == nullptr || args[2] == nullptr){
        (console->get_stream()) << "Bad arguments." << std::endl;
        return 1;
    }

    const char* s = (const char*)args[2];

    if (s[0] != 'U'){
        (console->get_stream()) << "Bad voltage source." << std::endl;
    }

    try {
        j = new Current_dusource<double>(*((double *)args[1]), s);
    } catch(std::bad_alloc){
        (console->get_stream()) << "Error while creating voltage supply element." << std::endl;
        return 1;
    }

    unsigned int ret = console->register_variable((const char *)args[0], j);
    if (ret == 1){
        delete j;
        (console->get_stream()) << "Lack of free memory. Voltage supply element cannot be created." << std::endl;
        return 2;
    } else if (ret == 3) {
        delete j;
        (console->get_stream()) << "Variable name reserved. Cannot create voltage supply element with given variable name." << std::endl;
        return 1;
    }

    (console->get_stream()) << "Element created." << std::endl;

    return 0;
}

unsigned int connect(Console* console, void** args){
    if (args[0] == nullptr || args[1] == nullptr || args[2] == nullptr || args[3] == nullptr){
        (console->get_stream()) << "Bad arguments." << std::endl;
        return 1;
    }

    const char* c1 = ((const char*)args[0]);
    const char* c2 = ((const char*)args[2]);

    if (!(c1[0] == 'a' || c1[0] == 'A' || c1[0] == '0' || c1[0] == 'b' || c1[0] == 'B' || c1[0] == '1')){
        (console->get_stream()) << "Bad arguments." << std::endl;
        return 1;
    }
    if (!(c2[0] == 'a' || c2[0] == 'A' || c2[0] == '0' || c2[0] == 'b' || c2[0] == 'B' || c2[0] == '1')){
        (console->get_stream()) << "Bad arguments." << std::endl;
        return 1;
    }

    if (((Electronics<double>*)args[1])->get_type() == 1){ //Node detected
        ((Node<double>*)args[1])->add((Electronics<double>*)args[3]);
        (console->get_stream()) << "Node 1 connected." << std::endl;
    } else {
        if (c1[0] == 'a' || c1[0] == 'A' || c1[0] == '0')
           ((Electronics<double>*)args[1])->connect_in((Electronics<double>*)args[3]);
        else if (c1[0] == 'b' ||c1[0] == 'B' || c1[0] == '1')
            ((Electronics<double>*)args[1])->connect_out((Electronics<double>*)args[3]);
    }
    if (((Electronics<double>*)args[3])->get_type() == 1){ //Node detected
        ((Node<double>*)args[3])->add((Electronics<double>*)args[0]);
        (console->get_stream()) << "Node 2 connected." << std::endl;
    } else {
        if (c2[0] == 'a' || c2[0] == 'A' || c2[0] == '0')
            ((Electronics<double>*)args[3])->connect_in((Electronics<double>*)args[1]);
        else if (c2[0] == 'b' ||c2[0] == 'B' || c2[0] == '1')
            ((Electronics<double>*)args[3])->connect_out((Electronics<double>*)args[1]);
    }

    (console->get_stream()) << "Element connected." << std::endl;

    return 0;
}

unsigned int create_node(Console* console, void** args){
    Node<double>* n;

    if (args[0] == nullptr){
        (console->get_stream()) << "Error while creating node element." << std::endl;
        return 1;
    }

    std::string name = ((const char *)args[0]);
    if (name.find(".") != string::npos){
        (console->get_stream()) << "Error while creating node element. Forbidden name of node." << std::endl;
        return 1;
    }

    try {
        n = new Node<double>(name);
    } catch(std::bad_alloc){
        (console->get_stream()) << "Error while creating node element." << std::endl;
        return 1;
    }

    unsigned int ret = console->register_variable((const char *)args[0], n);
    if (ret == 1){
        delete n;
        (console->get_stream()) << "Lack of free memory. Node element cannot be created." << std::endl;
        return 2;
    } else if (ret == 3) {
        delete n;
        (console->get_stream()) << "Variable name reserved. Cannot create node element with given variable name." << std::endl;
        return 1;
    }

    (console->get_stream()) << "Element created." << std::endl;

    return 0;
}

unsigned int solve(Console* console, void** args){
    if (args[0] == nullptr){
        (console->get_stream()) << "Electronic element does not exist." << std::endl;
        return 1;
    }

    Current_Solutions<double>* c = new Current_Solutions<double>;
    c->solve((Electronics<double>*)args[0]);
    c->get_solutions(console);
    delete c;

    return 0;
}




