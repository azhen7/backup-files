#ifndef _STD_COPY_RANDOM
#define _STD_COPY_RANDOM

#include <cstdint>
#include "type_traits.hpp"
#include "vector.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

namespace std_copy
{
    class seed_seq
    {
        public:
            typedef std::uint_least32_t result_type;

            seed_seq()
            {
            }

            template <class InputIt>
            seed_seq(InputIt first, InputIt last)
            {
                _internalBuffer.assign(first, last);
            }

            std::size_t size() { return _internalBuffer.size(); }
            
            template <class OutputIt>
        #if __cplusplus > 201703L
            requires output_iterator<OutputIt>
        #endif
            void param(OutputIt out)
            {
                std_copy::copy(_internalBuffer.begin(), _internalBuffer.end(), out);
            }

            template <class RandomIt>
            void generate(RandomIt first, RandomIt last)
        #if __cplusplus > 201703L
            requires random_access_iterator<RandomIt>
        #endif
            {
                std_copy::fill(first, last, 0x8b8b8b8b);

                const std::size_t n = last - first;
                const std::size_t s = this->size();
                const std::size_t t = (n < 7) ? (n - 1) >> 1
                                    : (n < 39) ? 3
                                    : (n < 68) ? 5
                                    : (n < 623) ? 7
                                    : 11;
                const std::size_t p = (n - t) >> 1;
                const std::size_t q = p + t;
                const std::size_t m = std_copy::max(s + 1, n);

                {
                    std::uint32_t r1 = 1371501266u;
                    std::uint32_t r2 = r1 + s;
                    first[p] += r1;
                    first[q] += r2;
                    first[0] = r2;
                }

                for (std::size_t k = 1; k < m; k++)
                {
                    std::size_t kp = (k + p) % n;
                    std::size_t kq = (k + q) % n;
                    std::size_t kmod = k % n;

                    std::uint32_t res = first[kmod] ^ first[kp] ^ first[(k - 1) % n];
                    std::uint32_t r1 = 1664525u * (res ^ (res >> 27));
                    std::uint32_t r2 = (k <= s) ? r1 + kmod + _internalBuffer[k - 1]
                                     :            r1 + kmod;
                    first[kp] +=  r1;
                    first[kq] += r2;
                    first[kmod] = r2;
                }

                for (std::size_t k = m; k < m + n; k++)
                {
                    std::size_t kp = (k + p) % n;
                    std::size_t kq = (k + q) % n;
                    std::size_t kmod = k % n;

                    std::uint32_t res = first[kmod] + first[kp] + first[(k - 1) % n];
                    std::uint32_t r3 = 1566083941u * (res ^ (res >> 27));
                    std::uint32_t r4 = r3 - kmod;
                    first[kp] ^= r3;
                    first[kq] ^= r4;
                    first[kmod] = r4;
                }
            }

        private:
            vector<result_type> _internalBuffer;
    };

    template <
        class UIntType,
        UIntType multiplierVal,
        UIntType incrementVal,
        UIntType modulusVal
    >
    /**
     * Given three variables a, b, c, calculates the next
     * generated pseudo-random value with the formula
     * _seed = ((_seed * a) + b) % c.
    */
    class linear_congruential_engine
    {
        protected:
            typename _std_copy_hidden::_std_copy_type_traits::_find_uleast<UIntType>::type _seed;

            typedef linear_congruential_engine<
                UIntType,
                multiplierVal,
                incrementVal,
                modulusVal
            > _self_type;
        
        public:
            typedef UIntType    result_type;

            static constexpr UIntType multiplier   = multiplierVal;
            static constexpr UIntType increment    = incrementVal;
            static constexpr UIntType modulus      = modulusVal;
            static constexpr UIntType default_seed = 1u;

            linear_congruential_engine()
                : _seed(default_seed) {}
            
            explicit linear_congruential_engine(result_type val)
                : _seed(val) {}

            linear_congruential_engine(const _self_type& l)
                : _seed(l._seed) {}

            /**
             * Sets the seed of the engine
             * @param val The seed that gets set.
            */
            void seed(result_type val = default_seed)
            {
                _seed = val;
            }
            /**
             * Returns the smallest possible value in the output range.
            */
            result_type min() const noexcept
            {
                return (increment == 0) ? 1u : 0u;
            }
            /**
             * Returns the maximum possible value in the output range.
            */
            result_type max() const noexcept
            {
                return modulus - 1;
            }
            /**
             * Generates and returns a pseudo-random value.
            */
            result_type operator()()
            {
                _seed = ((multiplier * _seed) + increment) % modulus;
                return _seed;
            }
            /**
             * Advances the internal state of the engine by z positions.
             * @param z The number of positions to advance the internal state by.
            */
            void discard(std::size_t z)
            {
                while (z-- > 0)
                    (*this)();
            }

            template <class UInt, UInt a, UInt c, UInt m>
            friend bool operator==(const _self_type& lhs,
                                   const _self_type& rhs);
            template <class UInt, UInt a, UInt c, UInt m>
            friend bool operator!=(const _self_type& lhs,
                                   const _self_type& rhs);
    };
    
    template <class UIntType, UIntType a, UIntType c, UIntType m>
    bool operator==(const linear_congruential_engine<UIntType, a, c, m>& lhs,
                    const linear_congruential_engine<UIntType, a, c, m>& rhs)
    {
        return (lhs._seed == rhs._seed) && (lhs.multiplier == rhs.multiplier)
               && (lhs.increment == rhs.increment) && (lhs.default_seed == rhs.default_seed);
    }

    template <class UIntType, UIntType a, UIntType c, UIntType m>
    bool operator!=(const linear_congruential_engine<UIntType, a, c, m>& lhs,
                    const linear_congruential_engine<UIntType, a, c, m>& rhs)
    {
        return !(lhs == rhs);
    }

    typedef linear_congruential_engine<std::uint_fast32_t, 16807UL, 0UL, 2147483647UL> minstd_rand0;
    typedef linear_congruential_engine<std::uint_fast32_t, 48271UL, 0UL, 2147483647UL> minstd_rand;
}

#endif /* _STD_COPY_RANDOM */