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
    Voltage_source<double>* r1 = new Voltage_source<double>(8);
    Resistor<double>* r2 = new Resistor<double>(2);
    Resistor<double>* r3 = new Resistor<double>(1);
    Resistor<double>* r4 = new Resistor<double>(1);

    n1->add(r1);
    n2->add(r1);
    n2->add(r2);
    n3->add(r2);
    n3->add(r3);
    n4->add(r3);
    n4->add(r4);
    n1->add(r4);

    r1->connect_in(n1);
    r1->connect_out(n2);

    r2->connect_in(n2);
    r2->connect_out(n3);

    r3->connect_in(n3);
    r3->connect_out(n4);

    r4->connect_in(n4);
    r4->connect_out(n1);

    Current_Solutions<double>* s= new Current_Solutions<double>;
     cout << s->solve(r1) << endl;

    delete n1;
    delete n2;
    delete r1;
    delete r2;
    cout << "Hello world!" << endl;
    return 0;
}*/

/*
#include <iostream>

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
    cout << n4->get_node() << endl;
    Node<double>* n6 = new Node<double>;
    cout << n4->get_node() << endl;
    Voltage_source<double>* r1 = new Voltage_source<double>(8);
    Resistor<double>* r2 = new Resistor<double>(1);
    Resistor<double>* r3 = new Resistor<double>(9);
    Resistor<double>* r4 = new Resistor<double>(1);
    Resistor<double>* r5 = new Resistor<double>(2);
    Resistor<double>* r6 = new Resistor<double>(2);
    Resistor<double>* r7 = new Resistor<double>(2);

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

    Current_Solutions<double>* s= new Current_Solutions<double>;
     cout << s->solve(r1) << endl;

    delete n1;
    delete n2;
    delete r1;
    delete r2;
    cout << "Hello world!" << endl;
    return 0;
}
*/

#include <iostream>

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
    Voltage_source<double>* r1 = new Voltage_source<double>(8);
    Resistor<double>* r2 = new Resistor<double>(1);
    Resistor<double>* r3 = new Resistor<double>(9);
    Resistor<double>* r4 = new Resistor<double>(1);
    Resistor<double>* r5 = new Resistor<double>(2);
    Resistor<double>* r6 = new Resistor<double>(2);
    Resistor<double>* r7 = new Resistor<double>(2);
    Resistor<double>* r8 = new Resistor<double>(2);
    Resistor<double>* r9 = new Resistor<double>(2);
    Resistor<double>* r10 = new Resistor<double>(2);

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

    n4->add(r8);
    n7->add(r8);
    n7->add(r9);
    n8->add(r9);
    n8->add(r10);
    n5->add(r10);

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

    r9->connect_in(n8);
    r9->connect_out(n6);

    Current_Solutions<double>* s= new Current_Solutions<double>;
     cout << s->solve(r1) << endl;

    delete n1;
    delete n2;
    delete r1;
    delete r2;
    cout << "Hello world!" << endl;
    return 0;
}
