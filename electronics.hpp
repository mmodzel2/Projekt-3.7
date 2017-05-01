/*
* Name: electronics.hpp
* Purpose: Solving problems with electronics
* @author mmodzel2
* @version 0.8 1-05-2017
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

            EVariable();
    }; //for use in solving electronics circuits

/*template <class type>
    typedef struct {
        type I;
    } Current;*/

template <class type>
    EVariable<type>::EVariable() : con(0), v(""){
    }

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

            virtual EVariable<type>* voltage(std::string current, bool out) = 0; //for current use
            virtual EVariable<type>* current(std::string current, bool out) = 0;

            virtual type voltage(type voltage, bool out, int) = 0; //for normal use
            virtual type current(type voltage, bool out, int) = 0;

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

            EVariable<type>* voltage(std::string current, bool out);
            EVariable<type>* current(std::string current, bool out);

            type voltage(type voltage, bool out, int);
            type current(type voltage, bool out, int);

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

            EVariable<type>* voltage(std::string current, bool out);
            EVariable<type>* current(std::string current, bool out);

            type voltage(type current, bool out, int);
            type current(type voltage, bool out, int);

            unsigned int get_type();
    };

template <class type>
    class Current_source: public Electronics<type>{
        private:
            type j_; //Current
        public:
            Current_source(type current);
            ~Current_source();

            EVariable<type>* voltage(std::string current, bool out);
            EVariable<type>* current(std::string current, bool out);

            type voltage(type current, bool out, int);
            type current(type voltage, bool out, int);

            unsigned int get_type();
    };

template <class type>
    class Current_disource: public Electronics<type>{
        private:
            type l_; //constant
            std::string current_;
        public:
            Current_disource(type l, std::string current);
            ~Current_disource();

            EVariable<type>* voltage(std::string current, bool out);
            EVariable<type>* current(std::string current, bool out);

            type voltage(type current, bool out, int);
            type current(type voltage, bool out, int);

            unsigned int get_type();
    };

template <class type>
    class Current_dusource: public Electronics<type>{
        private:
            type b_; //constant
            std::string voltage_;
        public:
            Current_dusource(type b, std::string voltage);
            ~Current_dusource();

            EVariable<type>* voltage(std::string current, bool out);
            EVariable<type>* current(std::string current, bool out);

            type voltage(type current, bool out, int);
            type current(type voltage, bool out, int);

            unsigned int get_type();
    };

template <class type>
    class Voltage_source: public Electronics<type>{
        private:
            type e_; //Voltage
        public:
            Voltage_source(type current);
            ~Voltage_source();

            EVariable<type>* voltage(std::string current, bool out);
            EVariable<type>* current(std::string current, bool out);

            type voltage(type current, bool out, int);
            type current(type voltage, bool out, int);

            unsigned int get_type();
    };

template <class type>
    class Voltage_disource: public Electronics<type>{
        private:
            type l_; //constant
            std::string current_;
        public:
            Voltage_disource(type l, std::string current);
            ~Voltage_disource();

            EVariable<type>* voltage(std::string current, bool out);
            EVariable<type>* current(std::string current, bool out);

            type voltage(type current, bool out, int);
            type current(type voltage, bool out, int);

            unsigned int get_type();
    };

template <class type>
    class Voltage_dusource: public Electronics<type>{
        private:
            type b_; //constant
            std::string voltage_;
        public:
            Voltage_dusource(type b, std::string voltage);
            ~Voltage_dusource();

            EVariable<type>* voltage(std::string current, bool out);
            EVariable<type>* current(std::string current, bool out);

            type voltage(type current, bool out, int);
            type current(type voltage, bool out, int);

            unsigned int get_type();
    };

template <class type>
    class Capacitity: public Electronics<type>{
        private:
            type c_; //capacity
        public:
            Capacitity(type c);
            ~Capacitity();

            EVariable<type>* voltage(std::string current, bool out);
            EVariable<type>* current(std::string current, bool out);

            type voltage(type current, bool out, int);
            type current(type voltage, bool out, int);

            unsigned int get_type();
    };

