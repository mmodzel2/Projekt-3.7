/*
* Name: electronics.hpp
* Purpose: Solving problems with electronics
* @author mmodzel2
* @version 0.6 29-04-2017
*/

#ifndef _ELECTR_HPP
#define _ELECTR_HPP

#include <string>
#include <sstream>
#include <assert.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#include "matrix.hpp"
#include "equation.hpp"

template <class type>
    class EVariable{
        public:
            type con; //constant
            std::string v;
    }; //for use in solving electronics circuits

/*template <class type>
    typedef struct {
        type I;
    } Current;*/

template <class type>
    class Electronics{
        /*private:
            type R; //resistance
            type C; //capacitity
            type I; //inductance
            type P; //power*/
        private:
            Electronics* in_;
            Electronics* out_;
        public:
            Electronics();
            virtual ~Electronics() = 0;

            virtual EVariable<type>* voltage(std::string current) = 0; //for current use
            virtual EVariable<type>* current(std::string current) = 0;

            virtual type voltage(type voltage, int) = 0; //for normal use
            virtual type current(type voltage, int) = 0;

            void connect_in(Electronics<type>* c);
            void connect_out(Electronics<type>* c);
            Electronics<type>* get_connect_in();
            Electronics<type>* get_connect_out();

            virtual unsigned int get_type() = 0;
    };

template <class type>
    class Node: public Electronics<type>{
        private:
            Electronics<type>* (*connections_);
            unsigned int connection_count_;
            unsigned int node_;
        public:
            Node();
            ~Node();
            void add(Electronics<type>* c);

            EVariable<type>* voltage(std::string current);
            EVariable<type>* current(std::string current);

            type voltage(type voltage, int);
            type current(type voltage, int);

            unsigned int get_type();

            Electronics<type>* get(unsigned int n);
            unsigned int get_node() const;
            unsigned int get_connection_count() const;

            static unsigned int node_number;
    };

template <class type>
    class Resistor: public Electronics<type>{
        private:
            type r_; //Resistance
        public:
            Resistor(type resistance);
            ~Resistor();

            EVariable<type>* voltage(std::string current);
            EVariable<type>* current(std::string current);

            type voltage(type current, int);
            type current(type voltage, int);

            unsigned int get_type();
    };

template <class type>
    class Current_source: public Electronics<type>{
        private:
            type j_; //Current
        public:
            Current_source(type current);
            ~Current_source();

            EVariable<type>* voltage(std::string current);
            EVariable<type>* current(std::string current);

            type voltage(type current, int);
            type current(type voltage, int);

            unsigned int get_type();
    };

template <class type>
    class Current_Solutions{
        private:
            type* Voltages_;
            type* Currents_;
        public:
            Current_Solutions();
            ~Current_Solutions();
            unsigned int solve(Electronics<type>* e);
            Node<type>** get_connections(Node<type>* snode, Node<type>* connections_list[], unsigned int &n);
            Node<type>** get_loops(Node<type>* connections_list[], unsigned int n, Node<type>* loops[], unsigned int k, unsigned int l);
    };

template <class type>
    Electronics<type>::Electronics() : in_(nullptr), out_(nullptr){
    }

template <class type>
    Electronics<type>::~Electronics(){
    }

template <class type>
    void Electronics<type>::connect_in(Electronics<type>* c){
        in_ = c;
    }

template <class type>
    void Electronics<type>::connect_out(Electronics<type>* c){
        out_ = c;
    }

template <class type>
    Electronics<type>* Electronics<type>::get_connect_in(){
        return in_;
    }

template <class type>
    Electronics<type>* Electronics<type>::get_connect_out(){
        return out_;
    }

template <class type>
    Node<type>::Node() : connections_(nullptr), connection_count_(0){
        node_ = ++node_number;
    }

template <class type>
    Node<type>::~Node(){
        if (connections_ != nullptr) delete[] connections_;
    }

template <class type>
    unsigned int Node<type>::node_number = 0;

template <class type>
    EVariable<type>* Node<type>::voltage(std::string current){
        EVariable<type>* v = new EVariable<type>;
        v->con = type(0);
        v->v = "1";
        return v;
    }

template <class type>
    EVariable<type>* Node<type>::current(std::string current){
        EVariable<type>* v = new EVariable<type>;
        v->con = 1;
        v->v = current;
        return v;
    }

