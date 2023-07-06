#ifndef _STD_COPY_ITERATOR_ADAPTORS
#define _STD_COPY_ITERATOR_ADAPTORS

#include "type_traits.hpp"
#include "iterator_traits.hpp"
#include "iterator_funcs.hpp"
#include "construct_destroy.hpp"
#include "move.hpp"

#include <cstdint>

namespace std_copy
{
    //std_copy::reverse_iterator
    template <class Iter>
    class reverse_iterator
    {
        private:
            Iter _current;

            typedef std_copy::iterator_traits<Iter> _iter_traits;
            typedef reverse_iterator<Iter>          _reverse_iterator_type;
        public:
            typedef Iter                                iterator_type;
            typedef typename _iter_traits::value_type            value_type;
            typedef typename _iter_traits::difference_type       difference_type;
            typedef typename _iter_traits::pointer               pointer;
            typedef typename _iter_traits::reference             reference;
            using iterator_concept = std_copy::conditional_t<
                                        random_access_iterator<Iter>,
                                        random_access_iterator_tag,
                                        bidirectional_iterator_tag
                                    >;

            //Default constructor
            constexpr reverse_iterator() : _current(Iter()) {}
            
            /**
             * Assigns the underlying iterator to x
             * @param x The iterator to assign the underlying iterator to.
            */
            constexpr explicit reverse_iterator(iterator_type x)
                : _current(x._current) {}

            /**
             * Assigns the underlying iterator to that of other.
             * @param other The reverse_iterator object to assign.
            */
            template <class U>
            constexpr reverse_iterator(const reverse_iterator<U>& other)
                : _current(other._current) {}

            /**
             * Assigns the underlying iterator to that of other.
             * @param other The reverse_iterator object to assign.
            */
            template <class U>
            constexpr _reverse_iterator_type& operator=(const reverse_iterator<U>& other)
            {
                _current = other._current;
                return *this;
            }
            /**
             * Returns the underlying iterator.
            */
            constexpr iterator_type base() const
            {
                return _current;
            }
            /**
             * Returns the value of the element before _current.
            */
            constexpr reference operator*() const
            {
                iterator_type temp = _current;
                return *--temp;
            }
            /**
             * Returns a pointer to the element before _current.
            */
            constexpr pointer operator->() const
            {
                if constexpr(std_copy::is_pointer<Iter>::value)
                    return _current - 1;
                
                return std_copy::prev(_current).operator->();
            }
            /**
             * Returns a reference to the element at the relative specified location.
             * @param n The relative index.
            */
            constexpr reference operator[](difference_type n)
            {
                return *(std_copy::prev(this->base(), n));
            }
            /**
             * Pre-decrements the underlying iterator.
            */
            constexpr _reverse_iterator_type& operator++()
            {
                --_current;
                return *this;
            }
            /**
             * Post-decrements the underlying iterator.
            */
            constexpr _reverse_iterator_type& operator++(int)
            {
                _reverse_iterator_type temp(*this);
                --_current;
                return temp;
            }
            /**
             * Pre-increments the underlying iterator.
            */
            constexpr _reverse_iterator_type& operator--()
            {
                ++_current;
                return *this;
            }
            /**
             * Post-increments the underlying iterator.
            */
            constexpr _reverse_iterator_type& operator--(int)
            {
                _reverse_iterator_type temp(*this);
                ++_current;
                return temp;
            }
            /**
             * Advances the underlying iterator by n positions.
             * @param n The number of positions to advance by.
            */
            constexpr _reverse_iterator_type& operator+=(difference_type n)
            {
                std_copy::advance(_current, -1 * n);
            }
            /**
             * Advances the underlying iterator by -n positions.
             * @param n The number of positions to advance by.
            */
            constexpr _reverse_iterator_type& operator-=(difference_type n)
            {
                std_copy::advance(_current, n);
            }
            /**
             * Returns an iterator which is advanced by n positions.
             * @param n The The number of positions to advance by.
            */
            constexpr _reverse_iterator_type& operator+(difference_type n)
            {
                return std_copy::prev(_current, n);
            }
            /**
             * Returns an iterator which is advanced by -n positions.
             * @param n The The number of positions to advance by.
            */
            constexpr _reverse_iterator_type& operator-(difference_type n)
            {
                return std_copy::next(_current, n);
            }
    };
    
    template <class Iterator1, class Iterator2>
    constexpr bool operator<(const reverse_iterator<Iterator1>& lhs,
                             const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() < rhs.base();
    }

    template <class Iterator1, class Iterator2>
    constexpr bool operator>(const reverse_iterator<Iterator1>& lhs,
                             const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() > rhs.base();
    }

    template <class Iterator1, class Iterator2>
    constexpr bool operator>=(const reverse_iterator<Iterator1>& lhs,
                              const reverse_iterator<Iterator2>& rhs)
    {
        return !(lhs < rhs);
    }

    template <class Iterator1, class Iterator2>
    constexpr bool operator<=(const reverse_iterator<Iterator1>& lhs,
                              const reverse_iterator<Iterator2>& rhs)
    {
        return !(lhs > rhs);
    }

    template <class Iterator1, class Iterator2>
    constexpr bool operator==(const reverse_iterator<Iterator1>& lhs,
                              const reverse_iterator<Iterator2>& rhs)
    {
        return lhs.base() == rhs.base();
    }
    
    template <class Iterator1, class Iterator2>
    constexpr bool operator!=(const reverse_iterator<Iterator1>& lhs,
                              const reverse_iterator<Iterator2>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,
                                         const reverse_iterator<Iterator>& it)
    {
        return std_copy::prev(it.base(), n);
    }

