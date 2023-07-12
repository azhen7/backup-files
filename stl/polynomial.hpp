#ifndef _STD_COPY_POLYNOMIAL
#define _STD_COPY_POLYNOMIAL

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

    class polynomial
    {
    private:
        using LD = long double;
        using _self_type = polynomial;

        LD* _buf{nullptr};
        std::ptrdiff_t _n{0};
    
    public:
        polynomial(std::ptrdiff_t n)
        {
            _n = n;
            _buf = new LD[n + 1];
        }
        polynomial(LD* s, LD* e)
        {
            _n = e - s;
            _buf = new LD[_n + 1];
            for (std::ptrdiff_t i = 0; s != e; i++)
            {
                _buf[i] = *s;
                s++;
            }
        }
        polynomial()
        {
        }

        ~polynomial()
        {
            if (_buf)
            {
                delete[] _buf;
                _buf = nullptr;
                _n = 0;
            }
        }

        _self_type& set_terms(LD* s, LD* e) noexcept
        {
            _n = e - s - 1;
            if (_buf)
                delete[] _buf;
            _buf = new LD[_n + 1];

            std_copy::copy(s, e, _buf);
            return *this;
        }
        _self_type& set_terms(const polynomial& e) noexcept
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
                throw std::out_of_range("polynomial::at");
            }
            return _buf[i];
        }
        LD* data() const noexcept
        {
            return _buf;
        }

        LD leading_coefficient() const noexcept
        {
            return _buf[0];
        }
        LD y_intercept() const noexcept
        {
            return _buf[_n];
        }
    };
}

#endif /* _STD_COPY_POLYNOMIAL */