template <class type>
    type Node<type>::voltage(type current, int){
        return type(0);
    }

template <class type>
    type Node<type>::current(type voltage, int){
        return type(0);
    }

template <class type>
    unsigned int Node<type>::get_type(){
        return 1;
    }

template <class type>
    void Node<type>::add(Electronics<type>* c){
        if (connection_count_ == 0){
            connections_ = new Electronics<type>* [10]; //create block
            ++connection_count_;
            connections_[0] = c; //add element
        } else {
            Electronics<type>* (*temp_connections);
            if (connection_count_%10 == 0){
                temp_connections = new Electronics<type>* [connection_count_+10]; //create new block for node connections
                for (unsigned int i = 0; i < connection_count_; i++) //copy content
                    temp_connections[i] = connections_[i];

                delete[] connections_; //delete old block
                connections_ = temp_connections; //set new block pointer

            }
            connections_[connection_count_++] = c; //add element
        }
    }

template <class type>
    Electronics<type>* Node<type>::get(unsigned int n){
        if (n >= connection_count_) return nullptr;
        return connections_[n];
    }

template <class type>
    unsigned int Node<type>::get_node() const{
        return node_;
    }

template <class type>
    unsigned int Node<type>::get_connection_count() const{
        return connection_count_;
    }

template <class type>
    Resistor<type>::Resistor(type resistance) : r_(resistance){
    }

template <class type>
    Resistor<type>::~Resistor(){
    }

template <class type>
    EVariable<type>* Resistor<type>::voltage(std::string current){
        EVariable<type>* v = new EVariable<type>;
        v->con = r_;
        v->v = current;
        return v;
    }

template <class type>
    EVariable<type>* Resistor<type>::current(std::string current){
        EVariable<type>* v = new EVariable<type>;
        v->con = 1;
        v->v = current;
        return v;
    }

template <class type>
    type Resistor<type>::voltage(type current, int){
        return current*r_;
    }

template <class type>
    type Resistor<type>::current(type voltage, int){
        return voltage/r_;
    }

template <class type>
    unsigned int Resistor<type>::get_type(){
        return 0;
    }

template <class type>
    Current_source<type>::Current_source(type current) : j_(current){
    }

template <class type>
    Current_source<type>::~Current_source(){
    }

template <class type>
    EVariable<type>* Current_source<type>::voltage(std::string current){
        EVariable<type>* v = new EVariable<type>;
        v->con = 0;
        v->v = current;
        return v;
    }

template <class type>
    EVariable<type>* Current_source<type>::current(std::string current){
        EVariable<type>* v = new EVariable<type>;
        v->con = j_;
        v->v = "1";
        return v;
    }

template <class type>
    type Current_source<type>::voltage(type current, int){
        return type(0);
    }

template <class type>
    type Current_source<type>::current(type voltage, int){
        return j_;
    }

template <class type>
    unsigned int Current_source<type>::get_type(){
        return 2;
    }

template <class type>
    Current_Solutions<type>::Current_Solutions() : Voltages_(nullptr), Currents_(nullptr){
    }

template <class type>
    Current_Solutions<type>::~Current_Solutions(){
        if (Voltages_ != nullptr) delete[] Voltages_;
        if (Currents_ != nullptr) delete[] Currents_;
    }

