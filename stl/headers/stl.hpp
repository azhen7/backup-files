#include <algorithm>
#include <string>
#include <stdexcept>

namespace std_copy {
    template <class T>
    class STL_CONTAINER {
        protected:
            typedef T               value_type;
            typedef T*              pointer;
            typedef T&              reference;
            typedef const T&        const_reference;
            typedef std::size_t     size_type;

            pointer internalBuffer_;
            size_type numberOfElements_;
    };
}
