#ifndef REVERSE_VECTOR_ITERATOR_HPP
# define REVERSE_VECTOR_ITERATOR_HPP

#include <cstddef>


#include "../extras/choose.hpp"

namespace ft
{

    template <typename T, bool isConst>
    class reverse_vector_iterator 
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

            reverse_vector_iterator (pointer ptr = 0) : _ptr(ptr) {}
            reverse_vector_iterator (reverse_vector_iterator const &in) : _ptr(in._ptr) {}

            ~reverse_vector_iterator () {}

            /*
             * Constructor/Destructors
             */

            /*
             * Getter
             */

            reverse_vector_iterator base() const { return reverse_vector_iterator(this->_ptr + 1); }

            pointer getPointer () const { return this->_ptr; }

            /*
             * Getter
             */

            /*
             * Operator
             */
            
            reverse_vector_iterator& operator=(reverse_vector_iterator const &in) { this->_ptr = in._ptr; return *this; }

            reverse_vector_iterator& operator+=(int i) {this->_ptr -= i; return *this; }
            reverse_vector_iterator& operator-=(int i) {this->_ptr += i; return *this; }
            reverse_vector_iterator operator+(int i) const {reverse_vector_iterator tmp(*this); tmp -= i; return tmp; }
            reverse_vector_iterator operator-(int i) const {reverse_vector_iterator tmp(*this); tmp += i; return tmp; }

            difference operator-(reverse_vector_iterator const &in) const { return this->_ptr - in._ptr; }

            reverse_vector_iterator& operator++() { --this->_ptr; return *this;}
            reverse_vector_iterator operator++(int i) { reverse_vector_iterator tmp(*this);  --this->_ptr; return tmp;}
            reverse_vector_iterator& operator--(){ ++this->_ptr; return *this;}
            reverse_vector_iterator operator--(int i) { reverse_vector_iterator tmp(*this);  ++this->_ptr; return tmp;}


            bool operator<=(reverse_vector_iterator const &in) const { return this->_ptr <= in._ptr; }
            bool operator>=(reverse_vector_iterator const &in) const { return this->_ptr >= in._ptr; }
            bool operator==(reverse_vector_iterator const &in) const { return this->_ptr == in._ptr; }
            bool operator!=(reverse_vector_iterator const &in) const { return this->_ptr != in._ptr; }
            bool operator<(reverse_vector_iterator const &in) const { return this->_ptr < in._ptr; }
            bool operator>(reverse_vector_iterator const &in) const { return this->_ptr > in._ptr; }

            value_type operator*() const { return *this->_ptr; }
            pointer operator->() const { return this->_ptr; }
            value_type operator[](int i) const { return this->_ptr[i]; }

            /*
             * Operator
             */

    };

}



#endif
