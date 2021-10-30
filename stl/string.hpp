#ifndef _STD_COPY_STRING
#define _STD_COPY_STRING

#include "allocator.hpp"
#include "iterator.hpp"

namespace std
{
    template <class CharT, class Alloc = std_copy::allocator<CharT>>
    class basic_string
    {
        private:
            typedef basic_string<CharT, Alloc>      basic_string_type;
            typedef iterator<basic_string_type>     iterator_type;

        public:
            using value_type        =       CharT;
            using allocator_type    =       Alloc;
            using size_type         =       std_copy::allocator_traits<Alloc>::size_type;
            using difference_type   =       std_copy::allocator_traits<Alloc>::difference_type;
            using reference         =       value_type&;
            using const_reference   =       const reference;
            using pointer           =       std_copy::allocator_traits<Alloc>::pointer;
            using const_pointer     =       const pointer;
            using iterator          =       iterator_type;
            using const_iterator    =       const iterator;

        private:
            pointer internalString_;
            size_type length_;
            size_type capacity_;
            allocator_type allocator;
        
        public:
            basic_string()
                : length_(0),
                capacity_(0),
                internalString_(nullptr)
            {
            }

            
    };
}

#endif