template <class type>
    unsigned int Current_Solutions<type>::solve(Electronics<type>* e){
        //start from finding first node
        bool flag;
        unsigned int nodes_count = 0;
        Node<type>** connection_list;
        Node<type>** connection_loops;

        unsigned int &n = *new unsigned int;
        n = 0;

        Electronics<type>* en = e;
        while(1){
             en = en->get_connect_in(); //go left
             if (en == e) break;
             if (en == nullptr) break; //end of connections
             if (en->get_type() == 1) break; //node detected
        }

       if (en == e) { //Nodes were not created
            cout << "Nodes weren't created" << endl;
       } else {
           cout << "Nodes created" << endl;
            if (en == nullptr){
                en = e;
                while(1){
                    en = en->get_connect_out(); //go right
                    if (en == nullptr) break; //end of connections
                    if (en->get_type() == 1) break; //node detected
                }
            }

            if (en == nullptr) return 1; //current without connections

            cout << "Start node: " << (static_cast<Node<type>*>(en))->get_node() << endl;
            connection_list = get_connections(static_cast<Node<type>*>(en), nullptr, n);
            cout << "Connections count: " << n << endl;
            /* For debug purpose */
            for (unsigned int i = 0; i < n; i++){
                cout << connection_list[i*2]->get_node() << " - " << connection_list[i*2+1]->get_node() << endl;
            }
            /* End */
            Node<type>** nodes = new Node<type>* [n] {nullptr};

            //for (unsigned int i = 0; i < n; i++) nodes[i] = nullptr;

            for (unsigned int i = 0; i < n; i++){
                flag = 0;
                for (unsigned int j = 0; j < nodes_count; j++)
                    if (nodes[j] == connection_list[i*2]){
                        flag = 1;
                        break;
                    }
                if (flag == 0)
                    nodes[nodes_count++] = connection_list[i*2];
            }

            cout << "Nodes count: " << nodes_count << endl;

            for (unsigned int i = 0; i < n; i++) cout << nodes[i]->get_node() << endl;

            /* Prepare matrix for currents to get currents formulas */

            Matrix<double>* I = new Matrix<double>(nodes_count,n); //create current matrix to get node currents
            Matrix<double>* IB = new Matrix<double>(nodes_count,1); //create matrix for right side of current equations

            /* Example build of matrix
                -1   1  v1
                 1  -1  v2
                 e1  e2
                        where e - connection, v - node
                              -1 - start of connection, 1 - end of connection, 0 - node is not a part of connection
            */

            for (unsigned int i = 0; i < n; i++){ //set direction of current in matrix
                //check if node is a part of connection and set direction of current
                for (unsigned int j = 0; j < nodes_count; j++){
                    if (connection_list[i*2] == nodes[j]) I->set(j,i,-1); //start of connection - from this direction current comes
                    if (connection_list[(i*2)+1] == nodes[j]) I->set(j,i,1); //end of connection
                }
            }

            /* Now get values from electronics current functions for each element in circuit */
            for (unsigned int i = 0; i < n; i++){
                for (unsigned int j = 0; j < connection_list[i*2]->get_connection_count(); j++){
                    std::stringstream isstr;
                    EVariable<type> *var, *var1 = nullptr;
                    Electronics<type> *ie, *pie;
                    isstr << "I" << connection_list[i*2]->get_node() << "." << connection_list[(i*2)+1]->get_node();
                    pie = connection_list[i*2];
                    ie = connection_list[i*2]->get(j);
                    while(1){
                        if (ie == nullptr) break;
                        if (ie->get_type() == 1) break;

                        if (ie->get_connect_in() == pie){ //good direction
                            var = ie->current(isstr.str()); //get value for electronic element
                            if (var->v != isstr.str()){ //element is current source
                                if (var1 != nullptr) delete var1;
                                var1 = var; //save current source information
                            } else delete var;

                            pie = ie;
                            ie = ie->get_connect_out(); //go to next element
                        } else { //reverse direction
                            var = ie->current(isstr.str()); //get value for electronic element
                            if (var->v != isstr.str()){ //element is current source
                                if (var1 != nullptr) delete var1;
                                var1 = var;
                                var1->con *= -1; //reverse direction
                            } else delete var;

                            pie = ie;
                            ie = ie->get_connect_in();
                        }
                    }
                    if (ie != nullptr) {
                        if ((static_cast<Node<type>*>(ie)) == connection_list[(i*2)+1]){
                            if (var1 != nullptr){ //found current source
                                cout << "Current source detected." << endl;
                                if (var1->v == "1"){ //current is not depended from another current - probably independent source
                                    cout << "Independent current source detected." << endl;
                                    /*for (unsigned int m = 0; m < nodes_count; m++){
                                        //move element to right of equation
                                        if (I->get(m,i) == -1){
                                                I->set(m,i,0);
                                                IB->set(m,0,var1->con);
                                        } else if (I->get(m,i) == 1){
                                                I->set(m,i,0);
                                                IB->set(m,0,-var1->con);
                                        }
                                    }*/
                                    I->expand(I->get_rows()+1, I->get_columns());
                                    IB->expand(IB->get_rows()+1, 1);
                                    I->set(I->get_rows()-1,i,1);
                                    IB->set(IB->get_rows()-1,0,var1->con);
                                } else if (var1->v[0] == 'I'){ //current depends from another current
                                    //we have to find connection in which current var1->v goes
                                    //to do

                                }
                                //to add voltage dependent current



                                delete var1;
                                break; //found connection
                            }
                        }
                    }
                    if (var1 != nullptr) delete var1;
                }
            }

            /* Show matrix - for test purpose */
            for (unsigned int i = 0; i < I->get_rows(); i++){
                for (unsigned int j = 0; j < I->get_columns(); j++)
                    cout << I->get(i,j) << " ";
                cout << endl;
            }

            cout << "----------" << endl;

            for (unsigned int i = 0; i < IB->get_rows(); i++){
                for (unsigned int j = 0; j < IB->get_columns(); j++)
                    cout << IB->get(i,j) << " ";
                cout << endl;
            }

            /*I->set(0,0,0);
            IB->set(0,0,2);
            I->set(1,0,0);
            IB->set(1,0,-2);

            for (unsigned int i = 0; i < I->get_rows(); i++){
                for (unsigned int j = 0; j < I->get_columns(); j++)
                    cout << I->get(i,j) << " ";
                cout << endl;
            }*/



            /* Prepare next part of matrix for voltages to get voltages formulas */
            /* We need to find loops in network */
            connection_loops = get_loops(connection_list,n,nullptr,0,0);
            if (connection_loops == nullptr) cout << "Loop not found" << endl;

            for (unsigned int i = 0; i < n; i++){
                if (connection_loops[i*(n+1)] != nullptr){
                    for (unsigned int j = 0; j < n+1; j++){
                         if (connection_loops[i*(n+1)+j] == nullptr) break;
                         cout << connection_loops[i*(n+1)+j]->get_node() << "->";
                    }
                    cout << endl;
                }
            }

            stringstream* solution;
            solution = equation(*I, *IB);
            if (solution == nullptr) cout << "No solution..." << endl;
            else{
            for (unsigned int m = 0; m < I->get_columns(); m++)
            {
                cout << solution[m].str() << endl;
            }
            }
        }

        return 0;
    }

