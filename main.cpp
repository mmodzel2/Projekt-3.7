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
    Current_source<double>* r1 = new Current_source<double>(2);
    Resistor<double>* r2 = new Resistor<double>(1);
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
}
