/*
* Name: electronics.hpp
* Purpose: Solving problems with electronics
* @author mmodzel2
* @version 1.00 18-05-2017
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
            std::string v; //string name of current or voltage

            EVariable();
    }; //for use in solving electronics circuits - equals con*v; 0*0 means voltage or current not known; con*1 - independent source

template <class type>
    EVariable<type>::EVariable() : con(0), v(""){
    }

template <class type>
    class Electronics{
        private:
            Electronics* in_;
            Electronics* out_;
        public:
            Electronics();
            virtual ~Electronics() = 0;

            virtual EVariable<type>* voltage(std::string current, bool out) = 0; //for circuit solving use
            virtual EVariable<type>* current(std::string current, bool out) = 0;

            virtual type voltage(type voltage, bool out, int) = 0; //for normal use - not used in solving
            virtual type current(type voltage, bool out, int) = 0;

            void connect_in(Electronics<type>* c);
            void connect_out(Electronics<type>* c);
            Electronics<type>* get_connect_in();
            Electronics<type>* get_connect_out();

            virtual unsigned int get_type() = 0;

            static unsigned int console_connect(Console* console, void** args);
            static unsigned int console_disconnect(Console* console, void** args);

            static unsigned int console_remove(Console* console, void** args);
    };

template <class type>
    class Node: public Electronics<type>{
        private:
            Electronics<type>* (*connections_);
            unsigned int connection_count_;
            std::string node_;
        public:
            Node(std::string node_name);
            ~Node();
            void add(Electronics<type>* c);
            void remove(Electronics<type>* c);

            EVariable<type>* voltage(std::string current, bool out);
            EVariable<type>* current(std::string current, bool out);

            type voltage(type voltage, bool out, int);
            type current(type voltage, bool out, int);

            unsigned int get_type();

            Electronics<type>* get(unsigned int n);
            std::string get_node() const;
            unsigned int get_connection_count() const;

            static unsigned int create(Console* console, void** args);
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
            static unsigned int create(Console* console, void** args);
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
            static unsigned int create(Console* console, void** args);
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
            static unsigned int create(Console* console, void** args);
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
            static unsigned int create(Console* console, void** args);
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
            static unsigned int create(Console* console, void** args);
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
            static unsigned int create(Console* console, void** args);
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
            static unsigned int create(Console* console, void** args);
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
            static unsigned int create(Console* console, void** args);
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
            static unsigned int create(Console* console, void** args);
    };

template <class type>
    class Current_Solutions{
        private:
            type* voltages_;
            type* currents_;
            std::string* connections_;
            unsigned int connections_count_;
        public:
            Current_Solutions();
            ~Current_Solutions();
            unsigned int solve(Electronics<type>* e);
            Node<type>** get_connections(Node<type>* snode, Node<type>* connections_list[], Electronics<type>** (&interconnections_list), unsigned int &n);
            Node<type>** get_loops(Node<type>* connections_list[], unsigned int n, Node<type>* loops[], unsigned int k, unsigned int l);
            void get_connection_current(Node<type>* connections_list[], Electronics<type>* interconnections_list[], unsigned int i, unsigned int n, Matrix<type>* I, Matrix<type>* IB);
            unsigned int get_connection_voltage(Node<type>* connections_list[], Electronics<type>* interconnections_list[], unsigned int i, unsigned int n, Matrix<type>* I, Matrix<type>* IB, unsigned int mr, type dir);
            void get_solutions(Console* console);

            static unsigned int console_solve(Console* console, void** args);
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
    unsigned int Electronics<type>::console_connect(Console* console, void** args){
        Electronics<type>* e = nullptr;
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
        } else {
            if (c1[0] == 'a' || c1[0] == 'A' || c1[0] == '0'){
                e = ((Electronics<double>*)args[1])->get_connect_in();
                /* Check if there was previously connected element - if yes disconnect it */
                if (e != nullptr){
                    if (e->get_connect_in() == ((Electronics<double>*)args[1]))
                        e->connect_in(nullptr); //disconnect element from previous one
                    else if (e->get_connect_out() == ((Electronics<double>*)args[1]))
                        e->connect_out(nullptr); //disconnect element from previous one
                }
                ((Electronics<double>*)args[1])->connect_in((Electronics<double>*)args[3]);
            } else if (c1[0] == 'b' || c1[0] == 'B' || c1[0] == '1'){
                e = ((Electronics<double>*)args[1])->get_connect_out();
                /* Check if there was previously connected element - if yes disconnect it */
                if (e != nullptr){
                    if (e->get_connect_in() == ((Electronics<double>*)args[1]))
                        e->connect_in(nullptr); //disconnect element from previous one
                    else if (e->get_connect_out() == ((Electronics<double>*)args[1]))
                        e->connect_out(nullptr); //disconnect element from previous one
                }
                ((Electronics<double>*)args[1])->connect_out((Electronics<double>*)args[3]);
            }
        }
        if (((Electronics<double>*)args[3])->get_type() == 1){ //Node detected
            ((Node<double>*)args[3])->add((Electronics<double>*)args[1]);
        } else {
            if (c2[0] == 'a' || c2[0] == 'A' || c2[0] == '0'){
                e = ((Electronics<double>*)args[3])->get_connect_in();
                /* Check if there was previously connected element - if yes disconnect it */
                if (e != nullptr){
                    if (e->get_connect_in() == ((Electronics<double>*)args[3]))
                        e->connect_in(nullptr); //disconnect element from previous one
                    else if (e->get_connect_out() == ((Electronics<double>*)args[3]))
                        e->connect_out(nullptr); //disconnect element from previous one
                }
                ((Electronics<double>*)args[3])->connect_in((Electronics<double>*)args[1]);
            } else if (c2[0] == 'b' || c2[0] == 'B' || c2[0] == '1'){
                e = ((Electronics<double>*)args[3])->get_connect_out();
                /* Check if there was previously connected element - if yes disconnect it */
                if (e != nullptr){
                    if (e->get_connect_in() == ((Electronics<double>*)args[3]))
                        e->connect_in(nullptr); //disconnect element from previous one
                    else if (e->get_connect_out() == ((Electronics<double>*)args[3]))
                        e->connect_out(nullptr); //disconnect element from previous one
                }
                ((Electronics<double>*)args[3])->connect_out((Electronics<double>*)args[1]);
            }
        }

        (console->get_stream()) << "Element connected." << std::endl;

        return 0;
}

