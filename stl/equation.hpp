#ifndef _STD_COPY_EQUATION
#define _STD_COPY_EQUATION

#include "move.hpp"
#include "algorithm.hpp"

#include <string>
#include <cstdint>
#include <cmath>
#include <stdexcept>

namespace std_copy
{
    class point
    {
        protected:
            using LD = long double;

            LD x;
            LD y;
        
        public:
            point() : x(0), y(0) {}
            point(LD a, LD b)
                : x(a), y(b) {}
            point(const point& obj)
                : x(obj.x), y(obj.y) {}
            point(point&& obj)
                : x(move(obj.x)), y(move(obj.y)) {}

            LD get_x() const noexcept
            {
                return x;
            }

            LD get_y() const noexcept
            {
                return y;
            }

            point& set_x(LD a)
            {
                x = move(a);
                return *this;
            }

            point& set_y(LD b)
            {
                y = move(b);
                return *this;
            }
    };

    class equation
    {
    private:
        using LD = long double;
        using _self_type = equation;

        LD* _buf{nullptr};
        std::ptrdiff_t _n{0};
    
    public:
        equation(std::ptrdiff_t n)
        {
            _n = n;
            _buf = new LD[n + 1];
        }
        equation(LD* s, LD* e)
        {
            _n = e - s;
            _buf = new LD[_n + 1];
            for (std::ptrdiff_t i = 0; s != e; i++)
            {
                _buf[i] = *s;
                s++;
            }
        }
        equation()
        {
        }

        _self_type& set_terms(LD* s, LD* e) noexcept
        {
            _n = e - s - 1;
            if (_buf)
                delete[] _buf;
            _buf = new LD[_n + 1];

            for (std::ptrdiff_t i = 0; s != e; i++)
            {
                _buf[i] = *s;
                s++;
            }
            return *this;
        }
        template <std::ptrdiff_t n>
        _self_type& set_terms(LD x[n])
        {
            _n = n - 1;
            if (_buf)
                delete[] _buf;
            _buf = new LD[_n];

            for (std::ptrdiff_t i = 0; i < _n; i++)
            {
                _buf[i] = x[i];
            }
            return *this;
        }
        _self_type& set_terms(const equation& e) noexcept
        {
            _n = e._n;
            if (_buf)
                delete[] _buf;
            _buf = new LD[_n + 1];

            std_copy::copy(e._buf, e._buf + _n + 1, _buf);
            return *this;
        }

        LD operator()(LD x) const noexcept
        {
            LD sum = 0;
            LD p = std::pow(x, _n);
            for (std::ptrdiff_t i = 0; i < _n + 1; i++)
            {
                sum += _buf[i] * p;
                p /= x;
            }
            return sum;
        }
        LD substitute(LD x) const noexcept
        {
            return (*this)(x);
        }

        LD degree() const noexcept
        {
            return _n;
        }
        LD& at(std::size_t i) const
        {
            if (i > _n)
            {
                throw std::out_of_range("equation::at");
            }
            return _buf[i];
        }
        LD* data() const noexcept
        {
            return _buf;
        }

        LD leading_coefficient() const noexcept
        {
            if (_n == 0) return 0;
            return _buf[0];
        }
        LD y_intercept() const noexcept
        {
            if (_n == 0) return 0;
            return _buf[_n];
        }
    };
}

#endif /* _STD_COPY_EQUATION */