template <class type>
    Node<type>** Current_Solutions<type>::get_connections(Node<type>* snode, Node<type>* connections_list[], unsigned int &n){
        bool flag;
        Electronics<type> *e, *in, *out;
        Electronics<type> *pe; //previous node
        Node<type>** temp_list;
        Node<type>* ne;
        unsigned int i,j,k;

        assert (snode->get_connection_count() != 0); //Node has to have one connection
        if (connections_list != nullptr)
            for (i = 0; i < n; i++)
                if (connections_list[i*2] == snode) return connections_list; //node was processed

        cout << "Working on: " << snode->get_node() << " - " << snode->get_connection_count() << endl;

        for (i = 0; i < snode->get_connection_count(); i++){
            cout << "Element: " << i << endl;
            e = snode->get(i);
            pe = snode;
            while(1){
                in = e->get_connect_in();
                out = e->get_connect_out();
                if (in == nullptr || out == nullptr) break;
                cout << "Work: " << endl;
                if (in == pe) {
                    cout << "IN is previous" << endl;
                    if (out->get_type() != 1){
                        pe = e; //move forward
                        e = out;
                        continue;
                    }
                } else if (out == pe) {
                    cout << "OUT is previous" << endl;
                    if (in->get_type() != 1){
                        pe = e; //move forward
                        e = in;
                        continue;
                    }
                    out = in;
                } else cout << "Something goes wrong. :/" << endl; //for test purpose

                ne = static_cast<Node<type>*>(out);
                cout << "Node detected: " << ne->get_node() << "; (size of connections: " << n << ")" << endl;
                if (connections_list == nullptr) connections_list = new Node<type>* [100] {nullptr};
                else {
                    flag = 0;
                    for (j = 0; j < n*2; j+=2){
                        if (connections_list[j] == ne && connections_list[j+1] == snode){
                            cout << "Connection exists" << endl;
                            flag = 1;
                            break;
                        }
                        cout << j << endl;
                        cout << "T: " << connections_list[j]->get_node() << " - " << connections_list[j+1]->get_node() << endl;
                    }
                if (flag) break; //connection exists

                /*temp_list = new Node<type>* [n*2+4] {nullptr};
                    for (j = 0; j < n*2; j=+2){
                        temp_list[j] = connections_list[j];
                        temp_list[j+1] = connections_list[j+1];
                    }

                    delete[] connections_list;
                    connections_list = temp_list;*/
                }

                connections_list[n*2] = snode; //add connection
                connections_list[(n*2)+1] = ne;
                cout << "Connection: " << snode->get_node() << " - " << ne->get_node() << endl;
                n++;

                connections_list = get_connections(static_cast<Node<type>*>(out), connections_list, n); //find connections in found node
                break;
            }
        }
        cout << "End working: " << snode->get_node() << endl;
        return connections_list;
    }

