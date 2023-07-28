#ifndef _STD_COPY_RANDOM
#define _STD_COPY_RANDOM

#include <cstdint>
#include "type_traits.hpp"
#include "vector.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"

namespace _std_copy_hidden
{
    namespace _std_copy_random
    {
        template <
            class UIntType,
            UIntType mult,
            UIntType add,
            UIntType mod,
            bool bigEnough = (!(mod & (mod - 1)) /*Is a power of two*/ || ((UIntType(-1) - add) / mult >= mod - 1) /*Result - 1 is less than max value of UIntType*/),
            bool useSchrage = (mod % mult < mod / mult)
        >
        struct _mod_without_overflow
        {
            static UIntType calc(UIntType x)
            {
                using T = typename _std_copy_hidden::_std_copy_type_traits::_find_uleast<UIntType>::type;
                return static_cast<UIntType>((x * T(mult) + add) % mod);
            }
        };
        //Current integer type (UIntType) is large enough to store the value
        template <
            class UIntType,
            UIntType mult,
            UIntType add,
            UIntType mod,
            bool s
        >
        struct _mod_without_overflow<UIntType, mult, add, mod, true, s>
        {
            static UIntType calc(UIntType x)
            {
                UIntType result = x * mult + add;
                if (mod != 0) result %= mod;
                return result;
            }
        };
        //Use Schrage's method
        template <
            class UIntType,
            UIntType mult,
            UIntType add,
            UIntType mod
        >
        struct _mod_without_overflow<UIntType, mult, add, mod, false, true>
        {
            static UIntType calc(UIntType x)
            {
                if (mult == 1)
                    x %= mod;
                else
                {
                    static const UIntType q = mod / mult;
                    static const UIntType r = mod % mult;

                    UIntType t1 = mult * (x % q);
                    UIntType t2 = r * (x / q);
                    if (t1 >= t2)
                        x = t1 - t2;
                    else
                        x = mod - (t1 - t2);
                }
                if (add != 0)
                {
                    const UIntType d = mod - x;
                    if (d > add)
                        x += add;
                    else
                        x = add - d;
                }
                return x;
            }
        };
    }
}

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

                //k == 0
                {
                    std::uint32_t r1 = 1371501266u;
                    std::uint32_t r2 = r1 + s;
                    first[p] += r1;
                    first[q] += r2;
                    first[0] = r2;
                }

                //k = 1 to m - 1
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

                //k = m to (m + n - 1)
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

    /**
     * Given a seed s, the next generated seed is calculated by
     * s = ((s * multiplierVal) + incrementVal) % modulusVal.
     * 
     * @param UIntType The unsigned integral type.
     * @param multiplierVal The multiplier.
     * @param incrementVal The added value.
     * @param modulusVal The value to mod.
    */
    template <
        class UIntType,
        UIntType multiplierVal,
        UIntType incrementVal,
        UIntType modulusVal
    >
    class linear_congruential_engine
    {
        protected:
            UIntType _seed;

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
                _seed = _std_copy_hidden::_std_copy_random::_mod_without_overflow<UIntType, multiplier, increment, modulus>::calc(_seed);
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

    /**
     * Let X the generated pseudo-random sequence.
     * For the ith generated value, it is calculated by the formula
     * Xi = (X(i - r) - X(i - s) - C) mod 2^w. If Xi < 0, C is set to 1,
     * otherwise, it's set to 0.
     * 
     * @param UIntType The unsigned integral type.
     * @param w The word size, in bits, of the state sequence.
     * @param s The short lag.
     * @param r The long lag.
    */
    template <
        class UIntType,
        std::size_t w,
        std::size_t s,
        std::size_t r
    >
    class subtract_with_carry_engine
    {
        protected:
            typedef subtract_with_carry_engine<UIntType, w, s, r> _self_type;
            typename _std_copy_hidden::_std_copy_type_traits::_find_uleast<UIntType>::type _seed;
        
        public:
            static constexpr std::size_t word_size = w;
            static constexpr std::size_t short_lag = s;
            static constexpr std::size_t long_lag = r;
            static constexpr UIntType default_seed = 19780503u;

            typedef UIntType result_type;

            subtract_with_carry_engine()
            {

            }
    };
}

#endif /* _STD_COPY_RANDOM */