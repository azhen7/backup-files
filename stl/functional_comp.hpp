#ifndef _STD_COPY_FUNCTIONAL_COMP
#define _STD_COPY_FUNCTIONAL_COMP

namespace std_copy
{
    //unary_function
    template <class ArgType, class ResType>
    struct unary_function
    {
        typedef ArgType     argument_type;
        typedef ResType     result_type;
    };

    //binary_function
    template <class FirstArgType, class SecondArgType, class ResType>
    struct binary_function
    {
        typedef FirstArgType        first_argument_type;
        typedef SecondArgType       second_argument_type;
        typedef ResType             result_type;  
    };

    //unary_negate
    template <class Function>
    struct unary_negate
    {
        public:
            typedef typename Function::argument_type argument_type;
            typedef bool                    result_type;
        
        protected:
            Function _internalPred;
        
        public:
            explicit constexpr unary_negate(const Function& x)
                : _internalPred(forward<Function>(x)) {}

            constexpr result_type operator()(const argument_type& x) const
            {
                return !_internalPred(x);
            }
    };
    //not1
    template <class Function>
    constexpr unary_negate<Function> not1(const Function& f)
    {
        return unary_negate<Function>(f);
    }

    //binary_negate
    template <class Function>
    struct binary_negate
    {
        public:
            typedef typename Function::first_argument_type   first_argument_type;
            typedef typename Function::second_argument_type  second_argument_type;
            typedef bool                            result_type;
        
        protected:
            Function _internalPred;
        
        public:
            explicit constexpr binary_negate(const Function& f)
                : _internalPred(forward<Function>(f)) {}
            
            constexpr result_type operator()(const first_argument_type& x, const second_argument_type& y) const
            {
                return !_internalPred(x, y);
            }
    };
    //not2
    template <class Function>
    constexpr binary_negate<Function> not2(const Function& f)
    {
        return binary_negate<Function>(f);
    }

    //pointer_to_unary_function
    template <class ArgType, class ResType>
    struct pointer_to_unary_function : public unary_function<ArgType, ResType>
    {
        protected:
            typedef ResType (*_internalFunctionType)(ArgType);
            _internalFunctionType _internalFunction;
        
        public:
            pointer_to_unary_function(_internalFunctionType f)
                : _internalFunction(forward<_internalFunctionType>(f)) {}
            
            constexpr ResType operator()(const ArgType& x) const
            {
                return _internalFunction(x);
            }
    };

    //pointer_to_binary_function
    template <class ArgType1, class ArgType2, class ResType>
    struct pointer_to_binary_function : public binary_function<ArgType1, ArgType2, ResType>
    {
        protected:
            typedef ResType (*_internalFunctionType)(ArgType1, ArgType2);
            _internalFunctionType _internalFunction;
        
        public:
            pointer_to_binary_function(_internalFunctionType f)
                : _internalFunction(forward<_internalFunctionType>(f)) {}
            
            constexpr ResType operator()(const ArgType1& x, const ArgType2& y) const
            {
                return _internalFunction(x, y);
            }
    };

    //ptr_fun
    template <class ArgType, class ResType>
    pointer_to_unary_function<ArgType, ResType> ptr_fun(ResType (*f)(ArgType))
    {
        return pointer_to_unary_function<ArgType, ResType>(f);
    }
    
    template <class ArgType1, class ArgType2, class ResType>
    pointer_to_binary_function<ArgType1, ArgType2, ResType> ptr_fun(ResType (*f)(ArgType1, ArgType2))
    {
        return pointer_to_binary_function<ArgType1, ArgType2, ResType>(f);
    }

