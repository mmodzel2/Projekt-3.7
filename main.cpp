#include <iostream>

#include "electronics.hpp"

using namespace std;

int main()
{
    Node<int>* n = new Node<int>;
    cout << n->get_node();
    delete n;
    cout << "Hello world!" << endl;
    return 0;
}
