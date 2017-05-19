/*
* Name: test.hpp
* Purpose: Solving problems with electronics
* @author mmodzel2
* @version 1.0 18-05-2017
*/

#ifndef _TEST_HPP
#define _TEST_HPP

#include <assert.h>

#include "matrix.hpp"
#include "electronics.hpp"

template <class type>
    class Test{
        public:
            static unsigned int test(Console* console, void** args);
            static unsigned int test_assert(Console* console, void** args);
    };

template <class type>
    unsigned int Test<type>::test_assert(Console* console, void** args){
        Matrix <type> *m = new Matrix <type> (2,2);
        Matrix <type> *m1 = new Matrix <type> (2,2);

        /* Test matrix class */

        m->set(0,0,1);
        assert(m->get(0,0) == 1);
        assert(m->get(0,1) == 0);
        assert(m->get(1,0) == 0);
        assert(m->get(1,1) == 0);

        m->set(1,1,1);

        m1->set(0,0,3);
        m1->set(0,1,3);
        m1->set(1,0,3);
        m1->set(1,1,3);

        (*m1)+=(*m);

        assert(m1->get(0,0) == 4);
        assert(m1->get(0,1) == 3);
        assert(m1->get(1,0) == 3);
        assert(m1->get(1,1) == 4);

        assert(m1->get(3,3) == 0); //out of bound

        (*m1)*=(*m);

        assert(m1->get(0,0) == 4);
        assert(m1->get(0,1) == 3);
        assert(m1->get(1,0) == 3);
        assert(m1->get(1,1) == 4);

        assert(m1->get(2,1) == 0); //out of bound
        assert(m1->get(2,2) == 0); //out of bound

        assert(m->det() == 1);

        Matrix <double> *m2 = m->inverse();
        assert(m2 != nullptr); //det = 1

        assert(m2->get(0,0) == 1);
        assert(m2->get(0,1) == 0);
        assert(m2->get(1,0) == 0);
        assert(m2->get(1,1) == 1);

        Matrix <double> *m3 = m2->transpose();
        assert(m3 != nullptr);

        assert(m3->get(0,0) == 1);
        assert(m3->get(0,1) == 0);
        assert(m3->get(1,0) == 0);
        assert(m3->get(1,1) == 1);

        delete m;
        delete m1;
        delete m2;
        delete m3;

        /* Test electronics */
        Node<double>* n = new Node<double>("0");
        Resistor<double>* r = new Resistor<double>(10);

        n->add(r);
        assert(n->get(0) == r);
        assert(n->get(1) == nullptr);
        n->remove(r);
        assert(n->get(0) == nullptr);
        assert(n->get(1) == nullptr);

        n->add(r);
        r->connect_in(n);
        assert(r->get_connect_in() == n);

        Node<double>* n1 = new Node<double>("1");
        Voltage_source<double>* e = new Voltage_source<double>(10);

        n->add(e);

        n1->add(r);
        n1->add(e);

        r->connect_out(n1);
        assert(r->get_connect_out() == n1);

        e->connect_out(n1);
        assert(e->get_connect_out() == n1);

        e->connect_in(n);
        assert(r->get_connect_in() == n);

        Current_Solutions<double>* c = new Current_Solutions<double>;
        c->solve(e);

        r->connect_in(nullptr);
        assert(r->get_connect_in() == nullptr);

        delete e;
        delete r;
        delete n;
        delete n1;

        return 0;
    }

