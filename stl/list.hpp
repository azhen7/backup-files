#ifndef _STD_COPY_LIST
#define _STD_COPY_LIST

#include "allocator.hpp"
#include "allocator_traits.hpp"
#include "iterator.hpp"
#include "move.hpp"
#include "algorithm.hpp"
#include "functional_comp.hpp"
#include <cstdint>
#include <stdexcept>

#define _DEBUG 1

#if _DEBUG
#include <iostream>
#include <list>
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-local-addr"

namespace _std_copy_hidden
{
    namespace _std_copy_list
    {
        template <class _Type>
        struct _node
        {
            private:
                typedef _node<_Type> _self_type;

            public:
                _self_type *_next;
                _self_type *_prev;

                _Type _value;

                void _init(_self_type* p, _self_type* n, const _Type& val)
                {
                    _prev = p;
                    _next = n;
                    _value = std_copy::move(val);
                }
        };

        template <class T>
        T& _generate_garbage_val() {
            T* t = new T;
            T& val = *t;
            delete t;
            return val;
        }

        template <class _T>
        struct _node_iterator
        {
            private:
                typedef _node<_T> _node_type;
                typedef _node_iterator<_T> _self_type;
                _node_type* _curr;

            public:
                typedef std::ptrdiff_t difference_type;
                typedef std_copy::bidirectional_iterator_tag iterator_category;
                typedef _T value_type;
                typedef _T& reference;
                typedef _T* pointer;

                _node_iterator(_node_type* e)
                    : _curr(e)
                {
                }

                _self_type operator++()
                {
                    _curr = _curr->_next;
                    return *this;
                }
                _self_type operator++(int)
                {
                    _self_type temp = *this;
                    _curr = _curr->_next;
                    return temp;
                }
                _self_type operator--()
                {
                    _curr = _curr->_prev;
                    return *this;
                }
                _self_type operator--(int)
                {
                    _self_type temp = *this;
                    _curr = _curr->_prev;
                    return temp;
                }
                _T& operator*()
                {
                    return _curr->_value;
                }
                _node_type* base()
                {
                    return _curr;
                }
                void operator=(const _self_type& l)
                {
                    _curr = l._curr;
                }
                bool operator==(const _self_type& l)
                {
                    return _curr == l._curr;
                }
                bool operator!=(const _self_type& l)
                {
                    return !(*this == l);
                }
        };


        template <class _T>
        struct _const_node_iterator
        {
            private:
                typedef const _node<_T> _node_type;
                typedef _const_node_iterator<_T> _self_type;
                const _node_type* _curr;
                const _node_type* _prev;

            public:
                typedef std::ptrdiff_t difference_type;
                typedef std_copy::bidirectional_iterator_tag iterator_category;
                typedef _T value_type;
                typedef const _T& reference;
                typedef const _T* pointer;

                _const_node_iterator(_node_type *e, _node_type* p)
                    : _curr(e)
                {
                    if (p && !e) _prev = p;
                }

                _self_type operator++()
                {
                    _curr = _curr->_next;
                    return *this;
                }
                _self_type operator++(int)
                {
                    _self_type temp = *this;
                    _curr = _curr->_next;
                    return temp;
                }
                _self_type operator--()
                {
                    _curr = _curr->_prev;
                    return *this;
                }
                _self_type operator--(int)
                {
                    _self_type temp = *this;
                    _curr = _curr->_prev;
                    return temp;
                }
        
                _T& operator*()
                {
                    return _curr->_value;
                }
                _node_type* base()
                {
                    return _curr;
                }
                void operator=(const _node_iterator<_T> &l)
                {
                    _curr = l._curr;
                }
                bool operator==(const _node_iterator<_T> &l)
                {
                    return _curr == l._curr;
                }
                bool operator!=(const _node_iterator<_T> &l)
                {
                    return !(*this == l);
                }
        };
    }
};

#pragma GCC diagnostic pop

