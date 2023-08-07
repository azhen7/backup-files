#ifndef _STD_COPY_FORWARD_LIST
#define _STD_COPY_FORWARD_LIST

#include "allocator.hpp"
#include "allocator_traits.hpp"
#include <cstdint>

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

        };

        template <class T>
        struct _const_node_iterator
        {
        };
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
            _node_type* _end;
            _node_type* _before_head;

        public:
            
    };
}


#endif /* _STD_COPY_FORWARD_LIST */