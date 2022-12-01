#ifndef _STD_COPY_STD_FUNCTIONAL
#define _STD_COPY_STD_FUNCTIONAL

#include "move.hpp"

namespace std_copy
{
    /**
     * An implementation of std::function from the header <functional>.
     * @param ReturnType The return type of the internal function object.
     * @param ArgumentTypes The types of the arguments that the internal function 
     * object accepts.
    */
    template <class ReturnType, class ...ArgumentTypes>
    class function;
    template <class ReturnType, class ...ArgumentTypes>
    class function<ReturnType(ArgumentTypes...)>
    {
        protected:
            typedef function<ReturnType(ArgumentTypes...)>    _function_type;
            typedef ReturnType (*_internalFunctionType)(ArgumentTypes...);

            _internalFunctionType _target;

        public:
            function() : _target(nullptr) {}
            function(decltype(nullptr)) : _target(nullptr) {}

            function(const _function_type& f)
                : _target(f._target) {}
            function(_function_type&& f) noexcept
                : _target(forward<F>(f._target)) {}
            
            template <class F>
            function(F&& f)
                : _target(forward<F>(f)) {}
            
            _function_type& operator=(const _function_type& f)
            {
                _target = move(f._target);
                return *this;
            }
            _function_type& operator=(_function_type&& f)
            {
                _target = move(f._target);
                return *this;
            }
            _function_type& operator=(decltype(nullptr))
            {
                _target = nullptr;
                return *this;
            }
            template <class F>
            _function_type& operator=(F&& f)
            {
                _target = forward<F>(f);
                return *this;
            }

            void swap(_function_type& f)
            {
                _internalFunctionType swapTemp = f._target;
                f._target = _target;
                _target = swapTemp;
            }

            operator bool()
            {
                return _target != nullptr;
            }
            bool has_target()
            {
                return _target != nullptr;
            }

            ReturnType operator()(ArgumentTypes... Arguments)
            {
                if (!_target)
                    throw std::bad_function_call();

                return _target(forward<ArgumentTypes>(Arguments)...);
            }
    };
}

#endif /* _STD_COPY_STD_FUNCTIONAL */