#ifndef _STD_COPY_CONCEPTS
#define _STD_COPY_CONCEPTS

#if __cplusplus > 201703L
#include "type_traits.hpp"

namespace std_copy
{
    //Concept equivalent of is_same_v
    template <class T, class U>
    concept same_as = is_same_v<T, U> && is_same_v<U, T>;
    //Concept equivalent of is_integral_v
    template <class T>
    concept integral = is_integral_v<T>;
    //Concept equivalent of is_floating_v
    template <class T>
    concept floating_point = is_floating_point_v<T>;
    //Concept equivalent of is_convertible
    template <class T, class U>
    concept convertible_to =
    requires(T elemT, U elemU)
    {
        {static_cast<U>(elemT)} -> same_as<U>;
        {static_cast<T>(elemU)} -> same_as<T>;
    };
    //Concept equivalent of is_signed_v
    template <class T>
    concept signed_integral = integral<T> && is_signed_v<T>;
    //Concept equivalent of is_unsigned_v
    template <class T>
    concept unsigned_integral = integral<T> && is_unsigned_v<T>;
    //Checks if two types are assignable
    template <class LHS, class RHS>
    concept assignable_from = is_lvalue_reference_v<LHS> &&
    requires(LHS l, RHS r)
    {
        {l = r} -> same_as<LHS>;
    };
    //Checks if a given type T can be constructed from Args...
    template <class T, class ...Args>
    concept constructible_from =
    requires(Args... args)
    {
        {T(forward<Args>(args)...)} -> same_as<T>;
    };
    //Check if a given type T is default constructible
    template <class T>
    concept default_constructible =
    requires
    {
        {T()};
    };
}
#endif

#endif /* _STD_COPY_CONCEPTS */