template <class type>
    class Inductance: public Electronics<type>{
        private:
            type l_; //inductance
        public:
            Inductance(type l);
            ~Inductance();

            EVariable<type>* voltage(std::string current, bool out);
            EVariable<type>* current(std::string current, bool out);

            type voltage(type current, bool out, int);
            type current(type voltage, bool out, int);

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
            Node<type>** get_connections(Node<type>* snode, Node<type>* connections_list[], Electronics<type>** (&interconnections_list), unsigned int &n);
            Node<type>** get_loops(Node<type>* connections_list[], unsigned int n, Node<type>* loops[], unsigned int k, unsigned int l);
            void get_connection_current(Node<type>* connections_list[], Electronics<type>* interconnections_list[], unsigned int i, unsigned int n, Matrix<type>* I, Matrix<type>* IB);
            unsigned int get_connection_voltage(Node<type>* connections_list[], Electronics<type>* interconnections_list[], unsigned int i, unsigned int n, Matrix<type>* I, Matrix<type>* IB, unsigned int mr, type dir);
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
    EVariable<type>* Node<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = type(0);
        v->v = "1";
        return v;
    }

template <class type>
    EVariable<type>* Node<type>::current(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = 1;
        v->v = current;
        return v;
    }

template <class type>
    type Node<type>::voltage(type current, bool out, int){
        return type(0);
    }

template <class type>
    type Node<type>::current(type voltage, bool out, int){
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
            Electronics<type>** temp_connections;
            if (connection_count_%10 == 0){
                temp_connections = connections_;
                connections_ = new Electronics<type>* [connection_count_+10]; //create new block for node connections
                for (unsigned int i = 0; i < connection_count_; i++) //copy content
                    connections_[i] = temp_connections[i];

                delete[] temp_connections; //delete old block
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
    EVariable<type>* Resistor<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = type(-1)*r_;
        v->v = current;
        return v;
    }

template <class type>
    EVariable<type>* Resistor<type>::current(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = 1;
        v->v = current;
        return v;
    }

template <class type>
    type Resistor<type>::voltage(type current, bool out, int){
        return current*r_;
    }

template <class type>
    type Resistor<type>::current(type voltage, bool out, int){
        return voltage/r_;
    }

template <class type>
    unsigned int Resistor<type>::get_type(){
        return 0;
    }

template <class type>
    Capacitity<type>::Capacitity(type c) : c_(c){
    }

template <class type>
    Capacitity<type>::~Capacitity(){
    }

template <class type>
    EVariable<type>* Capacitity<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = 0;
        v->v = "0"; //not known
        return v;
    }

template <class type>
    EVariable<type>* Capacitity<type>::current(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = 0;
        v->v = "1"; //current not goes
        return v;
    }

template <class type>
    type Capacitity<type>::voltage(type current, bool out, int){
        return type(0); //not known
    }

template <class type>
    type Capacitity<type>::current(type voltage, bool out, int){
        return type(0);
    }

template <class type>
    unsigned int Capacitity<type>::get_type(){
        return 0;
    }

template <class type>
    Inductance<type>::Inductance(type l) : l_(l){
    }

template <class type>
    Inductance<type>::~Inductance(){
    }

template <class type>
    EVariable<type>* Inductance<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = 0;
        v->v = "1"; //voltage is zero
        return v;
    }

template <class type>
    EVariable<type>* Inductance<type>::current(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = 1;
        v->v = current;
        return v;
    }

template <class type>
    type Inductance<type>::voltage(type current, bool out, int){
        return type(0);
    }

template <class type>
    type Inductance<type>::current(type voltage, bool out, int){
        return type(0); //not known
    }

template <class type>
    unsigned int Inductance<type>::get_type(){
        return 0;
    }

template <class type>
    Current_source<type>::Current_source(type current) : j_(current){
    }

template <class type>
    Current_source<type>::~Current_source(){
    }

template <class type>
    EVariable<type>* Current_source<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = 0;
        v->v = "0"; //voltage is not known
        //v->con = j_;
        //v->v = "1";
        return v;
    }

template <class type>
    EVariable<type>* Current_source<type>::current(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        if (out == 0) v->con = j_;
        else v->con = -1*j_;
        v->v = "1";
        //v->con = 1;
        //v->v = current;
        return v;
    }

template <class type>
    type Current_source<type>::voltage(type current, bool out, int){
        return type(0);
    }

template <class type>
    type Current_source<type>::current(type voltage, bool out, int){
        if (out == 0) return j_;
        else return -1*j_;
    }