namespace std_copy
{
    /**
     * An implementation of std::list from the header <list>.
     * @param T The type of the elements.
     * @param Alloc The allocator used to allocate new elements.
     */
    template <class T, class Alloc = std_copy::allocator<T>>
    class list
    {
        private:
            typedef list<T, Alloc>                                              _list_type;
            typedef _std_copy_hidden::_std_copy_list::_node<T>                  _node_type;
            typedef allocator<_node_type>                                       _node_allocator_type;

        public:
            typedef T                                                           value_type;
            typedef T&                                                          reference;
            typedef const T&                                                    const_reference;
            typedef allocator_traits<Alloc>::pointer                            pointer;
            typedef allocator_traits<Alloc>::const_pointer                      const_pointer;
            typedef Alloc                                                       allocator_type;
            typedef _std_copy_hidden::_std_copy_list::_node_iterator<T>         iterator;
            typedef _std_copy_hidden::_std_copy_list::_const_node_iterator<T>   const_iterator;
            typedef std_copy::reverse_iterator<iterator>                        reverse_iterator;
            typedef std_copy::reverse_iterator<const_iterator>                  const_reverse_iterator;
            typedef std::size_t                                                 size_type;
            typedef std::ptrdiff_t                                              difference_type;

        private:
            _node_type *_head{nullptr};
            _node_type *_tail{nullptr};
            size_type _size;

            void _copy_list(_node_type *dest, _node_type *src)
            {
                while (src)
                {
                    dest->_value = src->_value;
                    src = src->_next;
                    dest = dest->_next;
                }
            }
            template <class InputIt>
            void _range_init_list(InputIt first, InputIt last)
            {
                if (!_head)
                    _head = _node_allocator_type::allocate(1);
                
                _size = distance(first, last);

                _head->_value = *first;

                _node_type *tempHead = _head;
                _size = 1;

                _tail = tempHead;
                ++first;
                while (first != last)
                {
                    if (_size == size_type(-1))
                        throw std::length_error("Range is too long");
                    _node_type *attach = _node_allocator_type::allocate(1);

                    attach->_prev = tempHead;
                    attach->_value = *first;

                    tempHead->_next = attach;
                    tempHead = tempHead->_next;

                    ++_size;
                    ++first;
                    _tail = tempHead;
                }
            }
            void _value_init_list(size_type count, const_reference val)
            {
                if (!_head)
                    _head = _node_allocator_type::allocate(1);

                _head->_value = val;

                _node_type *tempHead = _head;
                _tail = tempHead;
                while (count > 1)
                {
                    _node_type *attach = _node_allocator_type::allocate(1);

                    attach->_prev = tempHead;
                    attach->_value = val;

                    tempHead->_next = attach;
                    tempHead = tempHead->_next;

                    count--;
                    _tail = tempHead;
                }
            }
            void _destroy_list()
            {
                // _node_type *previous = _head->_prev;
                // while (_head)
                // {
                //     if (previous)
                //         _node_allocator_type::deallocate(previous, 1);

                //     _head->_value.~value_type();
                //     previous = _head;
                //     _head = _head->_next;
                // }
                // _node_allocator_type::deallocate(previous, 1);
                // _head = nullptr;
                // _size = 0;
                _node_type* temp = _head;
                while (_size > 0)
                {
                    _head = _head->_next;
                    _node_allocator_type::deallocate(temp, 1);
                    temp = _head;
                    _size--;
                }
                _head = nullptr;
            }

            // Funtions used for appending elements (e.g. push_front, push_back, insert, etc.)
            bool _check_if_empty(const_reference val)
            {
                if (!_head)
                {
                    _head = _node_allocator_type::allocate(1);
                    _head->_value = val;
                    _tail = _head;
                    _size = 1;
                    return true;
                }
                return false;
            }
            // _node_type* __end_check_if_nullptr() const noexcept
            // {
            //     return _tail ? _tail->_next : nullptr;
            // }
            
