#ifndef _STD_COPY_STD_FUNCTIONAL
#define _STD_COPY_STD_FUNCTIONAL

#include "move.hpp"
#include <functional>

namespace std_copy
{
    /**
     * My implementation of std::function from the header <functional>
    */
    template <class T, class ...Args>
    class function {};
    template <class T, class ...Args>
    class function<T(Args...)>
    {
        private:
            typedef function<T(Args...)>    _function_type;
            typedef T (*_internalFunctionType)(Args...);

            _internalFunctionType _target;

        public:
            function() : _target(nullptr) {}
            function(decltype(nullptr)) : _target(nullptr) {}

            function(const _function_type& f)
                : _target(f._target) {}
            function(_function_type&& f) noexcept
                : _target(move(f._target)) {}
            
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

            bool operator bool()
            {
                return _target != nullptr;
            }
            bool has_target()
            {
                return _target != nullptr;
            }

            T operator()(Args... args)
            {
                if (!_target)
                    throw std::bad_function_call();

                return _target(forward<Args>(args)...);
            }
    };
}

#endif /* _STD_COPY_STD_FUNCTIONAL */