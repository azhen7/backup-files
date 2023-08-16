#ifndef _STD_COPY_FORWARD_LIST
#define _STD_COPY_FORWARD_LIST

#include "allocator.hpp"
#include "allocator_traits.hpp"
#include <cstdint>
#include "iterator.hpp"
#include "move.hpp"

#define _STD_COPY_FORWARD_LIST_DEBUG_PRINT 1

#if _STD_COPY_FORWARD_LIST_DEBUG_PRINT
    #include <iostream>
#endif

namespace _std_copy_hidden
{
    namespace _std_copy_forward_list_iterators
    {
        template <class _T>
        struct _node
        {
            private:
                typedef _node<_T> _self_type;

            public:
                _self_type* _next;
                _T _value;

                void _init(_self_type* n, const _T& v)
                {
                    _value = v;
                    _next = n;
                }
        };

        template <class T>
        struct _node_iterator
        {
            private:
                typedef _node<T> _node_type;
                typedef _node_iterator<T> _self_type;
                _node_type* _curr;
            
            public:
                typedef std::ptrdiff_t difference_type;
                typedef std_copy::forward_iterator_tag iterator_category;
                typedef T value_type;
                typedef T& reference;
                typedef T* pointer;

                _node_iterator(_node_type* c)
                    : _curr(c)
                {
                }

                _self_type operator++() noexcept
                {
                    _curr = _curr->_next;
                    return *this;
                }
                _self_type operator++(int) noexcept
                {
                    _self_type temp = *this;
                    _curr = _curr->_next;
                    return temp;
                }
                T& operator*() const noexcept
                {
                    return _curr->_value;
                }
                _node_type* base() const noexcept
                {
                    return _curr;
                }
                void operator=(const _self_type& l) noexcept
                {
                    _curr = l._curr;
                }
                friend bool operator==(const _self_type& a, const _self_type& l)
                {
                    return a._curr == l._curr;
                }
                friend bool operator!=(const _self_type& a, const _self_type& l)
                {
                    return !(a == l);
                }
        };

        template <class T>
        struct _const_node_iterator
        {
            private:
                typedef const _node<T> _node_type;
                typedef _const_node_iterator<T> _self_type;
                const _node_type* _curr;

            public:
                typedef std::ptrdiff_t difference_type;
                typedef std_copy::forward_iterator_tag iterator_category;
                typedef T value_type;
                typedef const T& reference;
                typedef const T* pointer;

                _const_node_iterator(const _node_type *e)
                    : _curr(e)
                {
                }

                _const_node_iterator() : _curr() {}

                template <class _T>
                _const_node_iterator(const _node_iterator<_T>& n)
                    : _curr(n.base())
                {
                }

                _self_type operator++() noexcept
                {
                    _curr = _curr->_next;
                    return *this;
                }
                _self_type operator++(int) noexcept
                {
                    _self_type temp = *this;
                    _curr = _curr->_next;
                    return temp;
                }
        
                T& operator*() const noexcept
                {
                    return _curr->_value;
                }
                _node_type* base() const noexcept
                {
                    return _curr;
                }
                void operator=(const _node_iterator<T> &l) noexcept
                {
                    _curr = l._curr;
                }
                friend bool operator==(const _self_type& a, const _self_type& l)
                {
                    return a._curr == l._curr;
                }
                friend bool operator!=(const _self_type& a, const _self_type& l)
                {
                    return !(a == l);
                }
        };

        template <class T>
        _node_iterator<T> _toUnconstNodeIterator(_const_node_iterator<T> s)
        {
            return _node_iterator<T>(const_cast<_node<T>*>(s.base()));
        }
    }
};

namespace std_copy
{
    /**
     * An implementation of std::forward_list, defined in the header file <forward_list>.
     * @param T The type of the elements.
     * @param Alloc The type of the object used to allocate the underlying buffer
     * used for containing the values.
     */
    template <class T, class Alloc = allocator<T>>
    class forward_list
    {
        private:
            typedef forward_list<T, Alloc>                                              _forward_list_type;
            typedef _std_copy_hidden::_std_copy_forward_list_iterators::_node<T>        _node_type;
            typedef typename allocator_traits<Alloc>::rebind_alloc<_node_type>          _node_allocator_type;

