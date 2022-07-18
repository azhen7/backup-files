#ifndef _STD_COPY_EQUATION
#define _STD_COPY_EQUATION

#include "move.hpp"
#include <string>

namespace std_copy
{
    class point
    {
        protected:
            long long x;
            long long y;
        
        public:
            point() : x(0), y(0) {}
            point(long long a, long long b)
                : x(move(a)), y(move(b)) {}
            point(const point& obj)
                : x(move(obj.x)), y(move(obj.y)) {}
            point(point&& obj)
                : x(move(obj.x)), y(move(obj.y)) {}

            long long get_x() const noexcept
            {
                return x;
            }

            long long get_y() const noexcept
            {
                return y;
            }

            void set_x(long long a)
            {
                x = move(a);
            }

            void set_y(long long b)
            {
                y = move(b);
            }
    };

    template <unsigned long long DegreeOfEquation>
    class equation
    {
        protected:
                using _long_long_type = long long;
                using _equation_type  = equation<DegreeOfEquation>;

                _long_long_type _coefficients[DegreeOfEquation + 1];

        public:
            equation(_long_long_type (&arr)[DegreeOfEquation + 1])
            {
                for (_long_long_type i = 0; i < DegreeOfEquation + 1; i++)
                    _coefficients[i] = move(arr[i]);
            }

            template <class ...Args>
            equation(Args ...args)
            {
                _long_long_type i = 0;
                (void(_coefficients[i++] = args), ...);
            }

            _long_long_type operator()(_long_long_type input)
            {
                _long_long_type ret = 0;
                for (_long_long_type i = 0; i < DegreeOfEquation + 1; i++)
                    ret += _coefficients[i] * __builtin_pow(input, DegreeOfEquation - i);
                return ret;
            }

            _equation_type change_coefficient(_long_long_type term, _long_long_type newCoef)
            {
                _coefficients[term - 1] = newCoef;
                return *this;
            }

            _equation_type set_coefficients(_long_long_type (&arr)[DegreeOfEquation + 1])
            {
                for (_long_long_type i = 0; i < DegreeOfEquation + 1; i++)
                    _coefficients[i] = move(arr[i]);
                return *this;
            }
            template <class ...Args>
            _equation_type set_coefficients(Args... a)
            {
                _long_long_type i = 0;
                (void(_coefficients[i++] = a), ...);
                return *this;
            }

            _long_long_type* coefficients() const noexcept
            {
                return _coefficients;
            }

            point y_intercept()
            {
                return point(0, _coefficients[DegreeOfEquation]);
            }

            _long_long_type degree() const noexcept
            {
                return DegreeOfEquation;
            }

            _long_long_type leading_coefficient() const noexcept
            {
                if constexpr(DegreeOfEquation == 0)
                    return 0;
                return _coefficients[0];
            }

            _long_long_type constant() const noexcept
            {
                if constexpr(DegreeOfEquation == 0)
                    return 0;
                return _coefficients[DegreeOfEquation];
            }

            equation<DegreeOfEquation - 1> derivative()
            {
                _long_long_type newCoefs[DegreeOfEquation];

                for (_long_long_type i = 0; i < DegreeOfEquation; i++)
                {
                    newCoefs[i] = (DegreeOfEquation - i) * _coefficients[i];
                }
                return equation<DegreeOfEquation - 1>(newCoefs);
            }
    };

    template <unsigned long long N>
    std::string to_string(equation<N> e)
    {
        //tbd
    }
}

#endif /* _STD_COPY_EQUATION */