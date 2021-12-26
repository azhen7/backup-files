#ifndef _STD_COPY_RANDOM
#define _STD_COPY_RANDOM

#include <cstdint>
#include <random>

namespace std_copy
{
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
            > _linear_congruential_engine_type;
        
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

            linear_congruential_engine(const _linear_congruential_engine_type& l)
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
            void discard(unsigned long long z)
            {
                while (z-- > 0)
                    (*this)();
            }

            template <class UInt, UInt a, UInt c, UInt m>
            friend bool operator==(const _linear_congruential_engine_type& lhs,
                                   const _linear_congruential_engine_type& rhs);
            template <class UInt, UInt a, UInt c, UInt m>
            friend bool operator!=(const _linear_congruential_engine_type& lhs,
                                   const _linear_congruential_engine_type& rhs);
    };
    
    template <class UIntType, UIntType a, UIntType c, UIntType m>
    bool operator==(const linear_congruential_engine<UIntType, a, c, m>& lhs,
                    const linear_congruential_engine<UIntType, a, c, m>& rhs)
    {
        return lhs._seed == rhs._seed;
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