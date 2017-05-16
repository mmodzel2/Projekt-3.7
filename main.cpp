/*
* Name: main.cpp
* Purpose: Solving problems with electronics
* @author mmodzel2
* @version 0.98 14-05-2017
*/

#include <iostream>
#include <stdlib.h>
#include <string>

#include "console.hpp"
#include "electronics.hpp"

using namespace std;

unsigned int test(Console* console, void** args);
unsigned int help(Console* console, void** args);

int main()
{
    string str;
    Console* console = new Console(std::cout);

    console->register_instruction(Resistor<double>::create, "create_resistance", 2, 8, 10);
    console->register_instruction(Resistor<double>::create, "cr", 2, 8, 10);
    console->register_instruction(Capacitity<double>::create, "create_capacitity", 2, 8, 10);
    console->register_instruction(Capacitity<double>::create, "cc", 2, 8, 10);
    console->register_instruction(Inductance<double>::create, "create_inductance", 2, 8, 10);
    console->register_instruction(Inductance<double>::create, "ci", 2, 8, 10);
    console->register_instruction(Voltage_source<double>::create, "create_voltage_supply", 2, 8, 10);
    console->register_instruction(Voltage_source<double>::create, "cvs", 2, 8, 10);
    console->register_instruction(Current_source<double>::create, "create_current_supply", 2, 8, 10);
    console->register_instruction(Current_source<double>::create, "ccs", 2, 8, 10);
    console->register_instruction(Voltage_disource<double>::create, "create_divoltage_supply", 3, 8, 10, 8);
    console->register_instruction(Voltage_disource<double>::create, "cdivs", 3, 8, 10, 8);
    console->register_instruction(Voltage_dusource<double>::create, "create_duvoltage_supply", 3, 8, 10, 8);
    console->register_instruction(Voltage_dusource<double>::create, "cduvs", 3, 8, 10, 8);
    console->register_instruction(Current_disource<double>::create, "create_dicurrent_supply", 3, 8, 10, 8);
    console->register_instruction(Current_disource<double>::create, "cdics", 3, 8, 10, 8);
    console->register_instruction(Current_dusource<double>::create, "create_ducurrent_supply", 3, 8, 10, 8);
    console->register_instruction(Current_dusource<double>::create, "cducs", 3, 8, 10, 8);
    console->register_instruction(Node<double>::create, "create_node", 1, 8);
    console->register_instruction(Node<double>::create, "cn", 1, 8);

    console->register_instruction(Electronics<double>::console_connect, "connect", 4, 8, 11, 8, 11);
    console->register_instruction(Electronics<double>::console_disconnect, "disconnect", 2, 8, 11);
    console->register_instruction(Electronics<double>::console_remove, "remove", 1, 11);
    console->register_instruction(Current_Solutions<double>::console_solve, "solve",1,11);

    console->register_instruction(test, "test",0);
    console->register_instruction(help, "help",0);

    cout << "Write an instruction:" << endl;
    while(1){
        getline(cin,str);
        if (str == "exit" || str == "quit") break;
        console->parse(str.c_str());
    }

    return 0;
}

unsigned int test(Console* console, void** args){
    console->parse("cvs e 4");
    console->parse("ccs j 3");
    console->parse("cr r1 1");
    console->parse("cr r2 2");
    console->parse("cr r3 3");
    console->parse("cr r4 4");
    console->parse("cr r5 5");
    console->parse("cducs g 0.3 U3.2");

    console->parse("cn 1");
    console->parse("cn 2");
    console->parse("cn 3");
    console->parse("cn 4");
    console->parse("cn 5");
    console->parse("cn 6");
    console->parse("cn 7");

    console->parse("connect 0 6 0 j");
    console->parse("connect 0 6 1 r1");
    console->parse("connect 0 6 1 r3");
    console->parse("connect 0 6 1 r5");
    console->parse("connect 0 6 1 g");
    console->parse("connect 0 1 0 2");
    console->parse("connect 0 4 0 5");
    console->parse("connect 0 1 1 j");
    console->parse("connect 0 2 0 r1");
    console->parse("connect 0 3 1 e");
    console->parse("connect 0 7 0 e");
    console->parse("connect 0 7 0 r3");
    console->parse("connect 0 4 0 r5");
    console->parse("connect 0 5 0 g");
    console->parse("connect 0 2 0 r2");
    console->parse("connect 0 3 1 r2");
    console->parse("connect 0 3 0 r4");
    console->parse("connect 0 4 1 r4");

/*  console->parse("cvs e 30");
    console->parse("cr r1 10");
    console->parse("cr r2 10");
    console->parse("cr r3 10");
    console->parse("cdivs r4 200 In1.n4");
    console->parse("cn n1");
    console->parse("cn n2");
    console->parse("cn n3");
    console->parse("cn n4");
    console->parse("connect 0 n1 0 e");
    console->parse("connect 0 n4 1 e");
    console->parse("connect 0 n1 0 r1");
    console->parse("connect 0 n2 1 r1");
    console->parse("connect 0 n2 0 r2");
    console->parse("connect 0 n3 1 r2");
    console->parse("connect 0 n3 0 r3");
    console->parse("connect 0 n4 1 r3");
    console->parse("connect 0 n3 0 r4");
    console->parse("connect 0 n4 1 r4");
    */

    console->parse("solve e");

    console->parse("remove e");
    console->parse("remove j");
    console->parse("remove r1");
    console->parse("remove r2");
    console->parse("remove r3");
    console->parse("remove r4");
    console->parse("remove r5");
    console->parse("remove g");

    console->parse("remove 1");
    console->parse("remove 2");
    console->parse("remove 3");
    console->parse("remove 4");
    console->parse("remove 5");
    console->parse("remove 6");
    console->parse("remove 7");

    return 0;
}

unsigned int help(Console* console, void** args){
    (console->get_stream()) << "cn - create_node [name]" << std::endl;
    (console->get_stream()) << "cr - create_resistance [name] [resistance]" << std::endl;
    (console->get_stream()) << "cc - create_capacitity  [name] [capacitity]" << std::endl;
    (console->get_stream()) << "ci - create_inductance [name] [inductance]" << std::endl;
    (console->get_stream()) << "cvs - create_voltage_supply [name] [voltage]" << std::endl;
    (console->get_stream()) << "ccs - create_current_supply [name] [current]" << std::endl;
    (console->get_stream()) << "cdivs - create_divoltage_supply [name] [multiplier] [current_name] - create voltage source controlled by current " << std::endl;
    (console->get_stream()) << "cduvs - create_duvoltage_supply [name] [multiplier] [voltage_name] - create voltage source controlled by voltage" << std::endl;
    (console->get_stream()) << "cdics - create_dicurrent_supply [name] [multiplier] [current_name] - create current source controlled by current " << std::endl;
    (console->get_stream()) << "cducs - create_ducurrent_supply [name] [multiplier] [voltage_name] - create current source controlled by voltage" << std::endl;
    (console->get_stream()) << "connect [side1] [name1] [side2] [name2]" << std::endl;
    (console->get_stream()) << "disconnect [side] [name]" << std::endl;
    (console->get_stream()) << "solve [name]" << std::endl;
    (console->get_stream()) << "remove [name]" << std::endl;

    return 0;
}