            void __resize(size_type count, const_reference val)
            {
                if (count > _size)
                {
                    size_type left = count - _size;
                    while (left-- > 0)
                    {
                        _node_type* it = _node_allocator_type::allocate(1);

                        it->_prev = _tail;
                        it->_value = val;

                        _tail->_next = it;
                        _tail = _tail->_next;
                    }
                }
                else
                {
                    size_type left = _size - count;
                    while (left-- > 0)
                    {
                        _tail = _tail->_prev;
                        _node_allocator_type::deallocate(_tail->_next, 1);
                    }
                }
            }

            template <class Function>
            size_type __remove(Function compare)
            {
                size_type numberOfRemoved = 0;
                _node_type* temp = _head;
                while (temp)
                {
                    if (compare(temp->_value))
                    {
                        temp = temp->_prev;
                        _node_type* nextNext = temp->_next->_next;
                        _node_allocator_type::deallocate(temp->_next, 1);
                        temp->_next = nextNext;

                        if (nextNext)
                        {
                            nextNext->_prev = temp;
                        }

                        _size--;
                        numberOfRemoved++;
                    }
                    _tail = temp;
                    temp = temp->_next;
                }
                return numberOfRemoved;
            }

        public:
            list() : _size(0)
            {
                _head = nullptr;
            }

            explicit list(size_type count, const_reference val)
                : _size(count)
            {
                _value_init_list(count, val);
            }

            explicit list(size_type count)
                : _size(count)
            {
                _value_init_list(count, value_type());
            }

            template <class InputIt>
            list(InputIt first, InputIt last)
    #if __cplusplus > 201703L
                requires input_iterator<InputIt>
    #endif
            {
                _range_init_list(first, last);
            }

            list(_list_type &&other)
                : _size(move(other._size)),
                _head(move(other._head))
            {
            }

            list(const _list_type &other)
                : _size(other._size)
            {
                _copy_list(_head, other._head);
            }

            ~list()
            {
                _destroy_list();
            }