template <class type>
    Node<type>** Current_Solutions<type>::get_loops(Node<type>* connections_list[], unsigned int n, Node<type>* loops[], unsigned int k, unsigned int l){
        /* n - size of connections_list, k - number of loop on which function has to work, l - number of element in loop on which to work */
        bool flag = 0, flag1 = 0;
        unsigned int tempcn, cn = 0;
        Node<type>* tempn;

        bool* memflag = new bool[n]; //block for setting flags that will tell if memory block is copied for specific node - it prevents from unspecific destroying loop before getting to next node in created loop
        for (unsigned int i = 0; i < n; i++) memflag[i] = 0;

        memflag[k] = 1;

        if (loops == nullptr){
            loops = new Node<type>* [n*(n+1)]; //allocate memory for saving connections loops
            /* Build of structure above
                square n*(n+1) in which every loop starts from k*n - where k is number of loop in structure
                every loop has n+1 elements - each element in loop is pointer to node in the loop */
            for (unsigned int j = 1; j < n*(n+1); j++)
                loops[j] = nullptr; //we do not have elements in loops - clear it

            //set first element in first loop - first node
            //the best to start is node with the biggest number of connections
            for (unsigned int j = 0; j < n*2; j+=2){
                tempcn = connections_list[j]->get_connection_count();
                if (tempcn > cn) {
                        cn = tempcn;
                        tempn = connections_list[j];
                }
            }
            loops[0] = tempn;
            k = 0;
            l = 0;
        }

        //find next node in connections_list
        for(unsigned int j = 0; j < n*2; j+=2){
            if (connections_list[j] == loops[k*(n+1)+l]){
                if (flag == 0){ //add node to existing loop
                    flag = 1;
                    loops[k*(n+1)+l+1] = connections_list[j+1];
                } else {
                    for (unsigned int i = 0; i < n; i++)
                        if (loops[i*(n+1)] == nullptr){
                            memflag[i] = 1; //set block

                            for (unsigned int m = 0; m <= l; m++)
                                loops[(i*(n+1))+m] = loops[(k*(n+1))+m]; //copy previous nodes in loop

                            loops[i*(n+1)+l+1] = connections_list[j+1]; //add node to created loop
                            break;
                        }
                }
            }
           /* if (connections_list[j+1] == loops[k*n+l]){
                if (flag == 0){ //add node to existing loop
                    flag = 1;
                    loops[k*n+l+1] = connections_list[j];
                } else {
                    for (unsigned int i = 0; i < n; i++)
                        if (loops[i*n] == nullptr){
                            memflag[i] = 1; //set block

                            for (unsigned int m = 0; m <= l; m++)
                                loops[(i*n)+m] = loops[(k*n)+m]; //copy previous nodes in loop

                            loops[i*n+l+1] = connections_list[j]; //add node to created loop
                            break;
                        }
                }
            }*/
        }

        //make recursion to existing loop and created new loops
        for(unsigned int j = 0; j < n; j++){
            if (memflag[j] == 1){
                flag1 = 1;
                if (loops[j*(n+1)] != loops[j*(n+1)+l+1]){ //loop is not closed

                //check if loop is cut
                flag = 0;
                for (unsigned int i = 1; i < l; i++)
                    if (loops[j*(n+1)+i] == loops[j*(n+1)+l+1]){ //node is in loop - loop has to be skipped
                        for (unsigned int p = 0; p < n+1; p++) loops[j*(n+1)+p] = nullptr;
                        flag = 1;
                        break;
                    }
                    if (flag == 0)  //loop is not cut
                         get_loops(connections_list, n, loops, j, l+1); //work on next or existing loop

                } else cout << "Loop closed." << endl;
            }
        }

        if (flag1 == 0) for (unsigned int p = 0; p < n+1; p++) loops[k*(n+1)+p] = nullptr; //loop not found

        delete[] memflag;

        return loops;
    }


#endif // _ELECTR_HPP
