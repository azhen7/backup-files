#ifndef _STD_COPY_CONSTRUCT_DESTROY
#define _STD_COPY_CONSTRUCT_DESTROY

namespace std_copy
{
    /**
     * This function returns the actual address of an object referenced 
     * by val, even in the presence of an overloaded operator&.
     * @param f The object to return the actual address of.
    */
    template <class T>
    T* addressof(T& f)
    {
        return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(f)));
    }
    /**
     * Constructs an object at a particular location in memory.
     * @param location The location to construct the object.
     * @param args The arguments forwarded to the object's constructor.
    */
    template <class T, class ...Args>
    constexpr void construct_at(T* location, Args&&... args)
    {
        ::new (static_cast<void*>(location)) T(forward<Args>(args)...);
    }
    /**
     * Destroys an object at a particular location in memory.
     * @param ptr The location in memory.
    */
    template <class T>
    constexpr void destroy_at(T* ptr)
    {
        if constexpr(is_array<T>::value)
        {
            for (T& elem : *ptr)
                destroy_at(addressof(elem));
        }
        else
            ptr->~T();
    }
    /**
     * Destroys all the elements in the range [first, last).
     * @param first An iterator to the start of the range to destroy.
     * @param last An iterator to the end of the range to destroy.
    */
    template <class InputIterator>
    constexpr void destroy(InputIterator first, InputIterator last)
    {
        while (first != last)
        {
            destroy_at(addressof(*first));
            first++;
        }
    }
    /**
     * Destroys the first n elements in the range starting from first.
     * @param first An iterator to the start of the range to destroy.
     * @param n The number of elements after first to destroy.
    */
    template <class InputIterator, class Size>
    constexpr void destroy_n(InputIterator first, Size n)
    {
        while (n > 0)
        {
            destroy_at(addressof(*first));
            first++;
            n--;
        }
    }
}

#endif /* _STD_COPY_CONSTRUCT_DESTROY */