            /**
             * Clears the contents of the list.
             */
            void clear() noexcept
            {
                _destroy_list();
                _size = 0;
                _tail = nullptr;
            }
            /**
             * Returns the number of elements in the list.
             */
            size_type size() const noexcept
            {
                return _size;
            }
            /**
             * Appends an element onto the end of the list.
             * @param elem The element to append.
             */
            void push_back(const_reference elem)
            {
                if (_check_if_empty(elem))
                {
                    return;
                }
                _tail->_next = _node_allocator_type::allocate(1);
                _tail->_next->_init(_tail, nullptr, elem);
                _tail = _tail->_next;
                _size++;
            }
            /**
             * Pushes an element to the beginning of the list.
             * @param elem The element to push to the beginning.
             */
            void push_front(const_reference elem)
            {
                if (_check_if_empty(elem))
                {
                    return;
                }
                _head->_prev = _node_allocator_type::allocate(1);
                _head->_prev->_init(nullptr, _head, elem);
                _head = _head->_prev;
                _size++;
            }
            /**
             * Removes the first element.
             */
            void pop_front()
            {
                _head = _head->_next;
                _node_allocator_type::deallocate(_head->_prev, 1);
                _head->_prev = nullptr;
                _size--;
            }
            /**
             * Removes the last element.
             */
            void pop_back()
            {
                _tail = _tail->_prev;
                _node_allocator_type::deallocate(_tail->_next, 1);
                _tail->_next = nullptr;
                _size--;
            }
            /**
             * Returns iterator to beginning of list.
             */
            iterator begin() const noexcept { return iterator(_head); }
            /**
             * Returns const iterator to beginning of list.
             */
            const_iterator cbegin() const noexcept { return const_iterator(_head); }
            /**
             * Returns iterator to end of list.
             */
            iterator end() const noexcept { return iterator(_tail); }
            /**
             * Returns const iterator to end of list.
             */
            const_iterator cend() const noexcept { return const_iterator(_tail); }
            /**
             * Returns reverse iterator to beginning of list.
             */
            reverse_iterator rbegin() const noexcept { return reverse_iterator(_head); }
            /**
             * Returns reverse iterator to beginning of list.
             */
            reverse_iterator rend() const noexcept { return reverse_iterator(_tail); }
            /**
             * Returns constant reverse iterator to beginning of list.
             */
            const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(_head); }
            /**
             * Returns constant reverse iterator to end of list.
             */
            const_reverse_iterator crend() const noexcept { return const_reverse_iterator(_tail); }
            /**
             * Inserts an element at @p pos.
             * @param pos The position to insert the element at.
             * @param elem The element to insert.
             */
            iterator insert(iterator pos, const_reference elem)
            {
                if (pos == this->end())
                {
                    this->push_back(elem);
                    return pos;
                }
                else if (pos == this->begin())
                {
                    this->push_front(elem);
                    return pos;
                }

                _size++;

                _node_type* newElem = _node_allocator_type::allocate(1);
                newElem->_init(pos.base()->_prev, pos.base(), elem);
                pos.base()->_prev = newElem;
                if (pos.base()->_prev->_prev)
                {
                    pos.base()->_prev->_prev->_next = newElem;
                }
                return pos;
            }
            /**
             * Inserts an element at @p pos.
             * @param pos The position to insert the element at.
             * @param args The arguments that are forwarded to the element's type's constructor.
             */
            template <class... Args>
            iterator emplace(iterator pos, Args &&...args)
            {
                return this->insert(pos, value_type(args...));
            }
            /**
             * Inserts an element at the end of the list.
             * @param args The arguments that are forwarded to the element's type's constructor.
             */
            template <class... Args>
            reference emplace_back(Args &&...args)
            {
                this->push_back(value_type(args...));
                return _tail->_value;
            }
            /**
             * Inserts an element at the beginning of the list.
             * @param args The arguments that are forwarded to the element's type's constructor.
             */
            template <class... Args>
            reference emplace_front(Args &&...args)
            {
                this->push_front(value_type(args...));
                return _head->_value;
            }
            /**
             * Erases the element at @p pos.
             * @param pos The position of the element to erase.
             */
            iterator erase(iterator pos)
            {
                if (pos.base() == _tail)
                {
                    this->pop_back();
                    return this->end();
                }
                else if (pos.base() == _head)
                {
                    this->pop_front();
                    return this->begin();
                }
                _node_type* nextIt;

                _node_type* rawIt = pos.base();
                (rawIt->_prev)->_next = rawIt->_next;
                nextIt = rawIt->_next;
                _node_allocator_type::deallocate(rawIt, 1);
                _size--;

                return nextIt;
            }
            /**
             * Resizes the list to contain @p count elements. If @p count is greater than the
             * current size of the list, additional default-inserted elements are appended.
             * @param count The new size to resize the list to.
             */
            void resize(size_type count) noexcept
            {
                __resize(count, value_type());
            }
            /**
             * Resizes the list to contain @p count elements. If @p count is greater than the
             * current size of the list, additional copies of @p val are appended.
             * @param count The new size to resize the list to.
             * @param val The value that gets appended.
             */
            void resize(size_type count, const_reference val) noexcept
            {
                __resize(count, val);
            }
            /**
             * Removes all elements equal to @p val.
             * @param val The value to remove.
             */
            size_type remove(const_reference val)
            {
                return __remove(bind1st(equal_to<value_type>(), val));
            }
            /**
             * Removes all elements for which @p func returns true.
             * @param func The function determing which elements to remove.
             */
            template <class Function>
            size_type remove_if(Function func)
            {
                return __remove(func);
            }
            /**
             * Reverses the current list.
             */
            void reverse() noexcept
            {
                std_copy::reverse(this->begin(), this->end());
            }

    #if _DEBUG

            void _debug_print()
            {
                _node_type *temp = _head;
                while (temp)
                {
                    std::cout << temp->_value << ' ';
                    temp = temp->_next;
                }
                std::cout << '\n';
            }

    #endif
    };
}

#endif /* _STD_COPY_LIST */