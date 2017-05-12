#include <iostream>
#include <stdlib.h>
#include <string>

#include "console.hpp"
#include "electronics.hpp"

using namespace std;

int main()
{
    string str;
    Console* console = new Console(std::cout);

    console->register_instruction(create_resistance, "create_resistance", 2, 8, 10);
    console->register_instruction(create_resistance, "cr", 2, 8, 10);
    console->register_instruction(create_capacitity, "create_capacitity", 2, 8, 10);
    console->register_instruction(create_capacitity, "cc", 2, 8, 10);
    console->register_instruction(create_inductance, "create_inductance", 2, 8, 10);
    console->register_instruction(create_inductance, "cc", 2, 8, 10);
    console->register_instruction(create_voltage_supply, "create_voltage_supply", 2, 8, 10);
    console->register_instruction(create_voltage_supply, "cvs", 2, 8, 10);
    console->register_instruction(create_current_supply, "create_current_supply", 2, 8, 10);
    console->register_instruction(create_current_supply, "ccs", 2, 8, 10);
    console->register_instruction(create_divoltage_supply, "create_divoltage_supply", 3, 8, 10, 8);
    console->register_instruction(create_divoltage_supply, "cdivs", 3, 8, 10, 8);
    console->register_instruction(create_duvoltage_supply, "create_duvoltage_supply", 3, 8, 10, 8);
    console->register_instruction(create_duvoltage_supply, "cduvs", 3, 8, 10, 8);
    console->register_instruction(create_dicurrent_supply, "create_dicurrent_supply", 3, 8, 10, 8);
    console->register_instruction(create_dicurrent_supply, "cdics", 3, 8, 10, 8);
    console->register_instruction(create_ducurrent_supply, "create_ducurrent_supply", 3, 8, 10, 8);
    console->register_instruction(create_ducurrent_supply, "cducs", 3, 8, 10, 8);
    console->register_instruction(create_node, "create_node", 1, 8);
    console->register_instruction(create_node, "cn", 1, 8);
    console->register_instruction(create_ducurrent_supply, "cducs", 3, 8, 10, 8);

    console->register_instruction(connect, "connect", 4, 8, 11, 8, 11);
    console->register_instruction(solve, "solve",1,11);

    console->parse("cvs e 30");
    console->parse("cr r1 10");
    console->parse("cr r2 10");
    console->parse("cr r3 10");
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

    console->parse("cvs e4 30");
    console->parse("cr r4 30");
    console->parse("cn n5");
    console->parse("cn n6");
    console->parse("connect 0 n5 0 e4");
    console->parse("connect 0 n6 1 e4");
    console->parse("connect 0 n6 0 r4");
    console->parse("connect 0 n5 1 r4");

    cout << "Write an instruction:" << endl;
    while(1){
        getline(cin,str);
        if (str == "exit" || str == "quit") break;
        console->parse(str.c_str());
    }

    return 0;
}


/*#include <iostream>

#include "electronics.hpp"

using namespace std;

int main()
{
    Node<double>* n1 = new Node<double>;
    cout << n1->get_node() << endl;
    Node<double>* n2 = new Node<double>;
    cout << n2->get_node() << endl;
    Node<double>* n3 = new Node<double>;
    cout << n3->get_node() << endl;
    Node<double>* n4 = new Node<double>;
    cout << n4->get_node() << endl;
    Node<double>* n5 = new Node<double>;
    cout << n5->get_node() << endl;
    Node<double>* n6 = new Node<double>;
    cout << n6->get_node() << endl;
    Node<double>* n7 = new Node<double>;
    cout << n7->get_node() << endl;
    Node<double>* n8 = new Node<double>;
    cout << n8->get_node() << endl;
    Node<double>* n9 = new Node<double>;
    cout << n9->get_node() << endl;
    Node<double>* n10 = new Node<double>;
    cout << n10->get_node() << endl;

    Voltage_source<double>* r1 = new Voltage_source<double>(8);
    Resistor<double>* r2 = new Resistor<double>(1);
    Resistor<double>* r3 = new Resistor<double>(12);
    Resistor<double>* r4 = new Resistor<double>(1);
    Resistor<double>* r5 = new Resistor<double>(2);
    Resistor<double>* r6 = new Resistor<double>(16);
    Resistor<double>* r7 = new Resistor<double>(2);
    Resistor<double>* r8 = new Resistor<double>(2);
    Resistor<double>* r9 = new Resistor<double>(24);
    Resistor<double>* r10 = new Resistor<double>(2);
    Resistor<double>* r11 = new Resistor<double>(8);
    Resistor<double>* r12 = new Resistor<double>(8);
    Resistor<double>* r13 = new Resistor<double>(8);

    n1->add(r1);
    n2->add(r1);
    n2->add(r2);
    n3->add(r2);
    n3->add(r3);
    n4->add(r3);
    n4->add(r4);
    n1->add(r4);

    n3->add(r5);
    n5->add(r5);
    n5->add(r6);
    n6->add(r6);
    n6->add(r7);
    n4->add(r7);

    n5->add(r8);
    n7->add(r8);
    n7->add(r9);
    n8->add(r9);
    n8->add(r10);
    n6->add(r10);

    n7->add(r11);
    n9->add(r11);
    n9->add(r12);
    n10->add(r12);
    n10->add(r13);
    n8->add(r13);

    r1->connect_in(n1);
    r1->connect_out(n2);

    r2->connect_in(n2);
    r2->connect_out(n3);

    r3->connect_in(n3);
    r3->connect_out(n4);

    r4->connect_in(n4);
    r4->connect_out(n1);

    r5->connect_in(n3);
    r5->connect_out(n5);

    r6->connect_in(n5);
    r6->connect_out(n6);

    r7->connect_in(n6);
    r7->connect_out(n4);

    r8->connect_in(n5);
    r8->connect_out(n7);

    r9->connect_in(n7);
    r9->connect_out(n8);

    r10->connect_in(n6);
    r10->connect_out(n8);

    r11->connect_in(n7);
    r11->connect_out(n9);

    r12->connect_in(n9);
    r12->connect_out(n10);

    r13->connect_in(n10);
    r13->connect_out(n8);

    Current_Solutions<double>* s= new Current_Solutions<double>;
     cout << s->solve(r1) << endl;

    delete n1;
    delete n2;
    delete r1;
    delete r2;
    cout << "Hello world!" << endl;
    return 0;
}*/