    template <class Iterator>
    auto operator-(const reverse_iterator<Iterator>& it1,
                   const reverse_iterator<Iterator>& it2) -> decltype(it2.base() - it1.base())
    {
        return it2.base() - it1.base();
    }

    template <class Iter>
    constexpr reverse_iterator<Iter> make_reverse_iterator(Iter i)
    {
        return reverse_iterator<Iter>(i);
    }


    //std_copy::back_insert_iterator
    template <class Container>
    class back_insert_iterator
    {
        private:
            typedef back_insert_iterator<Container> _self_type;

        protected:
            Container* _current;

        public:
            typedef output_iterator_tag     iterator_category;
            typedef void                    value_type;
            typedef void                    pointer;
            typedef void                    reference;
            typedef std::ptrdiff_t          difference_type;
            typedef Container               container_type;

            //Initializes the underlying pointer to the container type to c
            explicit constexpr back_insert_iterator(Container& c)
            {
                _current = std_copy::addressof(c);
            }

            //Calls the push_back method of container_type - const lvalue ref
            constexpr _self_type& operator=(const typename Container::value_type& e)
            {
                _current->push_back(e);
                return *this;
            }
            //Calls the push_back method of container_type - rvalue ref
            constexpr _self_type& operator=(typename Container::value_type&& e)
            {
                _current->push_back(std_copy::move(e));
                return *this;
            }

            //No-op overloaded operators. They exist to satisfy LegacyOutputIterator
            constexpr _self_type& operator*() { return *this; }
            constexpr _self_type& operator++() { return *this; }
            constexpr _self_type& operator++(int) { return *this; }

            //Change containers
            constexpr _self_type& set_container(Container& c)
            {
                _current = std_copy::addressof(c);
                return *this;
            }
    };
    //Creates a back_insert_iterator object
    template <class Container>
    back_insert_iterator<Container> back_inserter(Container& c)
    {
        return back_insert_iterator<Container>(c);
    }

    //std_copy::front_insert_iterator
    template <class Container>
    class front_insert_iterator
    {
        private:
            typedef front_insert_iterator<Container> _self_type;

        protected:
            Container* _current;

        public:
            typedef output_iterator_tag     iterator_category;
            typedef void                    value_type;
            typedef void                    pointer;
            typedef void                    reference;
            typedef std::ptrdiff_t          difference_type;
            typedef Container               container_type;

            //Initializes the underlying pointer to the container type to c
            explicit constexpr front_insert_iterator(Container& c)
            {
                _current = std_copy::addressof(c);
            }

            //Calls the push_front method of container_type - const lvalue ref
            constexpr _self_type& operator=(const typename Container::value_type& e)
            {
                _current->push_front(e);
                return *this;
            }
            //Calls the push_front method of container_type - rvalue ref
            constexpr _self_type& operator=(typename Container::value_type&& e)
            {
                _current->push_front(std_copy::move(e));
                return *this;
            }

            //No-op overloaded operators. They exist to satisfy LegacyOutputIterator
            constexpr _self_type& operator*() { return *this; }
            constexpr _self_type& operator++() { return *this; }
            constexpr _self_type& operator++(int) { return *this; }

            //Change containers
            constexpr _self_type& set_container(Container& c)
            {
                _current = std_copy::addressof(c);
                return *this;
            }
    };
    //Creates a front_insert_iterator object
    template <class Container>
    front_insert_iterator<Container> front_inserter(Container& c)
    {
        return front_insert_iterator<Container>(c);
    }

    //std_copy::insert_iterator
    template <class Container>
    class insert_iterator
    {
        private:
            typedef insert_iterator<Container> _self_type;
            typedef typename Container::iterator _iterator_type;

        protected:
            Container* _current;
            _iterator_type _pos;

        public:
            typedef output_iterator_tag     iterator_category;
            typedef void                    value_type;
            typedef void                    pointer;
            typedef void                    reference;
            typedef std::ptrdiff_t          difference_type;
            typedef Container               container_type;

            //Initializes the underlying pointer to the container type to c
            explicit constexpr insert_iterator(Container& c, _iterator_type it)
                : _current(std_copy::addressof(c)),
                _pos(it) 
            {
            }

            //Set new container
            constexpr _self_type& set_container(container_type& c)
            {
                difference_type dist = std_copy::distance(std_copy::begin(c), _pos);
                _current = std_copy::addressof(c);
                _pos = std_copy::next(std::begin(c), dist);
                return *this;
            }

            //Set new iterator position to insert at
            constexpr _self_type& set_position_to_insert_at(_iterator_type newPos)
            {
                _pos = newPos;
                return *this;
            }

            //No-op overloaded operators. They exist to satisfy LegacyOutputIterator
            constexpr _self_type& operator*() { return *this; }
            constexpr _self_type& operator++() { return *this; }
            constexpr _self_type& operator++(int) { return *this; }

            //Calls the push_front method of container_type - const lvalue ref
            constexpr _self_type& operator=(const typename Container::value_type& e)
            {
                _pos = _current->insert(_pos, e);
                ++_pos;
                return *this;
            }
            //Calls the push_front method of container_type - rvalue ref
            constexpr _self_type& operator=(typename Container::value_type&& e)
            {
                _pos = _current->insert(_pos, std_copy::move(e));
                ++_pos;
                return *this;
            }
    };
    //Creates an insert_iterator object
    template <class Container>
    insert_iterator<Container> inserter(Container& c)
    {
        return insert_iterator<Container>(c);
    }
}

#endif /* _STD_COPY_ITERATOR_ADAPTORS */