template <class type>
    unsigned int Current_source<type>::get_type(){
        return 2;
    }

template <class type>
    Current_disource<type>::Current_disource(type l, std::string current) : l_(l), current_(current){
    }

template <class type>
    Current_disource<type>::~Current_disource(){
    }

template <class type>
    EVariable<type>* Current_disource<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = 0;
        v->v = "0"; //voltage is not known
        //v->con = j_;
        //v->v = "1";
        return v;
    }

template <class type>
    EVariable<type>* Current_disource<type>::current(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        if (out == 0) v->con = type(l_);
        else v->con = type(-l_);
        v->v = current_;
        //v->con = 1;
        //v->v = current;
        return v;
    }

template <class type>
    type Current_disource<type>::voltage(type current, bool out, int){
        return type(0); //not known
    }

template <class type>
    type Current_disource<type>::current(type voltage, bool out, int){
        return type(0); //not known
    }

template <class type>
    unsigned int Current_disource<type>::get_type(){
        return 3;
    }

template <class type>
    Current_dusource<type>::Current_dusource(type b, std::string voltage) : b_(b), voltage_(voltage){
    }

template <class type>
    Current_dusource<type>::~Current_dusource(){
    }

template <class type>
    EVariable<type>* Current_dusource<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = 0;
        v->v = "0"; //voltage is not known
        //v->con = j_;
        //v->v = "1";
        return v;
    }

template <class type>
    EVariable<type>* Current_dusource<type>::current(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        if (out == 0) v->con = type(b_);
        else v->con = type(-b_);
        v->v = voltage_;
        //v->con = 1;
        //v->v = current;
        return v;
    }

template <class type>
    type Current_dusource<type>::voltage(type current, bool out, int){
        return type(0); //not known
    }

template <class type>
    type Current_dusource<type>::current(type voltage, bool out, int){
        return type(0); //not known
    }

template <class type>
    unsigned int Current_dusource<type>::get_type(){
        return 3;
    }

template <class type>
    Voltage_source<type>::Voltage_source(type voltage) : e_(voltage){
    }

template <class type>
    Voltage_source<type>::~Voltage_source(){
    }

template <class type>
    EVariable<type>* Voltage_source<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        if (out == 0) v->con = e_;
        else v->con = type(-1)*e_;
        v->v = "1";
        return v;
    }

template <class type>
    EVariable<type>* Voltage_source<type>::current(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = 1;
        v->v = current;
        return v;
    }

template <class type>
    type Voltage_source<type>::voltage(type current, bool out, int){
        if (out == 0) return e_;
        else return type(-1)*e_;
    }

template <class type>
    type Voltage_source<type>::current(type voltage, bool out, int){
        return type(0);
    }

template <class type>
    unsigned int Voltage_source<type>::get_type(){
        return 2;
    }

template <class type>
    Voltage_disource<type>::Voltage_disource(type l, std::string current) : l_(l), current_(current){
    }

template <class type>
    Voltage_disource<type>::~Voltage_disource(){
    }

template <class type>
    EVariable<type>* Voltage_disource<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        if (out == 0) v->con = l_;
        else v->con = type(-1)*l_;
        v->v = current_;
        return v;
    }

template <class type>
    EVariable<type>* Voltage_disource<type>::current(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = 1;
        v->v = current;
        return v;
    }

template <class type>
    type Voltage_disource<type>::voltage(type current, bool out, int){
        return type(0); //not known
    }

template <class type>
    type Voltage_disource<type>::current(type voltage, bool out, int){
        return type(0); //not known
    }

template <class type>
    unsigned int Voltage_disource<type>::get_type(){
        return 3;
    }

template <class type>
    Voltage_dusource<type>::Voltage_dusource(type b, std::string voltage) : b_(b), voltage_(voltage){
    }

template <class type>
    Voltage_dusource<type>::~Voltage_dusource(){
    }

template <class type>
    EVariable<type>* Voltage_dusource<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        if (out == 0) v->con = b_;
        else v->con = type(-1)*b_;
        v->v = voltage_;
        return v;
    }

template <class type>
    EVariable<type>* Voltage_dusource<type>::current(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = 1;
        v->v = current;
        return v;
    }

template <class type>
    type Voltage_dusource<type>::voltage(type current, bool out, int){
        return type(0); //not known
    }

