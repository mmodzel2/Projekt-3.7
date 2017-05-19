/*
* Name: main.cpp
* Purpose: Solving problems with electronics
* @author mmodzel2
* @version 1.00 18-05-2017
*/

#include <iostream>
#include <stdlib.h>
#include <string>

#include "console.hpp"
#include "electronics.hpp"
#include "test.hpp"

using namespace std;

unsigned int help(Console* console, void** args);

int main()
{
    string str;
    Console* console = new Console(std::cout);

    Test<double>::test_assert(console, nullptr);

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

    console->register_instruction(Test<double>::test, "test",0);
    console->register_instruction(help, "help",0);

    cout << "Write an instruction:" << endl;
    while(1){
        getline(cin,str);
        if (str == "exit" || str == "quit") break;
        console->parse(str.c_str());
    }

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