template <class type>
    unsigned int Electronics<type>::console_disconnect(Console* console, void** args){
        Electronics* e = nullptr;
        if (args[0] == nullptr || args[1] == nullptr){
            (console->get_stream()) << "Bad arguments." << std::endl;
            return 1;
        }

        const char* c1 = ((const char*)args[0]);

        if (!(c1[0] == 'a' || c1[0] == 'A' || c1[0] == '0' || c1[0] == 'b' || c1[0] == 'B' || c1[0] == '1')){
            (console->get_stream()) << "Bad arguments." << std::endl;
            return 1;
        }

        if (((Electronics<double>*)args[1])->get_type() == 1){ //Node detected
                for (unsigned int i = 0; i < ((Node<double>*)args[1])->get_connection_count(); i++){
                    e = ((Node<double>*)args[1])->get(i);
                    if (e->get_connect_in() == ((Electronics<double>*)args[1]))
                        e->connect_in(nullptr); //disconnect element from node
                    if (e->get_connect_out() == ((Electronics<double>*)args[1]))
                        e->connect_out(nullptr); //disconnect element from node
                }
        } else {
            if (c1[0] == 'a' || c1[0] == 'A' || c1[0] == '0'){
               e = ((Electronics<double>*)args[1])->get_connect_in();
               if (e != nullptr){
                    if (e->get_type() == 1){
                        ((Node<double>*)e)->remove((Electronics<double>*)args[1]);
                    } else {
                        if (e->get_connect_in() == ((Electronics<double>*)args[1]))
                            e->connect_in(nullptr); //disconnect element that is connected to disconnecting element
                        if (e->get_connect_out() == ((Electronics<double>*)args[1]))
                            e->connect_out(nullptr); //disconnect element that is connected to disconnecting element
                        ((Electronics<double>*)args[1])->connect_in(nullptr); //disconnect element
                    }
               }
            }
            else if (c1[0] == 'b' ||c1[0] == 'B' || c1[0] == '1'){
               e = ((Electronics<double>*)args[1])->get_connect_out();
               if (e != nullptr){
                    if (e->get_type() == 1){
                        ((Node<double>*)e)->remove((Electronics<double>*)args[1]);
                    } else {
                        if (e->get_connect_in() == ((Electronics<double>*)args[1]))
                            e->connect_in(nullptr); //disconnect element that is connected to disconnecting element
                        if (e->get_connect_out() == ((Electronics<double>*)args[1]))
                            e->connect_out(nullptr); //disconnect element that is connected to disconnecting element
                    }
                    ((Electronics<double>*)args[1])->connect_out(nullptr); //disconnect element
               }
            }
        }

        (console->get_stream()) << "Element disconnected." << std::endl;

        return 0;
}

template <class type>
    unsigned int Electronics<type>::console_remove(Console* console, void** args){
        Electronics* e = nullptr;

        if (args[0] == nullptr){
            (console->get_stream()) << "Element does not exist." << std::endl;
            return 1;
        }

        if (((Electronics<double>*)args[0])->get_type() == 1){ //Node detected
                for (unsigned int i = 0; i < (((Node<double>*)args[0])->get_connection_count()); i++){
                    e = ((Node<double>*)args[0])->get(i);
                    if (e->get_connect_in() == ((Electronics<double>*)args[0]))
                        e->connect_in(nullptr); //disconnect element from node
                    if (e->get_connect_out() == ((Electronics<double>*)args[0]))
                        e->connect_out(nullptr); //disconnect element from node
                }
        } else {
            e = ((Electronics<double>*)args[0])->get_connect_in();
            if (e != nullptr){
                if (e->get_type() == 1){
                    ((Node<double>*)e)->remove((Electronics<double>*)args[0]);
                } else {
                    if (e->get_connect_in() == ((Electronics<double>*)args[0]))
                        e->connect_in(nullptr); //disconnect element that is connected to disconnecting element
                    if (e->get_connect_out() == ((Electronics<double>*)args[0]))
                        e->connect_out(nullptr); //disconnect element that is connected to disconnecting element
                    ((Electronics<double>*)args[0])->connect_in(nullptr); //disconnect element
                }
            }
            e = ((Electronics<double>*)args[0])->get_connect_out();
            if (e != nullptr){
                if (e->get_type() == 1){
                    ((Node<double>*)e)->remove((Electronics<double>*)args[0]);
                } else {
                    if (e->get_connect_in() == ((Electronics<double>*)args[0]))
                        e->connect_in(nullptr); //disconnect element that is connected to disconnecting element
                    if (e->get_connect_out() == ((Electronics<double>*)args[0]))
                        e->connect_out(nullptr); //disconnect element that is connected to disconnecting element
                }
                ((Electronics<double>*)args[0])->connect_out(nullptr); //disconnect element
            }
        }

        console->remove_variable((Electronics<double>*)args[0]);
        delete ((Electronics<double>*)args[0]);

        (console->get_stream()) << "Element removed." << std::endl;

        return 0;
}