template <class type>
    type Voltage_dusource<type>::current(type voltage, bool out, int){
        return type(0); //not known
    }

template <class type>
    unsigned int Voltage_dusource<type>::get_type(){
        return 3;
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
        Electronics<type>** interconnection_list = nullptr;
        Node<type>** connection_loops;
        unsigned int ret;

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
            connection_list = get_connections(static_cast<Node<type>*>(en), nullptr, interconnection_list, n);
            cout << "Connections count: " << n << endl;
            /* For debug purpose */
            for (unsigned int i = 0; i < n; i++){
                cout << connection_list[i*2]->get_node() << " - " << connection_list[i*2+1]->get_node() << endl;
            }
            /* End */
            Node<type>** nodes = new Node<type>* [n];

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

            for (unsigned int i = 0; i < nodes_count; i++) cout << nodes[i]->get_node() << endl;

            /* Prepare matrix for currents to get currents formulas */

            Matrix<type>* I = new Matrix<type>(nodes_count,n); //create current matrix to get node currents
            Matrix<type>* IB = new Matrix<type>(nodes_count,1); //create matrix for right side of current equations

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
                    if (connection_list[i*2] == nodes[j]) I->set(j,i,type(-1)); //start of connection - from this direction current comes
                    if (connection_list[(i*2)+1] == nodes[j]) I->set(j,i,type(1)); //end of connection
                }
            }

            /* Remove dependent current */
            I->expand(I->get_rows()-1,I->get_columns());
            IB->expand(IB->get_rows()-1,1);

            /* Now get values from electronics current functions for each element in circuit */
            for (unsigned int i = 0; i < n; i++){
                    get_connection_current(connection_list, interconnection_list, i, n, I, IB);
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
            if (connection_loops == nullptr) {
                    cout << "Loop not found" << endl;
                    return 1;
            }

            for (unsigned int i = 0; i < n; i++){
                if (connection_loops[i*(n+1)] != nullptr){
                    for (unsigned int j = 0; j < n+1; j++){
                         if (connection_loops[i*(n+1)+j] == nullptr) break;
                         cout << connection_loops[i*(n+1)+j]->get_node() << "->";
                    }
                    cout << endl;
                }
            }

            /* Now get values from electronics voltage functions for each element in loops */
            for (unsigned int m = 0; m < n; m++){
                if (connection_loops[m*(n+1)] != nullptr){
                    I->expand(I->get_rows()+1, I->get_columns());
                    IB->expand(IB->get_rows()+1, 1);
                    ret = 0;
                    for (unsigned int j = 0; j < n; j++){
                        if (connection_loops[m*(n+1)+j+1] == nullptr) break; //end of loop

                        for (unsigned int i = 0; i < n; i++){ //find connection
                            if (connection_list[i*2] == connection_loops[m*(n+1)+j] && connection_list[i*2+1] == connection_loops[m*(n+1)+j+1]){ //good direction
                                cout << connection_list[i*2]->get_node() << "->" << connection_list[i*2+1]->get_node() << endl;
                                ret = get_connection_voltage(connection_list, interconnection_list, i, n, I, IB, I->get_rows()-1, type(1));
                                break;
                            }
                            else if (connection_list[i*2] == connection_loops[m*(n+1)+j+1] && connection_list[i*2+1] == connection_loops[m*(n+1)+j]){ //reverse direction
                                ret = get_connection_voltage(connection_list, interconnection_list, i, n, I, IB, I->get_rows()-1, type(-1));
                                break;
                            }
                        }
                        if (ret == 1){ //voltage not found
                            I->expand(I->get_rows()-1, I->get_columns());
                            IB->expand(IB->get_rows()-1, 1);
                            break;
                        }
                    }
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

            /* Now solve equations */

            cout << "Solving..." << endl;

            stringstream* solution;
            solution = equation<type>(*I, *IB);
            if (solution == nullptr) cout << "No solution..." << endl;
            else {
                Currents_ = new type[n];
                Voltages_ = new type[n];
                for (unsigned int i = 0; i < n; i++){
                    //cout << "I" << connection_list[i*2]->get_node() << "." << connection_list[(i*2)+1]->get_node() << " = " << solution[i].str() << endl;
                    cout << solution[i].str() << endl;
                    solution[i] >> Currents_[i];
                }
                /* Get Voltages for solutions */
                for (unsigned int i = 0; i < n; i++){
                    type sum = type(0);
                    for (unsigned int m = 0; m < I->get_columns(); m++)
                        I->set(I->get_rows()-1,m,type(0));
                    IB->set(IB->get_rows()-1,0,type(0));

                    ret = get_connection_voltage(connection_list, interconnection_list, i, n, I, IB, I->get_rows()-1, type(1));
                    if (ret == 0){
                        for (unsigned int m = 0; m < I->get_columns(); m++){
                            sum += I->get(I->get_rows()-1,m)*Currents_[m];
                        }
                        Voltages_[i] = sum-IB->get(IB->get_rows()-1,0);
                    } else {
                        Voltages_[i] = type(0);
                    }
                }
                cout << "Voltages: " << endl;
                for (unsigned int i = 0; i < n; i++){
                    //cout << "U" << connection_list[i*2]->get_node() << "." << connection_list[(i*2)+1]->get_node() << " = " << Voltages_[i] << endl;
                    cout << Voltages_[i] << endl;
                }
                }
        }

        return 0;
    }

template <class type>
    Node<type>** Current_Solutions<type>::get_connections(Node<type>* snode, Node<type>* connections_list[], Electronics<type>** (&interconnections_list), unsigned int &n){
        bool flag;
        Electronics<type> *e, *in, *out;
        Electronics<type> *pe; //previous node
        Node<type>** temp_list;
        Electronics<type>** temp_interlist;
        Node<type>* ne;
        unsigned int i,j;

        assert (snode->get_connection_count() != 0); //Node has to have one connection
        if (connections_list != nullptr)
            for (i = 0; i < n; i++)
                if (connections_list[i*2] == snode) return connections_list; //node was processed

        cout << "Working on: " << snode->get_node() << " - " << snode->get_connection_count() << endl;

        if (interconnections_list == nullptr) interconnections_list = new Electronics<type>* [50] {nullptr};

        for (i = 0; i < snode->get_connection_count(); i++){
            cout << "Element: " << i << endl;
            e = snode->get(i);
            pe = snode;
            interconnections_list[n] = e; //add element between nodes to easier find elements all connection elements - optimization purpose
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

                if (n%50 == 0){
                    temp_list = connections_list;
                    connections_list = new Node<type>* [n*2+100];

                    temp_interlist = interconnections_list;
                    interconnections_list = new Electronics<type>* [n+50];

                    for (j = 0; j < n; ++j){
                        connections_list[j*2] = temp_list[j*2];
                        connections_list[j*2+1] = temp_list[j*2+1];

                        interconnections_list[j] = temp_interlist[j];
                    }

                    delete[] temp_list;
                    delete[] temp_interlist;
                }

                connections_list = get_connections(static_cast<Node<type>*>(out), connections_list, interconnections_list, n); //find connections in found node
                break;
            }
        }
        cout << "End working: " << snode->get_node() << endl;
        return connections_list;
    }

