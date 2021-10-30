#ifndef _STD_COPY_CHAR_TRAITS
#define _STD_COPY_CHAR_TRAITS

namespace std_copy
{
    template <class CharT>
    class char_traits
    {
        public:
            using char_type     =       CharT;
            using int_type      =       unsigned long long;
    };
}

#endif