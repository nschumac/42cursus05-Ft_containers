#ifndef VECTORITERATOR_HPP
# define VECTORITERATOR_HPP

#include <cstddef>

#include "../extras/choose.hpp"

namespace ft
{
    template <typename T, bool isConst>
    class vector_iterator 
    {
        public:

            typedef T                                           value_type;
            typedef typename ft::choose<isConst, const T*, T*>::type pointer;
            typedef typename ft::choose<isConst, const T&, T&>::type reference;
            typedef typename std::random_access_iterator_tag    iterator_category;
            typedef typename std::ptrdiff_t                     difference;

        private:
            pointer _ptr;

        public:

            /*
             * Constructor/Destructors
             */

            vector_iterator (pointer ptr = 0) : _ptr(ptr) {}
			vector_iterator (const vector_iterator<T, false>& in) : _ptr(in.getPointer()) {}

            ~vector_iterator () {}

            /*
             * Constructor/Destructors
             */

            /*
             * Getter
             */

            pointer getPointer () const { return this->_ptr; };

            /*
             * Getter
             */

            /*
             * Operator
             */
            
            vector_iterator& operator=(vector_iterator const &in) { this->_ptr = in._ptr; return *this; }

            vector_iterator& operator+=(int i) {this->_ptr += i; return *this; }
            vector_iterator& operator-=(int i) {this->_ptr -= i; return *this; }
            vector_iterator operator+(int i) const {vector_iterator tmp(*this); tmp += i; return tmp; }
            vector_iterator operator-(int i) const {vector_iterator tmp(*this); tmp -= i; return tmp; }

            difference operator-(vector_iterator const &in) const { return this->_ptr - in._ptr; }

            vector_iterator& operator++() { ++this->_ptr; return *this;}
            vector_iterator operator++(int i) { vector_iterator tmp(*this);  ++this->_ptr; return tmp;}
            vector_iterator& operator--(){ --this->_ptr; return *this;}
            vector_iterator operator--(int i) { vector_iterator tmp(*this);  --this->_ptr; return tmp;}


            bool operator<=(vector_iterator const &in) const { return this->_ptr <= in._ptr; }
            bool operator>=(vector_iterator const &in) const { return this->_ptr >= in._ptr; }
            bool operator==(vector_iterator const &in) const { return this->_ptr == in._ptr; }
            bool operator!=(vector_iterator const &in) const { return this->_ptr != in._ptr; }
            bool operator<(vector_iterator const &in) const { return this->_ptr < in._ptr; }
            bool operator>(vector_iterator const &in) const { return this->_ptr > in._ptr; }

            reference operator*() const { return *this->_ptr; }
            pointer operator->() const { return this->_ptr; }
            reference operator[](int i) const { return this->_ptr[i]; }

            /*
             * Operator
             */

    };

}



#endif