template <class type>
    Node<type>** Current_Solutions<type>::get_loops(Node<type>* connections_list[], unsigned int n, Node<type>* loops[], unsigned int k, unsigned int l){
        /* n - size of connections_list, k - number of loop on which function has to work, l - number of element in loop on which to work */
        bool flag = 0, flag1 = 0, flag2 = 0;
        unsigned int tempcn, cn = 0;
        Node<type>* tempn;

        bool* memflag = new bool[n]; //block for setting flags that will tell if memory block is copied for specific node - it prevents from unspecific destroying loop before getting to next node in created loop
        for (unsigned int i = 0; i < n; i++) memflag[i] = 0;

        memflag[k] = 1;

        if (loops == nullptr){
            flag2 = 1;
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
                    if (loops[j*(n+1)+i] == loops[j*(n+1)+l+1]){ //node is in loop -   wloop has to be skipped
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

        /* Check if every node has loop - if not create new loop with it */
        if (flag2 == 1){
            flag1 = 0;
            for(int j = 0; j < (int)n*2; j+=2){
                flag = 0;

                for (unsigned int i = 0; i < n; i++){
                    if (loops[i*(n+1)] != nullptr){
                        for (unsigned int p = 0; p < n; p++)
                            if (connections_list[j] == loops[i*(n+1)+p]){
                                flag = 1;
                                break;
                            }
                        if (flag == 1) break;
                    }
                }
                if (flag == 0){ /* Found node that does not have loop */
                    for (unsigned int i = 0; i < n; i++)
                        if (loops[i*(n+1)] == nullptr){
                            loops[i*(n+1)] = connections_list[j]; /* Create new loop */
                            get_loops(connections_list, n, loops, i, 0);
                            break;
                        }
                    j = -2; //check again
                    if (flag1 == 1) break;
                    flag1 = 1;
                }
            }
        }

        return loops;
    }

template <class type>
    unsigned int Current_Solutions<type>::get_connection_voltage(Node<type>* connections_list[], Electronics<type>* interconnections_list[], unsigned int i, unsigned int n, Matrix<type>* I, Matrix<type>* IB, unsigned int mrow, type dir){
        /* mrow - matrix row to work on, n - count of connections, dir - multiplier for direction and dependent sources */
        std::stringstream isstr, idsstr;
        EVariable<type> *var = nullptr;
        Electronics<type> *ie, *pie;
        unsigned int ret;

        isstr << "I" << connections_list[i*2]->get_node() << "." << connections_list[(i*2)+1]->get_node();

        pie = connections_list[i*2];
        ie = interconnections_list[i];
        while(1){
            assert (ie != nullptr);
            if (ie->get_type() == 1) break;

            if (pie == ie->get_connect_out()){ //reverse direction
                var = ie->voltage(isstr.str(), 1);
            } else var = ie->voltage(isstr.str(), 0);

            if (var->v == "0"){ //voltage not known
                    cout << "Current source detected." << endl;
                    //zero equation that it was not made
                    for (unsigned int m = 0; m < I->get_columns(); m++)
                        I->set(mrow,m,type(0));

                    IB->set(mrow,0,type(0));
                    return 1; //end finding voltage it is not known - probably current source
            } else if (var->v == "1"){ //voltage independent source detected
                    cout << "Independent voltage source detected." << endl;
                    //add equation to matrix
                    IB->set(mrow,0,(IB->get(mrow,0)+(var->con*type(-dir))));
            } else if (var->v[0] == 'I'){ //voltage depends from current
                    //check if this is the same current as in connection
                    if  (var->v == isstr.str()){
                        I->set(mrow,i,(IB->get(mrow,i)+(var->con*type(dir))));
                    } else {
                        //we have to find connection in which current var1->v goes
                        for (unsigned int m = 0; m < n; m++){
                            idsstr.str("");
                            idsstr << "I" << connections_list[m*2]->get_node() << "." << connections_list[(m*2)+1]->get_node();

                            if (idsstr.str() == var->v){
                                I->set(mrow,m,var->con*type(dir));
                                break;
                            }

                            /* Check reverse direction */
                            idsstr.str("");
                            idsstr << "I" << connections_list[(m*2)+1]->get_node() << "." << connections_list[m*2]->get_node();
                            if (idsstr.str() == var->v){
                                I->set(mrow,m,var->con*type(-dir));
                                break;
                            }
                        }
                    }
            } else if (var->v[0] == 'U'){ //voltage source depends from another voltage
                    //we have to find connection in which voltage var1->v goes
                    for (unsigned int m = 0; m < n; m++){
                        idsstr.str("");
                        idsstr << "U" << connections_list[m*2]->get_node() << "." << connections_list[(m*2)+1]->get_node();

                        if (idsstr.str() == var->v){
                            ret = get_connection_voltage(connections_list, interconnections_list, m, n, I, IB, mrow, var->con*dir); //get information about voltage
                            if (ret != 0) return 1; //voltage is not known
                            break;
                        }

                        /* Check reverse direction */
                        idsstr.str("");
                        idsstr << "U" << connections_list[(m*2)+1]->get_node() << "." << connections_list[m*2]->get_node();

                        if (idsstr.str() == var->v){
                            ret = get_connection_voltage(connections_list, interconnections_list, m, n, I, IB, mrow, var->con*(-dir)); //get information about voltage
                            if (ret != 0) return 1; //voltage is not known
                            break;
                        }
                    }
            }

            delete var;

            if (pie == ie->get_connect_in()){ //good direction
                pie = ie;
                ie = ie->get_connect_out();
            } else { //reverse direction
                pie = ie;
                ie = ie->get_connect_in();
            }

        }
        return 0;
    }


template <class type>
    void Current_Solutions<type>::get_connection_current(Node<type>* connections_list[], Electronics<type>* interconnections_list[], unsigned int i, unsigned int n, Matrix<type>* I, Matrix<type>* IB){
        std::stringstream isstr;
        EVariable<type> *var, *var1 = nullptr;
        Electronics<type> *ie, *pie;

        isstr << "I" << connections_list[i*2]->get_node() << "." << connections_list[(i*2)+1]->get_node();
        pie = connections_list[i*2];
        ie = interconnections_list[i];
        while(1){
            assert (ie != nullptr);
            if (ie->get_type() == 1) break;

            if (ie->get_connect_in() == pie){ //good direction
                  var = ie->current(isstr.str(),0); //get value for electronic element
            } else var = ie->current(isstr.str(),1); //get value for electronic element

            if (var->v != isstr.str()){ //element is current source
                if (var1 != nullptr) delete var1;
                    var1 = var; //save current source information
                } else delete var;

                pie = ie;
                ie = ie->get_connect_out(); //go to next element
            }
            if (var1 != nullptr){ //found current source
                cout << "Current source detected." << endl;
                if (var1->v == "1"){ //current is not depended from another current - probably independent source
                    cout << "Independent current source detected." << endl;
                    //add equation to matrix
                    I->expand(I->get_rows()+1, I->get_columns());
                    IB->expand(IB->get_rows()+1, 1);
                    I->set(I->get_rows()-1,i,type(1));
                    IB->set(IB->get_rows()-1,0,var1->con);
                } else if (var1->v[0] == 'I'){ //current depends from another current
                    //we have to find connection in which current var1->v goes
                    unsigned int m;
                    for (m = 0; m < n; m++){
                        isstr.str("");
                        isstr << "I" << connections_list[m*2]->get_node() << "." << connections_list[(m*2)+1]->get_node();

                        if (isstr.str() == var1->v){
                            I->expand(I->get_rows()+1, I->get_columns());
                            IB->expand(IB->get_rows()+1, 1);
                            I->set(I->get_rows()-1,i,type(1));
                            I->set(I->get_rows()-1,m,type(-1)*var1->con);
                            break;
                        }

                        /* Check reverse direction */
                        isstr.str("");
                        isstr << "I" << connections_list[(m*2)+1]->get_node() << "." << connections_list[m*2]->get_node();

                        if (isstr.str() == var1->v){
                            I->expand(I->get_rows()+1, I->get_columns());
                            IB->expand(IB->get_rows()+1, 1);
                            I->set(I->get_rows()-1,i,type(1));
                            I->set(I->get_rows()-1,m,var1->con);
                            break;
                        }
                    }
                    if (m == n){ //current not found - current is 0
                        I->expand(I->get_rows()+1, I->get_columns());
                        IB->expand(IB->get_rows()+1, 1);
                        I->set(I->get_rows()-1,i,type(1));
                    }
                } else if (var1->v[0] == 'U'){ //current depends from another voltage
                    //we have to find connection in which voltage var1->v goes
                    for (unsigned int m = 0; m < n; m++){
                        isstr.str("");
                        isstr << "U" << connections_list[m*2]->get_node() << "." << connections_list[(m*2)+1]->get_node();

                        if (isstr.str() == var1->v){
                            I->expand(I->get_rows()+1, I->get_columns());
                            IB->expand(IB->get_rows()+1, 1);
                            I->set(I->get_rows()-1,i,type(1));
                            get_connection_voltage(connections_list, interconnections_list, m, n, I, IB, I->get_rows()-1, type(-1)*var1->con); //get information about voltage
                            break;
                        }

                        /* Check reverse direction */
                        isstr.str("");
                        isstr << "U" << connections_list[(m*2)+1]->get_node() << "." << connections_list[m*2]->get_node();

                        if (isstr.str() == var1->v){
                            I->expand(I->get_rows()+1, I->get_columns());
                            IB->expand(IB->get_rows()+1, 1);
                            I->set(I->get_rows()-1,i,type(1));
                            get_connection_voltage(connections_list, interconnections_list, m, n, I, IB, I->get_rows()-1, var1->con); //get information about voltage
                            break;
                        }
                    }
                }

                delete var1;
            }
    }


#endif // _ELECTR_HPP
