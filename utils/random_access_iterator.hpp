#pragma once

#include "utils.hpp"

namespace ft
{
    
    /*
    ** @brief Random-access iterators allow to access elements at an
    ** arbitrary offset position relative to the element they point
    ** to. This is the most complete iterators. All pointer types
    ** are also valid random-access-iterators.
    */
    template <typename T>
        class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
        {
        public:
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category     iterator_category;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type            value_type;
            typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type       difference_type;
            typedef T*               pointer;
            typedef T&             reference;
            
            random_access_iterator(void) : _ptr(nullptr)
            {}

            random_access_iterator(pointer ptr) : _ptr(ptr)
            {}

            random_access_iterator(const random_access_iterator& x) : _ptr(x._ptr)
            {}

            random_access_iterator &operator=(const random_access_iterator& x)
            {
                if (this == &x)
                    return (*this);
                this->_ptr = x._ptr;
                return (*this);
            }

            virtual ~random_access_iterator() {}

            pointer base() const
            { return (this->_ptr); }

            reference operator*(void) const { return (*_ptr); }

            pointer operator->(void) { return &(this->operator*()); }

            random_access_iterator& operator++(void)
            {
                _ptr++;
                return (*this);
            }

            random_access_iterator operator++(int)
            {
                random_access_iterator ret(*this);
                operator++();
                return (ret);
            }

            random_access_iterator& operator--(void)
            {
                _ptr--;
                return (*this);
            }

            random_access_iterator operator--(int)
            {
                random_access_iterator ret(*this);
                operator--();
                return (ret);
            }

            random_access_iterator operator+(difference_type n) const { return (_ptr + n); }

            random_access_iterator operator-(difference_type n) const { return (_ptr - n); }

            random_access_iterator& operator+=(difference_type n)
            {
                _ptr += n;
                return (*this);
            }

            random_access_iterator& operator-=(difference_type n)
            {
                _ptr -= n;
                return (*this);
            }

            reference operator[](difference_type n) { return (*(operator+(n))); }

            operator random_access_iterator<const T> () const
            { return (random_access_iterator<const T>(this->_ptr)); }

            private:
                pointer _ptr;
        };

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator==(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator==(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator!=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator!=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator<(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator<(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator>(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template<typename T_L,
             typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator>(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator<=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator<=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator>=(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template<typename T_L,
             typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator>=(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template<typename T>
    ft::random_access_iterator<T> operator+(
        typename ft::random_access_iterator<T>::difference_type n,
        typename ft::random_access_iterator<T>& rai)
        {
            return (&(*rai) + n);
        }

    template <typename T>
    typename ft::random_access_iterator<T>::difference_type
    operator-(const ft::random_access_iterator<T> lhs,
              const ft::random_access_iterator<T> rhs)
    {
        return (lhs.base() - rhs.base());
    }

    template<typename T_L, typename T_R>
    typename ft::random_access_iterator<T_L>::difference_type
    operator-(const ft::random_access_iterator<T_L> lhs,
              const ft::random_access_iterator<T_R> rhs)
    {
        return (lhs.base() - rhs.base());
    }

    template <typename T>
    std::ostream& operator<< (std::ostream& out, const ft::random_access_iterator<T>& rai)
    {
        out << rai.base();
        return out;
    }

}