template <class type>
    unsigned int Test<type>::test(Console* console, void** args){
        (console->get_stream()) << "cvs e 4" << std::endl;
        console->parse("cvs e 4");
        (console->get_stream()) << "ccs j 3" << std::endl;
        console->parse("ccs j 3");
        (console->get_stream()) << "cr r1 1" << std::endl;
        console->parse("cr r1 1");
        (console->get_stream()) << "cr r2 2" << std::endl;
        console->parse("cr r2 2");
        (console->get_stream()) << "cr r3 3" << std::endl;
        console->parse("cr r3 3");
        (console->get_stream()) << "cr r4 4" << std::endl;
        console->parse("cr r4 4");
        (console->get_stream()) << "cr r5 5" << std::endl;
        console->parse("cr r5 5");
        (console->get_stream()) << "cducs g 0.3 U3.2" << std::endl;
        console->parse("cducs g 0.3 U3.2");

        (console->get_stream()) << "cn 1" << std::endl;
        console->parse("cn 1");
        (console->get_stream()) << "cn 2" << std::endl;
        console->parse("cn 2");
        (console->get_stream()) << "cn 3" << std::endl;
        console->parse("cn 3");
        (console->get_stream()) << "cn 4" << std::endl;
        console->parse("cn 4");
        (console->get_stream()) << "cn 5" << std::endl;
        console->parse("cn 5");
        (console->get_stream()) << "cn 6" << std::endl;
        console->parse("cn 6");
        (console->get_stream()) << "cn 7" << std::endl;
        console->parse("cn 7");

        (console->get_stream()) << "connect 0 6 0 j" << std::endl;
        console->parse("connect 0 6 0 j");
        (console->get_stream()) << "connect 0 6 1 r1" << std::endl;
        console->parse("connect 0 6 1 r1");
        (console->get_stream()) << "connect 0 6 1 r3" << std::endl;
        console->parse("connect 0 6 1 r3");
        (console->get_stream()) << "connect 0 6 1 r5" << std::endl;
        console->parse("connect 0 6 1 r5");
        (console->get_stream()) << "connect 0 6 1 g" << std::endl;
        console->parse("connect 0 6 1 g");
        (console->get_stream()) << "connect 0 1 0 2" << std::endl;
        console->parse("connect 0 1 0 2");
        (console->get_stream()) << "connect 0 4 0 5" << std::endl;
        console->parse("connect 0 4 0 5");
        (console->get_stream()) << "connect 0 1 1 j" << std::endl;
        console->parse("connect 0 1 1 j");
        (console->get_stream()) << "connect 0 2 0 r1" << std::endl;
        console->parse("connect 0 2 0 r1");
        (console->get_stream()) << "connect 0 3 1 e" << std::endl;
        console->parse("connect 0 3 1 e");
        (console->get_stream()) << "connect 0 7 0 e" << std::endl;
        console->parse("connect 0 7 0 e");
        (console->get_stream()) << "connect 0 7 0 r3" << std::endl;
        console->parse("connect 0 7 0 r3");
        (console->get_stream()) << "connect 0 4 0 r5" << std::endl;
        console->parse("connect 0 4 0 r5");
        (console->get_stream()) << "connect 0 5 0 g" << std::endl;
        console->parse("connect 0 5 0 g");
        (console->get_stream()) << "connect 0 2 0 r2" << std::endl;
        console->parse("connect 0 2 0 r2");
        (console->get_stream()) << "connect 0 3 1 r2" << std::endl;
        console->parse("connect 0 3 1 r2");
        (console->get_stream()) << "connect 0 3 0 r4" << std::endl;
        console->parse("connect 0 3 0 r4");
        (console->get_stream()) << "connect 0 4 1 r4" << std::endl;
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

        (console->get_stream()) << "solve e" << std::endl;
        console->parse("solve e");

        (console->get_stream()) << "remove e" << std::endl;
        console->parse("remove e");
        (console->get_stream()) << "remove j" << std::endl;
        console->parse("remove j");
        (console->get_stream()) << "remove r1" << std::endl;
        console->parse("remove r1");
        (console->get_stream()) << "remove r2" << std::endl;
        console->parse("remove r2");
        (console->get_stream()) << "remove r3" << std::endl;
        console->parse("remove r3");
        (console->get_stream()) << "remove r4" << std::endl;
        console->parse("remove r4");
        (console->get_stream()) << "remove r5" << std::endl;
        console->parse("remove r5");
        (console->get_stream()) << "remove g" << std::endl;
        console->parse("remove g");

        (console->get_stream()) << "remove 1" << std::endl;
        console->parse("remove 1");
        (console->get_stream()) << "remove 2" << std::endl;
        console->parse("remove 2");
        (console->get_stream()) << "remove 3" << std::endl;
        console->parse("remove 3");
        (console->get_stream()) << "remove 4" << std::endl;
        console->parse("remove 4");
        (console->get_stream()) << "remove 5" << std::endl;
        console->parse("remove 5");
        (console->get_stream()) << "remove 6" << std::endl;
        console->parse("remove 6");
        (console->get_stream()) << "remove 7" << std::endl;
        console->parse("remove 7");

        return 0;
    }

#endif // _TEST_HPP
