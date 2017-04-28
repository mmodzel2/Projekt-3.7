#ifndef _ELECTR_HPP
#define _ELECTR_HPP

#include "matrix.hpp"
#include "equation.hpp"

/*template <class type>
    typedef struct {
        type U;
    } Voltage;

template <class type>
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

            virtual type voltage(type current) = 0; //for current use
            virtual type current(type current) = 0;

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
            Electronics<type>* (*connections_)[];
            unsigned long connection_count_;
            unsigned long node_;
        public:
            Node();
            ~Node();
            void add(Electronics<type>* c);

            type voltage(type current);
            type current(type current);

            type voltage(type voltage, int);
            type current(type voltage, int);

            unsigned int get_type();

            Electronics<type>* get(unsigned long n);
            unsigned long get_node() const;

            static unsigned long node_number;
    };

template <class type>
    class Resistor: public Electronics<type>{
        private:
            type r_; //Resistance
        public:
            Resistor(type resistance);
            ~Resistor();

            type voltage(type current);
            type current(type current);

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
            Node<type>** get_connections(Node<type>* snode, Node<type>** connections_list, unsigned long n);
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
    unsigned long Node<type>::node_number = 0;

template <class type>
    type Node<type>::voltage(type current){
        return type(0);
    }

template <class type>
    type Node<type>::current(type current){
        return type(0);
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
            connections_ = new Electronics<type>*[++connection_count_]; //create block
            connections_[0] = c; //add element
        } else {
            Electronics<type>* (*temp_connections)[];
            temp_connections = new Electronics<type>*[connection_count_+1]; //create new block for node connections
            for (unsigned long i = 0; i < connection_count_; i++) //copy content
                temp_connections[i] = connections_[i];

            temp_connections[connection_count_++] = c; //add element
            delete[] connections_; //delete old block

            connections_ = temp_connections; //set new block pointer
        }
    }

template <class type>
    Electronics<type>* Node<type>::get(unsigned long n){
        if (n >= connection_count_) return nullptr;
        return connections_[n];
    }

template <class type>
    unsigned long Node<type>::get_node() const{
        return node_;
    }

template <class type>
    Resistor<type>::Resistor(type resistance) : r_(resistance){
    }

template <class type>
    Resistor<type>::~Resistor(){
    }

template <class type>
    type Resistor<type>::voltage(type current){
        return r_;
    }

template <class type>
    type Resistor<type>::current(type current){
        return current;
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
        Electronics<type>* en = e;
        Node<type>** connections_list;
        while(1){
             en = en->get_connect_in(); //go left
             if (en == e) break;
             if (en == nullptr) break; //end of connections
             if (en->get_type() == 1) break; //node detected
        }

        if (en == nullptr){
            Electronics<type>* en = e;
            while(1){
                en = en->get_connect_out(); //go right
                if (en == nullptr) break; //end of connections
                if (en->get_type() == 1) break; //node detected
            }
        }

        if (en == e) { //Nodes were not created

        } else {

        }

        if (en == nullptr) return 1; //current without connections

        connections_list = get_connections(dynamic_cast<Node<type>*>(en), nullptr, 0);

        return 0;
    }

template <class type>
    Node<type>** Current_Solutions<type>::get_connections(Node<type>* snode, Node<type>** connections_list, unsigned long n){

    }


#endif // _ELECTR_HPP
