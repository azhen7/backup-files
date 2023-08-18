#ifndef _STD_COPY_FORWARD_LIST
#define _STD_COPY_FORWARD_LIST

#include "allocator.hpp"
#include "allocator_traits.hpp"
#include "iterator.hpp"
#include "move.hpp"
#include "type_traits.hpp"

#include <cstdint>

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

        template <class T>
        using _is_input_iterator = std_copy::enable_if_t<
            std_copy::is_base_of_v<
                std_copy::input_iterator_tag,
                typename std_copy::iterator_traits<T>::iterator_category
            >
        >;
    };
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
            _node_type* _beforeHead{nullptr};
            size_type _size;

            void _allocate_beforeHead()
            {
                _beforeHead = _node_allocator_type::allocate(1);
                _beforeHead->_next = nullptr;
            }

            void _value_init_list(size_type count, const_reference val)
            {
                if (_beforeHead && _beforeHead->_next)
                {
                    _size = 0;
                    _destroy_list();
                }
                _allocate_beforeHead();
                _beforeHead->_next = _node_allocator_type::allocate(1);
                _beforeHead->_next->_value = val;
                _size = 1;
                
                _node_type* copy = _beforeHead->_next;
                while (count > 1)
                {
                    _node_type* nextElem = _node_allocator_type::allocate(1);
                    nextElem->_init(nullptr, val);
                    copy->_next = nextElem;
                    copy = nextElem;
                    count--;
                    _size++;
                }
            }
            template <class InputIt>
            void _range_init_list(InputIt first, InputIt last)
            {
                if (_beforeHead && _beforeHead->_next)
                {
                    _size = 0;
                    _destroy_list();
                }
                _allocate_beforeHead();
                _beforeHead->_next = _node_allocator_type::allocate(1);
                _beforeHead->_next->_value = *first++;
                _size = 1;

                _node_type* copy = _beforeHead->_next;
                while (first != last)
                {
                    _node_type* nextElem = _node_allocator_type::allocate(1);
                    nextElem->_init(nullptr, *first++);
                    copy->_next = nextElem;
                    copy = nextElem;
                    _size++;
                }
            }
            void _destroy_list()
            {
                _node_type* copy = _beforeHead;
                _node_type* temp = _beforeHead->_next;
                while (_size-- > 0)
                {
                    _beforeHead->_next = _beforeHead->_next->_next;
                    _node_allocator_type::deallocate(temp, 1);
                    temp = _beforeHead->_next;
                }
                _node_allocator_type::deallocate(copy, 1);
                _beforeHead = nullptr;
            }
            template <class ...Args>
            iterator _insert_after_helper(const_iterator pos, Args&& ...args)
            {
                iterator p = _std_copy_hidden::_std_copy_forward_list_iterators::_toUnconstNodeIterator(pos);
                if (pos == this->cbefore_begin())
                {
                    this->push_front(forward<Args>(args)...);
                    return p;
                }
                
                _node_type* newElem = _node_allocator_type::allocate(1);
                newElem->_init(p.base()->_next, value_type(forward<Args>(args)...));
                p.base()->_next = newElem;
                _size++;
                return p;
            }

        public:
            forward_list()
            {
                _allocate_beforeHead();
            }

            explicit forward_list(size_type count, const_reference val)
            {
                _value_init_list(count, val);
            }
            explicit forward_list(size_type count)
            {
                _value_init_list(count, value_type());
            }

            template <typename InputIt/*, typename = _std_copy_hidden::_std_copy_forward_list_iterators::_is_input_iterator<InputIt>*/>
            forward_list(InputIt first, InputIt last)
        #if __cplusplus > 201703L
            requires input_iterator<InputIt>
        #endif
            {
                _range_init_list(first, last);
            }

            forward_list(const forward_list& other)
            {
                _range_init_list(other.begin(), other.end());
            }
            forward_list(forward_list&& other)
                : _beforeHead(move(other._beforeHead))
            {}

            ~forward_list()
            {
                _destroy_list();
            }

            /**
             * Clears the contents of the list.
            */
            void clear() noexcept
            {
                _destroy_list();
            }
            /**
             * Returns true if the list is empty.
            */
            bool empty() const noexcept
            {
                return _beforeHead->_next == nullptr;
            }
            /**
             * Returns iterator to start.
            */
            iterator begin() const noexcept { return iterator(_beforeHead->_next); }
            /**
             * Returns const_iterator to start.
            */
            const_iterator cbegin() const noexcept { return const_iterator(_beforeHead->_next); }
            /**
             * Returns iterator to end.
            */
            iterator end() const noexcept { return iterator(nullptr); }
            /**
             * Returns const_iterator to end.
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
            /**
             * Inserts an element at the front of the container.
             * @param elem The element to insert.
            */
            void push_front(const_reference elem)
            {
                if (_size == 0ULL)
                {
                    _allocate_beforeHead();
                }
                _node_type* newElem = _node_allocator_type::allocate(1);
                newElem->_init(_beforeHead->_next, elem);
                _beforeHead->_next = newElem;
                _size++;
            }
            /**
             * Inserts @var element after @p pos.
             * @param pos The position to insert after.
             * @param element The element to insert.
            */
            iterator insert_after(const_iterator pos, const_reference element)
            {
                return this->_insert_after_helper(pos, element);
            }
            /**
             * Inserts rvalue @var element after @p pos.
             * @param pos The position to insert after.
             * @param element The rvalue element to insert.
            */
            iterator insert_after(const_iterator pos, value_type&& element)
            {
                return this->_insert_after_helper(pos, move(element));
            }
            /**
             * Inserts the range [first, last) after @p pos.
             * @param pos The position to insert after.
             * @param first The start of the range to insert.
             * @param last The end of the range to insert.
            */
            template <class InputIt>
        #if __cplusplus > 201703L
            requires input_iterator<InputIt>
        #endif
            iterator insert_after(const_iterator pos, InputIt first, InputIt last)
            {
                iterator p = _std_copy_hidden::_std_copy_forward_list_iterators::_toUnconstNodeIterator(pos);
                if (first == last) return p;
                
                _node_type* before = p.base();
                _node_type* afterPos = p.base()->_next;
                while (first != last)
                {
                    _node_type* elem = _node_allocator_type::allocate(1);
                    elem->_value = *first++;
                    before->_next = elem;
                    before = elem;
                    _size+;
                }
                before->_next = afterPos;
                return p;
            }
            /**
             * Inserts count instances of element after @p pos.
             * @param pos The position to insert after.
             * @param count The number of elements to insert.
             * @param element The element to insert.
            */
            iterator insert_after(const_iterator pos, size_type count, const_reference element)
            {
                iterator p = _std_copy_hidden::_std_copy_forward_list_iterators::_toUnconstNodeIterator(pos);
                if (count == 0ULL) return p;
                _size += count;
                
                _node_type* before = p.base();
                _node_type* afterPos = p.base()->_next;
                while (count-- > 0)
                {
                    _node_type* elem = _node_allocator_type::allocate(1);
                    elem->_value = element;
                    before->_next = elem;
                    before = elem;
                }
                before->_next = afterPos;
                return p;
            }
            /**
             * Forwards args... to value_type's constructor and inserts that element
             * after @p pos.
             * @param pos The position to insert after.
             * @param args The arguments to forward to the constructor.
            */
            template <class ...Args>
            iterator emplace_after(const_iterator pos, Args&& ...args)
            {
                return this->_insert_after_helper(pos, value_type(forward<Args>(args)...));
            }
            /**
             * Erases the element after @p pos.
             * @param pos An iterator to the element before the element to erase.
            */
            iterator erase_after(const_iterator pos)
            {
                iterator p = _std_copy_hidden::_std_copy_forward_list_iterators::_toUnconstNodeIterator(pos);
                if (p.base()->_next == nullptr) return this->end();

                _node_type* node = p.base();
                _node_type* nextNext = p.base()->_next->_next;
                _node_allocator_type::deallocate(node->_next, 1);
                node->_next = nextNext;
                _size--;
                return p;
            }

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