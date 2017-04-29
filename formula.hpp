#ifndef _FORMULA_HPP
#define _FORMULA_HPP

#include <sstream>

template <class type>
    class Formula{
        private:
            stringstream* s;
            bool isempty;
        public:
            Formula<type> operator+(const Formula<type> &f) const;
            Formula<type> &operator+=(const Formula<type> &f);
            Formula<type> operator-(const Formula<type> &f) const;
            Formula<type> &operator-=(const Formula<type> &f);
            Formula<type> operator*(const Formula<type> &f) const;
            Formula<type> &operator*=(const Formula<type> &f);
    };



template <class type>
    Formula<type> Formula<type>::operator+(const Formula<type> &f) const{
        Formula<type> *temp;
        if (this->isempty == 0){
                temp = new Formula <type>(this);
                (temp->get()) << "+" << (f->get())->str();
        } else temp = new Formula <type>(f)

        return *temp;
    }

template <class type>
    Formula<type> &Formula<type>::operator+=(const Formula<type> &f){
        if (this->isempty == 0)
            (temp->get()) << (f->get())->str();
        else (temp->get()) << "+" << (f->get())->str();
        return *this;
    }

#endif // _FORMULA_HPP
