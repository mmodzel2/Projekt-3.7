/*
* Name: test.hpp
* Purpose: Matrix and solving equations
* @author mmodzel2
* @version 1.0 20-04-2017
*/

#ifndef _TEST_HPP
#define _TEST_HPP

#include <assert.h>

#include "matrix.hpp"

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

        return 0;
    }

template <class type>
    unsigned int Test<type>::test(Console* console, void** args){
        (console->get_stream()) << "create testA 4 4 1 2 3 4 3 5 6 9 4 5 3 2 0 0 0 0" << std::endl;
        console->parse("create testA 4 4 1 2 3 4 3 5 6 9 4 5 3 2 0 0 0 0");
        (console->get_stream()) << "create testB 4 1 1 2 3 0" << std::endl;
        console->parse("create testB 4 1 1 2 3 0");
        (console->get_stream()) << "look testA" << std::endl;
        console->parse("look testA");
        (console->get_stream()) << "look testB" << std::endl;
        console->parse("look testB");
        (console->get_stream()) << "det testA" << std::endl;
        console->parse("det testA");
        (console->get_stream()) << "rank testA" << std::endl;
        console->parse("rank testA");
        (console->get_stream()) << "solve testA testB" << std::endl;
        console->parse("solve testA testB");

        (console->get_stream()) << "mul testA testB" << std::endl;
        console->parse("mul testA testB");
        (console->get_stream()) << "look testA" << std::endl;
        console->parse("look testA");

        (console->get_stream()) << "add testA testB" << std::endl;
        console->parse("add testA testB");
        (console->get_stream()) << "look testA" << std::endl;
        console->parse("look testA");

        (console->get_stream()) << "delete testA" << std::endl;
        console->parse("delete testA");
        (console->get_stream()) << "delete testB" << std::endl;
        console->parse("delete testB");

        return 0;
    }

#endif // _TEST_HPP