    //Basic arithmetic operations
    /**
     * Struct object performing addition on two elements.
    */
    template <class T>
    struct plus : public binary_function<T, T, T>
    {
        constexpr T operator()(const T& a, const T& b) const
        {
            return a + b;
        }
    };
    /**
     * Partial specialization of plus performing 
     * type deduction.
    */
    template <>
    struct plus<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b) const
            -> decltype(forward<T>(a) + forward<U>(b))
        {
            return a + b;
        }
    };

    /**
     * Struct object performing subtraction on two elements.
    */
    template <class T>
    struct minus : public binary_function<T, T, T>
    {
        constexpr T operator()(const T& a, const T& b) const
        {
            return a - b;
        }
    };
    /**
     * Partial specialization of minus performing 
     * type deduction.
    */
    template <>
    struct minus<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b) const
            -> decltype(forward<T>(a) - forward<U>(b))
        {
            return a - b;
        }
    };

    /**
     * Struct object performing multiplication on two elements.
    */
    template <class T>
    struct multiplies : public binary_function<T, T, T>
    {
        constexpr T operator()(const T& a, const T& b) const
        {
            return a * b;
        }
    };
    /**
     * Partial specialization of multiplies performing 
     * type deduction.
    */
    template <>
    struct multiplies<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b) const
            -> decltype(forward<T>(a) * forward<U>(b))
        {
            return a * b;
        }
    };

    /**
     * Struct object performing division on two elements.
    */
    template <class T>
    struct divides : public binary_function<T, T, T>
    {
        constexpr T operator()(const T& a, const T& b) const
        {
            return a / b;
        }
    };
    /**
     * Partial specialization of divides performing 
     * type deduction.
    */
    template <>
    struct divides<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b) const
            -> decltype(forward<T>(a) / forward<U>(b))
        {
            return a / b;
        }
    };

    /**
     * Struct object performing mod on two elements.
    */
    template <class T>
    struct modulus : public binary_function<T, T, T>
    {
        constexpr T operator()(const T& a, const T& b) const
        {
            return a % b;
        }
    };
    /**
     * Partial specialization of modulus performing type 
     * deduction.
    */
    template <>
    struct modulus<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b) const
            -> decltype(forward<T>(a) % forward<U>(b))
        {
            return a % b;
        }
    };

    /**
     * Struct object negating an element.
    */
    template <class T>
    struct negate : public unary_function<T, T>
    {
        constexpr T operator()(const T& a)
        {
            return -a;
        }
    };
    /**
     * Partial specialization of negate performing type 
     * deduction.
    */
    template <>
    struct negate<void>
    {
        template <class T>
        auto operator()(T&& a)
            -> decltype(forward<T>(a))
        {
            return -a;
        }
    };

    //Basic equality checks
    /**
     * Struct object checking equality between two values.
    */
    template <class T>
    struct equal_to : public binary_function<T, T, bool>
    {
        constexpr bool operator()(const T& a, const T& b) const
        {
            return a == b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct equal_to<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b) const
            -> decltype(forward<T>(a) == forward<U>(b))
        {
            return a == b;
        }
    };

    /**
     * Struct object checking inequality between two values.
    */
    template <class T>
    struct not_equal_to : public binary_function<T, T, bool>
    {
        constexpr bool operator()(const T& a, const T& b) const
        {
            return a != b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct not_equal_to<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b) const
            -> decltype(forward<T>(a) != forward<U>(b))
        {
            return a != b;
        }
    };

    /**
     * Struct object checking if a < b.
    */
    template <class T>
    struct less : public binary_function<T, T, bool>
    {
        constexpr bool operator()(const T& a, const T& b) const
        {
            return a < b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct less<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b) const
            -> decltype(forward<T>(a) < forward<U>(b))
        {
            return a < b;
        }
    };

    /**
     * Struct object checking if a > b.
    */
    template <class T>
    struct greater : public binary_function<T, T, bool>
    {
        constexpr bool operator()(const T& a, const T& b) const
        {
            return a > b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct greater<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b) const
            -> decltype(forward<T>(a) > forward<U>(b))
        {
            return a > b;
        }
    };

    /**
     * Struct object checking if a <= b.
    */
    template <class T>
    struct less_equal : public binary_function<T, T, bool>
    {
        constexpr bool operator()(const T& a, const T& b) const
        {
            return a <= b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct less_equal<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b) const
            -> decltype(forward<T>(a) <= forward<U>(b))
        {
            return a <= b;
        }
    };

    /**
     * Struct object checking if a >= b.
    */
    template <class T>
    struct greater_equal : public binary_function<T, T, bool>
    {
        constexpr bool operator()(const T& a, const T& b) const
        {
            return a >= b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct greater_equal<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b) const
            -> decltype(forward<T>(a) >= forward<U>(b))
        {
            return a >= b;
        }
    };

    //Logical operations
    /**
     * Struct object performing logical and on two elements.
    */
    template <class T>
    struct logical_and : public binary_function<T, T, bool>
    {
        constexpr bool operator()(const T& a, const T& b) const
        {
            return a && b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct logical_and<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b) const
            -> decltype(forward<T>(a) && forward<U>(b))
        {
            return a && b;
        }
    };

    /**
     * Struct object performing logical and on two elements.
    */
    template <class T>
    struct logical_or : public binary_function<T, T, bool>
    {
        constexpr bool operator()(const T& a, const T& b) const
        {
            return a || b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct logical_or<void>
    {
        template <class T, class U>
        auto operator()(T&& a, U&& b) const
            -> decltype(forward<T>(a) || forward<U>(b))
        {
            return a || b;
        }
    };

    /**
     * Struct object performing logical and on two elements.
    */
    template <class T>
    struct logical_not : public unary_function<T, bool>
    {
        constexpr bool operator()(const T& a)
        {
            return !a;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct logical_not<void>
    {
        template <class T>
        auto operator()(T&& a)
            -> decltype(!forward<T>(a))
        {
            return !a;
        }
    };

    //Bitwise operations
    /**
     * Struct object performing bitwise and on two elements.
    */
    template <class T>
    struct bit_and : public binary_function<T, T, T>
    {
        constexpr T operator()(const T& a, const T& b) const
        {
            return a & b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct bit_and<void>
    {
        template <class T, class I>
        auto operator()(T&& a, I&& b)
            -> decltype(forward<T>(a) & forward<I>(b))
        {
            return a & b;
        }
    };

    /**
     * Struct object performing bitwise or on two elements.
    */
    template <class T>
    struct bit_or : public binary_function<T, T, T>
    {
        constexpr T operator()(const T& a, const T& b) const
        {
            return a | b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct bit_or<void>
    {
        template <class T, class I>
        auto operator()(T&& a, I&& b)
            -> decltype(forward<T>(a) | forward<I>(b))
        {
            return a | b;
        }
    };

    /**
     * Struct object performing bitwise xor on two elements.
    */
    template <class T>
    struct bit_xor : public binary_function<T, T, T>
    {
        constexpr T operator()(const T& a, const T& b) const
        {
            return a ^ b;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct bit_xor<void>
    {
        template <class T, class I>
        auto operator()(T&& a, I&& b)
            -> decltype(forward<T>(a) ^ forward<I>(b))
        {
            return a ^ b;
        }
    };

    /**
     * Struct object performing bitwise not on two elements.
    */
    template <class T>
    struct bit_not : public unary_function<T, T>
    {
        constexpr T operator()(const T& a)
        {
            return ~a;
        }
    };
    /**
     * Partial specialization performing type deduction.
    */
    template <>
    struct bit_not<void>
    {
        template <class T>
        auto operator()(T&& a)
            -> decltype(~forward<T>(a))
        {
            return ~a;
        }
    };

    //identity
    template <class T>
    struct identity : public unary_function<T, T>
    {
        T operator()(const T& a)
        {
            return forward<T>(a);
        }
    };

    //binder1st
    template <class Fn>
    struct binder1st : public unary_function<typename Fn::second_argument_type, typename Fn::result_type>
    {
        protected:
            Fn _internalOp;
            typename Fn::first_argument_type val;
        
        public:
            binder1st(const Fn& f, const typename Fn::first_argument_type& s)
                : _internalOp(f), val(s)
            {}

            typename Fn::result_type operator()(const typename Fn::second_argument_type& x) const
            {
                return _internalOp(val, x);
            }
    };
    //bind1st
    template <class F, class T>
    binder1st<F> bind1st(const F& f, const T& x)
    {
        typedef typename F::first_argument_type _arg_type;
        return binder1st<F>(f, _arg_type(x));
    }

    //binder2nd
    template <class Fn>
    struct binder2nd : public unary_function<typename Fn::first_argument_type, typename Fn::result_type>
    {
        protected:
            Fn _internalOp;
            typename Fn::second_argument_type val;
        
        public:
            binder2nd(const Fn& f, const typename Fn::second_argument_type& s)
                : _internalOp(forward<Fn>(f)), val(forward<Fn>(f))
            {}

            typename Fn::result_type operator()(const typename Fn::first_argument_type& x) const
            {
                return _internalOp(x, val);
            }
    };
    //bind2nd
    template <class F, class T>
    binder2nd<F> bind2nd(const F& f, const T& x)
    {
        return binder2nd<F>(f, typename F::second_argument_type(x));
    }
}

#endif /* _STD_COPY_FUNCTIONAL_COMP */