        public:
            typedef T                                                                   value_type;
            typedef Alloc                                                               allocator_type;
            typedef T&                                                                  reference;
            typedef const T&                                                            const_reference;
            typedef allocator_traits<Alloc>::pointer                                    pointer;
            typedef allocator_traits<Alloc>::const_pointer                              const_pointer;
            typedef std::size_t                                                         size_type;
            typedef std::ptrdiff_t                                                      difference_type;
            typedef _std_copy_hidden::_std_copy_forward_list_iterators::_node_iterator<T> iterator;
            typedef _std_copy_hidden::_std_copy_forward_list_iterators::_const_node_iterator<T> const_iterator;

        private:
            _node_type* _head;
            _node_type* _tail;
            _node_type* _beforeHead;
            size_type _size;

            void _add_before_begin_and_end_ptrs()
            {
                _beforeHead = _node_allocator_type::allocate(1);
                _beforeHead->_next = _head;

                _tail->_next = nullptr; //operator-- is not defined (forward_list::iterator isn't bidirectional) so we can cheat using nullptr
            }
            void _value_init_list(size_type count, const_reference val)
            {
                _size = 1;
                _head = _node_allocator_type::allocate(1);
                _head->_value = val;
                _node_type* copy = _head;

                while (count > 1)
                {
                    _node_type* nextElem = _node_allocator_type::allocate(1);
                    nextElem->_value = val;
                    copy->_next = nextElem;
                    copy = nextElem;
                    count--;
                    _size++;
                }
                _tail = copy;
                _add_before_begin_and_end_ptrs();
            }
            template <class InputIt>
            void _range_init_list(InputIt first, InputIt last)
            {
                _size = 1;
                _head = _node_allocator_type::allocate(1);
                _head->_value = *first++;
                _node_type* copy = _head;

                while (first != last)
                {
                    _node_type* nextElem = _node_allocator_type::allocate(1);
                    nextElem->_value = *first++;
                    copy->_next = nextElem;
                    copy = nextElem;
                    _size++;
                }
                _tail = copy;
                _add_before_begin_and_end_ptrs();
            }
            void _destroy_list()
            {
                _node_type* temp = _head;
                while (_size > 0)
                {
                    _head = _head->_next;
                    _node_allocator_type::deallocate(temp, 1);
                    temp = _head;

                    _size--;
                }
                _head = nullptr;
                _tail = nullptr;
            }

        public:
            forward_list() : _size(0)
            {
            }

            forward_list(size_type count, const_reference val)
            {
                _value_init_list(count, val);
            }
            forward_list(size_type count)
            {
                _value_init_list(count, value_type());
            }

            template <class InputIt>
            forward_list(InputIt first, InputIt last)
            {
                _range_init_list(first, last);
            }

            forward_list(const forward_list& other)
            {
                _range_init_list(other.begin(), other.end());
            }
            forward_list(forward_list&& other)
                : _head(move(other._head)),
                _tail(move(other._tail)),
                _beforeHead(move(other._beforeHead)),
                _size(move(other._size))
            {}

            ~forward_list()
            {
                _destroy_list();
            }

            /**
             * Clears the contents of the list.
            */
            void clear()
            {
                _destroy_list();
            }
            /**
             * Returns iterator to start
            */
            iterator begin() const noexcept { return iterator(_head); }
            /**
             * Returns const_iterator to start
            */
            const_iterator cbegin() const noexcept { return const_iterator(_head); }
            /**
             * Returns iterator to end
            */
            iterator end() const noexcept { return iterator(nullptr); }
            /**
             * Returns const_iterator to end
            */
            const_iterator cend() const noexcept { return const_iterator(nullptr); }
            /**
             * Returns iterator to hypothetical element before start.
            */
            iterator before_begin() const noexcept { return iterator(_beforeHead); }
            /**
             * Returns const_iterator to hypothetical element before start.
            */
            const_iterator cbefore_begin() const noexcept { return const_iterator(_beforeHead); }

        #if _STD_COPY_FORWARD_LIST_DEBUG_PRINT

            void _debug_print() const noexcept
            {
                for (auto it = begin(); it != end(); it++)
                {
                    std::cout << *it << ' ';
                }
                std::cout << '\n';
            }

        #endif
    };
}


#endif /* _STD_COPY_FORWARD_LIST */