template <class type>
    Node<type>::Node(std::string node_name) : connections_(nullptr), connection_count_(0), node_(node_name){
    }

template <class type>
    Node<type>::~Node(){
        if (connections_ != nullptr) delete[] connections_;
    }

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
    void Node<type>::remove(Electronics<type>* c){
        unsigned int i = 0;
        if (connection_count_ != 0){
            for (; i < connection_count_; i++)
                if (connections_[i] == c) break;
            if (i >= connection_count_) return; //element is not connected to node

            if (connection_count_ == 1){
                delete[] connections_;
                connections_ = nullptr;
                connection_count_ = 0;
                return;
            }

            /* Move elements on the list */
            for (++i; i < connection_count_; i++){
                connections_[i-1] = connections_[i];
            }
            --connection_count_;
        }
    }

template <class type>
    Electronics<type>* Node<type>::get(unsigned int n){
        if (n >= connection_count_) return nullptr;
        return connections_[n];
    }

template <class type>
    std::string Node<type>::get_node() const{
        return node_;
    }

template <class type>
    unsigned int Node<type>::get_connection_count() const{
        return connection_count_;
    }

template <class type>
    unsigned int Node<type>::create(Console* console, void** args){
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

        unsigned int ret = console->register_variable((const char *)args[0], ((Electronics<type>*)n));
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

template <class type>
    Resistor<type>::Resistor(type resistance) : r_(resistance){
    }

template <class type>
    Resistor<type>::~Resistor(){
    }

template <class type>
    EVariable<type>* Resistor<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        v->con = r_;
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
    unsigned int Resistor<type>::create(Console* console, void** args){
        Resistor<double>* r;

        if (args[0] == nullptr){
            (console->get_stream()) << "Error while creating resistant element." << std::endl;
            return 1;
        }

        try {
            r = new Resistor<double>(*((double *)args[1]));
        } catch(std::bad_alloc){
            (console->get_stream()) << "Error while creating resistant element." << std::endl;
            return 1;
        }

        unsigned int ret = console->register_variable((const char *)args[0], ((Electronics<type>*)r));
        if (ret == 1){
            delete r;
            (console->get_stream()) << "Lack of free memory. Resistance element cannot be created." << std::endl;
            return 2;
        } else if (ret == 3) {
            delete r;
            (console->get_stream()) << "Variable name reserved. Cannot create resistance element with given variable name." << std::endl;
            return 1;
        }

        (console->get_stream()) << "Element created." << std::endl;

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
    unsigned int Capacitity<type>::create(Console* console, void** args){
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

        unsigned int ret = console->register_variable((const char *)args[0], ((Electronics<type>*)c));
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
    unsigned int Inductance<type>::create(Console* console, void** args){
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

        unsigned int ret = console->register_variable((const char *)args[0], ((Electronics<type>*)l));
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
        return v;
    }

template <class type>
    EVariable<type>* Current_source<type>::current(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        if (out == 1) v->con = j_;
        else v->con = -1*j_;
        v->v = "1";
        return v;
    }

template <class type>
    type Current_source<type>::voltage(type current, bool out, int){
        return type(0);
    }

template <class type>
    type Current_source<type>::current(type voltage, bool out, int){
        if (out == 1) return j_;
        else return -1*j_;
    }

template <class type>
    unsigned int Current_source<type>::get_type(){
        return 2;
    }

template <class type>
    unsigned int Current_source<type>::create(Console* console, void** args){
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

        unsigned int ret = console->register_variable((const char *)args[0], ((Electronics<type>*)j));
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
        return v;
    }

template <class type>
    EVariable<type>* Current_disource<type>::current(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        if (out == 1) v->con = type(l_);
        else v->con = type(-l_);
        v->v = current_;
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
    unsigned int Current_disource<type>::create(Console* console, void** args){
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

        unsigned int ret = console->register_variable((const char *)args[0], ((Electronics<type>*)j));
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
        return v;
    }

template <class type>
    EVariable<type>* Current_dusource<type>::current(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        if (out == 1) v->con = type(b_);
        else v->con = type(-b_);
        v->v = voltage_;
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
    unsigned int Current_dusource<type>::create(Console* console, void** args){
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

        unsigned int ret = console->register_variable((const char *)args[0], ((Electronics<type>*)j));
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

template <class type>
    Voltage_source<type>::Voltage_source(type voltage) : e_(voltage){
    }

template <class type>
    Voltage_source<type>::~Voltage_source(){
    }

template <class type>
    EVariable<type>* Voltage_source<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        if (out == 1) v->con = e_;
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
        if (out == 1) return e_;
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
    unsigned int Voltage_source<type>::create(Console* console, void** args){
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

        unsigned int ret = console->register_variable((const char *)args[0], ((Electronics<type>*)v));
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

template <class type>
    Voltage_disource<type>::Voltage_disource(type l, std::string current) : l_(l), current_(current){
    }

template <class type>
    Voltage_disource<type>::~Voltage_disource(){
    }

template <class type>
    EVariable<type>* Voltage_disource<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        if (out == 1) v->con = l_;
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
    unsigned int Voltage_disource<type>::create(Console* console, void** args){
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

        unsigned int ret = console->register_variable((const char *)args[0], ((Electronics<type>*)v));
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

template <class type>
    Voltage_dusource<type>::Voltage_dusource(type b, std::string voltage) : b_(b), voltage_(voltage){
    }

template <class type>
    Voltage_dusource<type>::~Voltage_dusource(){
    }

template <class type>
    EVariable<type>* Voltage_dusource<type>::voltage(std::string current, bool out){
        EVariable<type>* v = new EVariable<type>;
        if (out == 1) v->con = b_;
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
    unsigned int Voltage_dusource<type>::create(Console* console, void** args){
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

        unsigned int ret = console->register_variable((const char *)args[0], ((Electronics<type>*)v));
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

template <class type>
    Current_Solutions<type>::Current_Solutions() : voltages_(nullptr), currents_(nullptr), connections_(nullptr), connections_count_(0){
    }

template <class type>
    Current_Solutions<type>::~Current_Solutions(){
        if (connections_ != nullptr) delete[] connections_;
        if (voltages_ != nullptr) delete[] voltages_;
        if (currents_ != nullptr) delete[] currents_;
    }

template <class type>
    unsigned int Current_Solutions<type>::solve(Electronics<type>* e){
        //start from finding first node
        bool flag;
        unsigned int nodes_count = 0;
        Node<type>** nodes;
        Node<type>** connection_list;
        Electronics<type>** interconnection_list = nullptr;
        Node<type>** connection_loops;
        unsigned int ret;
        stringstream* solution;

        unsigned int &n = *new unsigned int(0);

        Electronics<type>* en = e->get_connect_in();
        Electronics<type>* pe = e;
        while(1){
             n++;
             if (en == e) break;
             if (en == nullptr) break; //end of connections
             if (en->get_type() == 1) break; //node detected

             //go ahead to find node or closed loop
             if (en->get_connect_in() == pe){
                pe = en;
                en = en->get_connect_out();
             } else if (en->get_connect_out() == pe){
                pe = en;
                en = en->get_connect_in();
             } else en = nullptr;
        }

       if (en == e) { //Nodes were not created
            //cout << "Nodes weren't created" << endl;
            solution = new std::stringstream();
            /* Count elements in circuit */

            //cout << "Count: " << n << endl;

            /* We need to create nodes between elements to solve circuit */
            nodes = new Node<type>* [n];

            pe = e;
            en = e->get_connect_in();

            for (unsigned int i = 0; i < n; i++){
                solution->str("");
                *solution << i;

                nodes[i] = new Node<type>(solution->str());

                //go ahead to find end of loop
                if (en->get_connect_in() == pe){
                    //disconnect element from each other and connect them together with node
                    nodes[i]->add(pe);
                    nodes[i]->add(en);

                    en->connect_in(nodes[i]);

                    if (pe->get_connect_in() == en){ //connect element to node
                        pe->connect_in(nodes[i]);
                    } else pe->connect_out(nodes[i]);

                    pe = en;
                    en = en->get_connect_out();
                } else if (en->get_connect_out() == pe){
                    //disconnect element from each other and connect them together with node
                    nodes[i]->add(pe);
                    nodes[i]->add(en);

                    en->connect_out(nodes[i]);

                    if (pe->get_connect_in() == en){ //connect element to node
                        pe->connect_in(nodes[i]);
                    } else pe->connect_out(nodes[i]);

                    pe = en;
                    en = en->get_connect_in();
                }
            }

            ret = Current_Solutions<type>::solve(e);

            /* Now turn back to previous state */
            for (unsigned int i = 0; i < n; i++){
                /* Disconnect elements from nodes and connect them back together */
                if ((nodes[i]->get(0))->get_connect_in() == nodes[i])
                     (nodes[i]->get(0))->connect_in(nodes[i]->get(1));
                else (nodes[i]->get(0))->connect_out(nodes[i]->get(1));

                if ((nodes[i]->get(1))->get_connect_in() == nodes[i])
                     (nodes[i]->get(1))->connect_in(nodes[i]->get(0));
                else (nodes[i]->get(1))->connect_out(nodes[i]->get(0));

                delete nodes[i];
            }

            delete[] nodes;
            delete solution;
       } else {
           n = 0;
           //cout << "Nodes created" << endl;
            if (en == nullptr){
                en = e;
                while(1){
                    en = en->get_connect_out(); //go right
                    if (en == nullptr) break; //end of connections
                    if (en->get_type() == 1) break; //node detected
                }
            }

            if (en == nullptr) return 1; //current without connections

            //cout << "Start node: " << (static_cast<Node<type>*>(en))->get_node() << endl;
            connection_list = get_connections(static_cast<Node<type>*>(en), nullptr, interconnection_list, n);
            //cout << "Connections count: " << n << endl;

            if (connections_ != nullptr) delete[] connections_;
            connections_ = new std::string[n];
            connections_count_ = n;

            /* Create names of connections. Build of name:
               "One node"."Second node" */
            for (unsigned int i = 0; i < n; i++){
                //cout << connection_list[i*2]->get_node() << " - " << connection_list[i*2+1]->get_node() << endl;
                connections_[i] = connection_list[i*2]->get_node()+"."+connection_list[i*2+1]->get_node();
            }

            /* Find nodes in circuit - they will be needed to set currents in connections */
            nodes = new Node<type>* [n];

            for (unsigned int i = 0; i < n; i++){
                flag = 0;
                for (unsigned int j = 0; j < nodes_count; j++)
                    if (nodes[j] == connection_list[i*2]){
                        flag = 1;
                        break;
                    }
                if (flag == 0)
                    nodes[nodes_count++] = connection_list[i*2];

                flag = 0;
                for (unsigned int j = 0; j < nodes_count; j++)
                    if (nodes[j] == connection_list[i*2+1]){
                        flag = 1;
                        break;
                    }
                if (flag == 0)
                    nodes[nodes_count++] = connection_list[i*2+1];
            }

            /* For test purpose */
            /*cout << "Nodes count: " << nodes_count << endl;
            for (unsigned int i = 0; i < nodes_count; i++) cout << nodes[i]->get_node() << endl;*/

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
            /*for (unsigned int i = 0; i < I->get_rows(); i++){
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
            cout << "----------" << endl;*/

            /* Prepare next part of matrix for voltages to get voltages formulas */
            /* We need to find loops in network */
            connection_loops = get_loops(connection_list,n,nullptr,0,0);
            if (connection_loops == nullptr) {
                /* Loop has not been found */
                currents_ = nullptr;
                voltages_ = nullptr;
                connections_ = nullptr;
                connections_count_ = 0;
                delete &n;

                return 1;
            }

            /* For test purpose - show loops */
            /*for (unsigned int i = 0; i < n*2; i++){
                if (connection_loops[i*(n+1)] != nullptr){
                    for (unsigned int j = 0; j < n+1; j++){
                         if (connection_loops[i*(n+1)+j] == nullptr) break;
                         cout << connection_loops[i*(n+1)+j]->get_node() << "->";
                    }
                    cout << endl;
                }
            }*/

            /* Check connections by looking through loops if there is a connection without loop set current in this connection to zero */
            for (unsigned int i = 0; i < n*2; i++){
                flag = 0;
                for (unsigned int j = 0; j < n*2; j++){
                    if (connection_loops[j*(n+1)] != nullptr){
                        for (unsigned int m = 0; m < n; m++){
                            if (connection_loops[j*(n+1)+m] == nullptr) break;
                            else if (connection_loops[j*(n+1)+m] == connection_list[i]){
                                flag = 1; //found node
                                break;
                            }
                        }
                        if (flag == 1) break;
                    }
                }
                if (flag == 0){ //node has not loop - set current to zero in the connection
                    i &= ~1;

                    I->expand(I->get_rows()+1,I->get_columns());
                    IB->expand(IB->get_rows()+1,1);

                    I->set(I->get_rows()-1,i/2,type(1));
                    i++;
                }
            }

            /* Now get values from electronics voltage functions for each element in loops */
            for (unsigned int m = 0; m < n*2; m++){
                if (connection_loops[m*(n+1)] != nullptr){
                    I->expand(I->get_rows()+1, I->get_columns());
                    IB->expand(IB->get_rows()+1, 1);

                    ret = 0;
                    if (connection_loops[m*(n+1)] == connection_loops[m*(n+1)+2]){ //doubled connection
                        unsigned int j = 0;

                        /* Find repeating connections and create loops for them */
                        while(1){
                            for (; j < n; j++){ //find first repeating connection that does not have unknown voltage
                                if (connection_list[j*2] == connection_loops[m*(n+1)] && connection_list[j*2+1] == connection_loops[m*(n+1)+1]){ //good direction
                                    ret = get_connection_voltage(connection_list, interconnection_list, j, n, I, IB, I->get_rows()-1, type(1));
                                    break;
                                }
                                else if (connection_list[j*2] == connection_loops[m*(n+1)+1] && connection_list[j*2+1] == connection_loops[m*(n+1)]){ //reverse direction
                                    ret = get_connection_voltage(connection_list, interconnection_list, j, n, I, IB, I->get_rows()-1, type(-1));
                                    break;
                                }
                            }
                            if (j >= n){ //connection with known voltage has not been found
                                I->expand(I->get_rows()-1, I->get_columns());
                                IB->expand(IB->get_rows()-1, 1);
                                break;
                            }
                            if (ret == 1) //voltage not found
                                continue; //find another connection that has known voltage

                            unsigned i = j+1;
                            while(1){
                            if (i >= n) break; //all doubled connections with connection above have been found
                                for (; i < n; i++){ //find next repeating connection and create new equation for loop containing first connection above and found one
                                    if (connection_list[i*2] == connection_loops[m*(n+1)] && connection_list[i*2+1] == connection_loops[m*(n+1)+1]){ //good direction
                                        /* Copy context of first equation */
                                        I->expand(I->get_rows()+1, I->get_columns());
                                        IB->expand(IB->get_rows()+1, 1);

                                        for (unsigned int k = 0; k < I->get_columns(); k++)
                                            I->set(I->get_rows()-1,k,I->get(I->get_rows()-2,k));

                                        IB->set(IB->get_rows()-1,0,IB->get(IB->get_rows()-2,0));

                                        //cout << connection_list[i*2]->get_node() << "->" << connection_list[i*2+1]->get_node() << endl;
                                        ret = get_connection_voltage(connection_list, interconnection_list, i, n, I, IB, I->get_rows()-2, type(-1));
                                        break;
                                    }
                                    else if (connection_list[i*2] == connection_loops[m*(n+1)+1] && connection_list[i*2+1] == connection_loops[m*(n+1)]){ //reverse direction
                                        /* Copy context of first equation */
                                        I->expand(I->get_rows()+1, I->get_columns());
                                        IB->expand(IB->get_rows()+1, 1);

                                        for (unsigned int k = 0; k < I->get_columns(); k++)
                                            I->set(I->get_rows()-1,k,I->get(I->get_rows()-2,k));

                                        IB->set(IB->get_rows()-1,0,IB->get(IB->get_rows()-2,0));

                                        ret = get_connection_voltage(connection_list, interconnection_list, i, n, I, IB, I->get_rows()-2, type(1));
                                        break;
                                    }
                                }
                                if (ret == 1){ //voltage not found
                                    /* Move equation to up */
                                    for (unsigned int k = 0; k < I->get_columns(); k++)
                                        I->set(I->get_rows()-2,k,I->get(I->get_rows()-1,k));

                                    IB->set(IB->get_rows()-2,0,I->get(IB->get_rows()-1,0));

                                    /* Remove unnecessary equation */
                                    I->expand(I->get_rows()-1, I->get_columns());
                                    IB->expand(IB->get_rows()-1, 1);
                                }
                                i++;
                            }

                            /* Remove unnecessary equation */
                            I->expand(I->get_rows()-1, I->get_columns());
                            IB->expand(IB->get_rows()-1, 1);
                            break;
                        }
                    } else {
                        for (unsigned int j = 0; j < n; j++){
                            if (connection_loops[m*(n+1)+j+1] == nullptr) break; //end of loop

                            for (unsigned int i = 0; i < n; i++){ //find connection
                                if (connection_list[i*2] == connection_loops[m*(n+1)+j] && connection_list[i*2+1] == connection_loops[m*(n+1)+j+1]){ //good direction
                                    //cout << connection_list[i*2]->get_node() << "->" << connection_list[i*2+1]->get_node() << endl;
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
            }

            /* Make matrix with n equations to get minor faster and solve it quicker*/
            I->expand(n,n);
            IB->expand(n,1);

            /* Show matrix - for test purpose */
            /*for (unsigned int i = 0; i < I->get_rows(); i++){
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

            cout << "----------" << endl;*/

            /* Now solve equations */
            solution = equation<type>(*I, *IB);
            if (solution != nullptr){
                /* Save solutions */
                currents_ = new type[n];
                voltages_ = new type[n];
                for (unsigned int i = 0; i < n; i++){
                    //cout << solution[i].str();
                    solution[i] >> currents_[i];
                }

                delete[] solution;
                /* Get Voltages for solutions */
                for (unsigned int i = 0; i < n; i++){
                    type sum = type(0);
                    for (unsigned int m = 0; m < I->get_columns(); m++)
                        I->set(I->get_rows()-1,m,type(0));
                    IB->set(IB->get_rows()-1,0,type(0));

                    ret = get_connection_voltage(connection_list, interconnection_list, i, n, I, IB, I->get_rows()-1, type(1));
                    if (ret == 0){
                        for (unsigned int m = 0; m < I->get_columns(); m++){
                            sum += I->get(I->get_rows()-1,m)*currents_[m]; //calculate known currents and add to voltage
                        }
                        voltages_[i] = sum-IB->get(IB->get_rows()-1,0);
                    } else {
                        voltages_[i] = type(0);
                    }
                }
            } else {
                currents_ = nullptr;
                voltages_ = nullptr;
                connections_ = nullptr;
                connections_count_ = 0;
            }
            delete[] connection_list;
            delete[] interconnection_list;
            delete[] connection_loops;
            delete[] nodes;
            delete I;
            delete IB;
        }

        delete &n;

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

        //cout << "Working on: " << snode->get_node() << " - " << snode->get_connection_count() << endl;

        if (interconnections_list == nullptr) interconnections_list = new Electronics<type>* [50] {nullptr};

        for (i = 0; i < snode->get_connection_count(); i++){
            e = snode->get(i); //current element in connection
            pe = snode; //previous element in connection
            interconnections_list[n] = e; //add element between nodes to easier find all elements in connection - optimization purpose
            while(1){
                if (e->get_type() == 1) //if node is connected to node without elements between skip finding node
                    out = e;
                else {
                    /* Check each side of connection in element */
                    in = e->get_connect_in();
                    out = e->get_connect_out();
                    if (in == nullptr || out == nullptr) break; //connection is not ended

                    if (in == pe) { //in is connected with previous element in connection
                        if (out->get_type() != 1){
                            pe = e; //move forward
                            e = out;
                            continue;
                        }
                    } else if (out == pe) { //out is connected with previous element in connection
                        if (in->get_type() != 1){
                            pe = e; //move forward
                            e = in;
                            continue;
                        }
                        out = in; //optimization purpose - it does not matter which side of element is node connected
                    } else break;
                }

                ne = static_cast<Node<type>*>(out);
                //cout << "Node detected: " << ne->get_node() << "; (size of connections: " << n << ")" << endl;
                if (connections_list == nullptr) connections_list = new Node<type>* [100] {nullptr};
                else {
                    flag = 0;
                    for (j = 0; j < n*2; j+=2){
                        if (connections_list[j] == ne && connections_list[j+1] == snode){
                            //cout << "Connection exists" << endl;
                            flag = 1;
                            break;
                        }
                    }
                    if (flag) break; //connection exists
                }

                connections_list[n*2] = snode; //add connection
                connections_list[(n*2)+1] = ne;
                //cout << "Connection: " << snode->get_node() << " - " << ne->get_node() << endl;
                n++;

                if (n%50 == 0){ //no more space for connections - expand it
                    temp_list = connections_list;
                    connections_list = new Node<type>* [n*2+100];

                    temp_interlist = interconnections_list;
                    interconnections_list = new Electronics<type>* [n+50];

                    for (j = 0; j < n; ++j){ //copy old block
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
        //cout << "End working: " << snode->get_node() << endl;
        return connections_list;
    }

template <class type>
    Node<type>** Current_Solutions<type>::get_loops(Node<type>* connections_list[], unsigned int n, Node<type>* loops[], unsigned int k, unsigned int l){
        /* n - size of connections_list, k - number of loop on which function has to work, l - number of element in loop on which to work */
        bool flag = 0, flag1 = 0, flag2 = 0;
        unsigned int tempcn = 0, cn = 0;
        Node<type>* tempn = nullptr;

        bool* memflag = new bool[n*2]; //block for setting flags that will tell if memory block is copied for specific node - it prevents from unspecific destroying loop before getting to next node in created loop
        for (unsigned int i = 0; i < n*2; i++) memflag[i] = 0;

        memflag[k] = 1; //block is to recurse

        if (loops == nullptr){
            flag2 = 1;
            loops = new Node<type>* [2*n*(n+1)]; //allocate memory for saving connections loops
            /* Build of structure above
                square n*(n+1) in which every loop starts from k*n - where k is number of loop in structure
                every loop has n+1 elements - each element in loop is pointer to node in the loop */
            for (unsigned int j = 1; j < 2*n*(n+1); j++)
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
                    if (l >= 1)
                        if (loops[k*(n+1)+l-1] == connections_list[j+1]) continue; //skip reverse direction that cuts itself
                    flag = 1;
                    loops[k*(n+1)+l+1] = connections_list[j+1];
                } else if (flag == 1) {
                    if (l >= 1)
                        if (loops[k*(n+1)+l-1] == connections_list[j+1]) continue; //skip reverse direction that cuts itself
                    for (unsigned int i = 0; i < n*2; i++)
                        if (loops[i*(n+1)] == nullptr){
                            memflag[i] = 1; //set block

                            for (unsigned int m = 0; m <= l; m++)
                                loops[(i*(n+1))+m] = loops[(k*(n+1))+m]; //copy previous nodes in loop

                            loops[i*(n+1)+l+1] = connections_list[j+1]; //add node to created loop
                            break;
                        }
                }
            }

            if (connections_list[j+1] == loops[k*(n+1)+l]){
                if (flag == 0){ //add node to existing loop
                    if (l >= 1)
                        if (loops[k*(n+1)+l-1] == connections_list[j]) continue; //skip reverse direction that cuts itself
                    flag = 1;
                    loops[k*(n+1)+l+1] = connections_list[j];
                } else if (flag == 1) {
                    if (l >= 1)
                        if (loops[k*(n+1)+l-1] == connections_list[j]) continue; //skip reverse direction that cuts itself
                    for (unsigned int i = 0; i < n*2; i++)
                        if (loops[i*(n+1)] == nullptr){
                            memflag[i] = 1; //set block

                            for (unsigned int m = 0; m <= l; m++)
                                loops[(i*(n+1))+m] = loops[(k*(n+1))+m]; //copy previous nodes in loop

                            loops[i*(n+1)+l+1] = connections_list[j]; //add node to created loop
                            break;
                        }
                }
            }

        }

        if (flag == 0){ //there is probably connection with the same nodes making closing loop
            if (l == 1){
                /* Check if connection repeats on list */
                for(unsigned int m = 0; m < n*2; m+=2){
                    if (connections_list[m] == loops[k*(n+1)+l-1] && connections_list[m+1] == loops[k*(n+1)+l]){
                        if (flag == 0) flag = 1;
                        else {/* Found repeated connection - close a loop */
                            loops[k*(n+1)+l+1] = loops[k*(n+1)+l-1];
                            break;
                        }
                    }
                }
            }
        }

        //make recursion to existing loop and created new loops
        for(unsigned int j = 0; j < n*2; j++){
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
                    if (flag == 0) //loop is not cut
                         get_loops(connections_list, n, loops, j, l+1); //work on next or existing loop

                }
            }
        }

        if (flag1 == 0) for (unsigned int p = 0; p < n+1; p++) loops[k*(n+1)+p] = nullptr; //loop not found

        delete[] memflag;

        /* Check if every node has loop - if not create new loop with it */
        if (flag2 == 1){
            flag1 = 0;
            for(int j = 0; j < (int)n*2; j+=2){
                flag = 0;

                for (unsigned int i = 0; i < n*2; i++){
                    if (loops[i*(n+1)] != nullptr){
                        for (unsigned int p = 0; p < n; p++)
                            if (connections_list[j] == loops[i*(n+1)+p]){ //node is in loop - end looking in this element
                                flag = 1;
                                break;
                            }
                        if (flag == 1) break;
                    }
                }
                if (flag == 0){ /* Found node that does not have loop */
                    for (unsigned int i = 0; i < n*2; i++)
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

            /* Delete repeating permutation loops - if there is doubling connection on the list, loop with this connection might be doubled */
            for (unsigned int i = 0; i < n*2; i++){
                if (loops[i*(n+1)] != nullptr){
                    unsigned int t = 0;
                    for (; t < n; t++) if (loops[i*(n+1)+t] == nullptr) break;

                    for (unsigned int j = i+1; j < n*2; j++){
                        if (loops[j*(n+1)] != nullptr){
                            unsigned int p = 0;
                            for (; p < n; p++) if (loops[j*(n+1)+p] == nullptr) break;

                            if (p != t) continue; //loops are not equal
                            /* Now check permutation of loops */

                            for (p = 0; p < t; p++){
                                flag = 0;
                                for (unsigned int u = 0; u < t; u++)
                                    if (loops[i*(n+1)+p] == loops[j*(n+1)+u]){
                                        flag = 1;
                                        break;
                                    }
                                if (flag == 0) break;
                            }

                            if (flag == 1) for (p = 0; p < n+1; p++) loops[j*(n+1)+p] = nullptr;
                        }
                    }
                }
            }

            /* Check if connection doubles - add loops */
            for (unsigned int i = 0; i < n*2; i+=2){
                for (unsigned int j = i+2; j < n*2; j+=2){
                    if ((connections_list[i] == connections_list[j]) && (connections_list[i+1] == connections_list[j+1])){
                        for (unsigned int p = 0; p < n*2; p++){ //add doubled connection
                            if (loops[p*(n+1)] == nullptr){
                                loops[p*(n+1)] = connections_list[i];
                                loops[p*(n+1)+1] = connections_list[i+1];
                                loops[p*(n+1)+2] = connections_list[i];
                                break;
                            }
                        }
                        break;
                    }
                }
            }

            /* Delete repeating permutation loops once more - after finding connection doubling loops there can be repeating loops on the list */
            for (unsigned int i = 0; i < n*2; i++){
                if (loops[i*(n+1)] != nullptr){
                    unsigned int t = 0;
                    for (; t < n; t++) if (loops[i*(n+1)+t] == nullptr) break;

                    for (unsigned int j = i+1; j < n*2; j++){
                        if (loops[j*(n+1)] != nullptr){
                            unsigned int p = 0;
                            for (; p < n; p++) if (loops[j*(n+1)+p] == nullptr) break;

                            if (p != t) continue; //loops are not equal
                            /* Now check permutation of loops */

                            for (p = 0; p < t; p++){
                                flag = 0;
                                for (unsigned int u = 0; u < t; u++)
                                    if (loops[i*(n+1)+p] == loops[j*(n+1)+u]){
                                        flag = 1;
                                        break;
                                    }
                                if (flag == 0) break;
                            }

                            if (flag == 1) for (p = 0; p < n+1; p++) loops[j*(n+1)+p] = nullptr;
                        }
                    }
                    //check if loop is too short - that means loop has not been created
                    if (loops[i*(n+1)+2] == nullptr) for (unsigned int p = 0; p < 2; p++) loops[i*(n+1)+p] = nullptr;
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

        pie = connections_list[i*2]; //previous element
        ie = interconnections_list[i]; //current element
        while(1){
            assert (ie != nullptr); //it is not possible that connection ends without second node
            if (ie->get_type() == 1) break;

            if (pie == ie->get_connect_out()){ //reverse direction
                var = ie->voltage(isstr.str(), 1);
            } else var = ie->voltage(isstr.str(), 0);

            if (var->v == "0"){ //voltage not known
                    //Current source detected
                    //zero equation that it was not made
                    for (unsigned int m = 0; m < I->get_columns(); m++)
                        I->set(mrow,m,type(0));

                    IB->set(mrow,0,type(0));
                    return 1; //end finding voltage it is not known - probably current source
            } else if (var->v == "1"){ //voltage independent source detected
                    //Independent voltage source detected.
                    //add equation to matrix
                    IB->set(mrow,0,(IB->get(mrow,0)+(var->con*type(dir))));
            } else if (var->v[0] == 'I'){ //voltage depends from current
                    //check if this is the same current as in connection
                    if  (var->v == isstr.str()){
                        I->set(mrow,i,(I->get(mrow,i)+(var->con*type(-dir))));
                    } else {
                        //we have to find connection in which current var1->v goes
                        for (unsigned int m = 0; m < n; m++){
                            idsstr.str("");
                            idsstr << "I" << connections_list[m*2]->get_node() << "." << connections_list[(m*2)+1]->get_node();

                            if (idsstr.str() == var->v){
                                I->set(mrow,m,I->get(mrow,m)+var->con*type(-dir));
                                break;
                            }

                            /* Check reverse direction */
                            idsstr.str("");
                            idsstr << "I" << connections_list[(m*2)+1]->get_node() << "." << connections_list[m*2]->get_node();
                            if (idsstr.str() == var->v){
                                I->set(mrow,m,I->get(mrow,m)+var->con*type(dir));
                                break;
                            }
                        }
                    }
            } else if (var->v[0] == 'U'){ //voltage source depends from another voltage
                    //we have to find connection in which voltage var1->v goes
                    for (unsigned int m = 0; m < n; m++){
                        idsstr.str("");
                        idsstr << "U" << connections_list[m*2]->get_node() << "." << connections_list[(m*2)+1]->get_node();

                        if (idsstr.str() == var->v){ //if equal get voltage information
                            ret = get_connection_voltage(connections_list, interconnections_list, m, n, I, IB, mrow, var->con*dir); //get information about voltage
                            if (ret != 0) return 1; //voltage is not known
                            break;
                        }

                        /* Check reverse direction */
                        idsstr.str("");
                        idsstr << "U" << connections_list[(m*2)+1]->get_node() << "." << connections_list[m*2]->get_node();

                        if (idsstr.str() == var->v){ //if equal get voltage information
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
        pie = connections_list[i*2]; //previous element in connection
        ie = interconnections_list[i]; //current element in connection
        while(1){
            assert (ie != nullptr); //it is not possible that connection ends without second node
            if (ie->get_type() == 1) break; //if found node - it means connection ends

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
                //Current source detected.
                if (var1->v == "1"){ //current is not depended from another current - probably independent source
                    //Independent current source detected.
                    //add equation to matrix
                    I->expand(I->get_rows()+1, I->get_columns());
                    IB->expand(IB->get_rows()+1, 1);
                    I->set(I->get_rows()-1,i,type(1));
                    IB->set(IB->get_rows()-1,0,type(-1)*var1->con);
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

                        if (isstr.str() == var1->v){ //if equal get voltage information
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

template <class type>
    void Current_Solutions<type>::get_solutions(Console* console){
        if (connections_count_ == 0 || currents_ == nullptr){
            (console->get_stream()) << "No solution." << std::endl;
        } else {
            (console->get_stream()) << "Currents:" << std::endl;
            for (unsigned int i = 0; i < connections_count_; i++){
                (console->get_stream()) << "I" << connections_[i] << " = " << currents_[i] << std::endl;
            }
            (console->get_stream()) << std::endl << "Voltages:" << std::endl;
            for (unsigned int i = 0; i < connections_count_; i++){
                (console->get_stream()) << "U" << connections_[i] << " = " << voltages_[i] << std::endl;
            }
        }
    }

template <class type>
    unsigned int Current_Solutions<type>::console_solve(Console* console, void** args){
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


#endif // _ELECTR_HPP
