#ifndef _STD_COPY_LIST
#define _STD_COPY_LIST

#include "allocator.hpp"
#include "allocator_traits.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include "functional_comp.hpp"
#include "_list_iterators.hpp"
#include <cstdint>
#include <stdexcept>

#define _STD_COPY_LIST_DEBUG_PRINT 1

#if _STD_COPY_LIST_DEBUG_PRINT
#include <iostream> 
#endif

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
        protected:
            typedef list<T, Alloc>                                              _list_type;
            typedef _std_copy_hidden::_std_copy_list_iterators::_node<T>        _node_type;
            typedef allocator<_node_type>                                       _node_allocator_type;

        public:
            typedef T                                                           value_type;
            typedef T&                                                          reference;
            typedef const T&                                                    const_reference;
            typedef allocator_traits<Alloc>::pointer                            pointer;
            typedef allocator_traits<Alloc>::const_pointer                      const_pointer;
            typedef Alloc                                                       allocator_type;
            typedef _std_copy_hidden::_std_copy_list_iterators::_node_iterator<T> iterator;
            typedef _std_copy_hidden::_std_copy_list_iterators::_const_node_iterator<T> const_iterator;
            typedef std_copy::reverse_iterator<iterator>                        reverse_iterator;
            typedef std_copy::reverse_iterator<const_iterator>                  const_reverse_iterator;
            typedef std::size_t                                                 size_type;
            typedef std::ptrdiff_t                                              difference_type;

        private:
            void _build_this_from_existing(_node_type *src, _node_type* src_end)
            {
                if (src == src_end)
                {
                    _tail = _node_allocator_type::allocate(1);
                    _head = _tail;
                    _tail->_next = _tail;
                    return;
                }

                _head = _node_allocator_type::allocate(1);
                _node_type* n = _head;
                while (src != src_end)
                {
                    n->_value = src->_value;
                    src = src->_next;
                    
                    n->_next = _node_allocator_type::allocate(1);
                    n->_next->_prev = n;
                    _tail = n;
                    n = n->_next;
                }
            }
            
            void _add_new_end_ptr()
            {
                _tail->_next = _node_allocator_type::allocate(1);
                _tail->_next->_prev = _tail;
            }

            void _link_nodes(_node_type* before, _node_type* after)
            {
                before->_next = after;
                after->_prev = before;
            }

            template <class InputIt>
            void _range_init_list(InputIt first, InputIt last)
            {
                if (_head)
                {
                    _destroy_list();
                    _head = _node_allocator_type::allocate(1);
                }
                
                _size = distance(first, last);

                _head->_value = *first;

                _node_type *tempHead = _head;
                _size = 1;

                _tail = tempHead;
                ++first;
                while (first != last)
                {
                    if (_size == size_type(-1))
                        throw std::length_error("Range is too large");
                    _node_type *attach = _node_allocator_type::allocate(1);

                    attach->_prev = tempHead;
                    attach->_value = *first;

                    tempHead->_next = attach;
                    tempHead = tempHead->_next;

                    _size++;
                    first++;
                    _tail = tempHead;
                }
                _add_new_end_ptr();
            }
            void _value_init_list(size_type count, const_reference val)
            {
                if (_head)
                {
                    _destroy_list();
                    _head = _node_allocator_type::allocate(1);
                }

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
                    _size++;
                    _tail = tempHead;
                }
                _add_new_end_ptr();
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

            // Funtions used for appending elements (e.g. push_front, push_back, insert, etc.)
            bool _check_if_empty(const_reference val)
            {
                if (_size == 0)
                {
                    _head = _node_allocator_type::allocate(1);
                    _head->_value = val;
                    _tail = _head;

                    _add_new_end_ptr();

                    _size = 1;
                    return true;
                }
                return false;
            }
            
            void _resize(size_type count, const_reference val)
            {
                if (count > _size)
                {
                    size_type leftExcludingEnd = count - _size - 1;

                    _tail = _tail->_next;
                    _tail->_value = val;

                    while (leftExcludingEnd-- > 0)
                    {
                        _node_type* it = _node_allocator_type::allocate(1);

                        _link_nodes(_tail, it);

                        it->_value = val;
                        _tail = _tail->_next;
                    }
                }
                else
                {
                    _node_allocator_type::deallocate(_tail->_next, 1);
                    size_type left = _size - count;
                    while (left-- > 0)
                    {
                        _tail = _tail->_prev;
                        _node_allocator_type::deallocate(_tail->_next, 1);
                    }
                }
                _size = count;
                _add_new_end_ptr();
            }

            template <class Function>
            size_type _remove(Function compare)
            {
                _node_type* temp = _head;

                size_type currIndex = 0;
                const size_type sizeRecord = _size;
                while (currIndex < sizeRecord)
                {
                    if (compare(temp->_value))
                    {
                        _node_type* nextNext = temp->_next;
                        temp = temp->_prev;
                        
                        _node_allocator_type::deallocate(temp->_next, 1);
                        _link_nodes(temp, nextNext);

                        _size--;
                    }
                    _tail = temp;
                    temp = temp->_next;
                    currIndex++;
                }
                _node_allocator_type::deallocate(_tail->_next, 1);
                _add_new_end_ptr();
                return sizeRecord - _size;
            }
            void _remove_elem_and_clear()
            {
                _size = 0;

                _node_allocator_type::deallocate(_tail, 1);
                _tail = _tail->_next;
                _tail->_next = _tail;
                _head = _tail;
            }

            _node_type* _head;
            _node_type* _tail;
            size_type _size;

        public:
            list() : _size(0)
            {
            }

            explicit list(size_type count, const_reference val)
                : _size(0)
            {
                _value_init_list(count, val);
            }

            explicit list(size_type count)
                : _size(0)
            {
                _value_init_list(count, value_type());
            }

            template <class InputIt>
            list(InputIt first, InputIt last)
    #if __cplusplus > 201703L
                requires input_iterator<InputIt>
    #endif
                : _size(0)
            {
                _range_init_list(first, last);
            }

            list(_list_type&& other)
                : _size(move(other._size)),
                _head(move(other._head)),
                _tail(move(other._tail))
            {
            }

            list(const _list_type &other)
                : _size(other._size)
            {
                _build_this_from_existing(other._head, other._tail->_next);
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
                if (_check_if_empty(elem)) return;

                _node_type* newTail = _node_allocator_type::allocate(1);

                _link_nodes(newTail, _tail->_next);
                _link_nodes(_tail, newTail);

                _tail->_next->_value = elem;

                _tail = _tail->_next;
                _size++;
            }
            /**
             * Pushes an element to the beginning of the list.
             * @param elem The element to push to the beginning.
             */
            void push_front(const_reference elem)
            {
                if (_check_if_empty(elem)) return;

                _node_type* a = _node_allocator_type::allocate(1);

                _link_nodes(a, _head);

                a->_value = elem;

                _head = _head->_prev;
                _size++;
            }
            /**
             * Removes the first element.
             */
            void pop_front()
            {
                if (_size == 1)
                {
                    _remove_elem_and_clear();
                    return;
                }

                _head = _head->_next;
                _node_allocator_type::deallocate(_head->_prev, 1);
                _size--;
            }
            /**
             * Removes the last element.
             */
            void pop_back()
            {
                if (_size == 1)
                {
                    _remove_elem_and_clear();
                    return;
                }

                _node_type* end = _tail->_next;
                _tail = _tail->_prev;
                end->_prev = _tail;

                _node_allocator_type::deallocate(_tail->_next, 1);

                _tail->_next = end;
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
            iterator end() const noexcept { return iterator(_tail->_next); }
            /**
             * Returns const iterator to end of list.
             */
            const_iterator cend() const noexcept { return const_iterator(_tail->_next); }
            /**
             * Returns reverse iterator to beginning of list.
             */
            reverse_iterator rbegin() const noexcept { return reverse_iterator(_head); }
            /**
             * Returns reverse iterator to beginning of list.
             */
            reverse_iterator rend() const noexcept { return reverse_iterator(_tail->_next); }
            /**
             * Returns constant reverse iterator to beginning of list.
             */
            const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(_head); }
            /**
             * Returns constant reverse iterator to end of list.
             */
            const_reverse_iterator crend() const noexcept { return const_reverse_iterator(_tail->_next); }
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
                
                //link the _next reference of the element two elements before @var pos to @var newElem
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
            iterator erase(iterator pos) noexcept
            {
                if (pos.base() == this->end())
                {
                    this->pop_back();
                    return this->end();
                }
                else if (pos.base() == this->begin())
                {
                    this->pop_front();
                    return this->begin();
                }
                
                _node_type* rawIt = pos.base();
                if (rawIt == _tail)
                {
                    _tail = _tail->_prev;
                }

                rawIt->_prev->_next = rawIt->_next;
                _node_type* nextIt = rawIt->_next;

                _node_allocator_type::deallocate(rawIt, 1);
                _size--;

                return nextIt;
            }
            /**
             * Erases the elements in the range [start, end)
             * @param start The start of the range of values to erase.
             * @param end The end of the range of values to erase.
             */
            iterator erase(iterator start, iterator end) noexcept
            {
                if (start == end) return end;

                _node_type* beforeStart = start.base()->_prev;
                _node_type* afterStart = start.base()->_next;
                _node_type* curr = start.base();

                while (curr != end.base())
                {
                    _node_allocator_type::deallocate(curr, 1);
                    curr = afterStart;
                    afterStart = afterStart->_next;
                    _size--;
                }

                _link_nodes(beforeStart, end.base());

                return end;
            }
            /**
             * Resizes the list to contain @p count elements. If @p count is greater than the
             * current size of the list, additional default-inserted elements are appended.
             * @param count The new size to resize the list to.
             */
            void resize(size_type count) noexcept
            {
                _resize(count, value_type());
            }
            /**
             * Resizes the list to contain @p count elements. If @p count is greater than the
             * current size of the list, additional copies of @p val are appended.
             * @param count The new size to resize the list to.
             * @param val The value that gets appended.
             */
            void resize(size_type count, const_reference val) noexcept
            {
                _resize(count, val);
            }
            /**
             * Removes all elements equal to @p val.
             * @param val The value to remove.
             */
            size_type remove(const_reference val) noexcept
            {
                return _remove(bind1st(equal_to<value_type>(), val));
            }
            /**
             * Removes all elements for which @p func returns true.
             * @param func The function determining which elements to remove.
             */
            template <class Function>
            size_type remove_if(Function func)
            {
                return _remove(func);
            }
            /**
             * Reverses the current list.
             */
            void reverse() noexcept
            {
                std_copy::reverse(this->begin(), this->end());
            }
            /**
             * Removes consecutive duplicate elements.
             */
            void unique() noexcept
            {
                auto newEnd = std_copy::unique(this->begin(), this->end());
                this->erase(newEnd, this->end());
            }

    #if _STD_COPY_LIST_DEBUG_PRINT

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

#endif /* _STD_COPY_LIST */