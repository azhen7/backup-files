#ifndef _STD_COPY_LIMITS
#define _STD_COPY_LIMITS

#include <cfloat>
#include <climits>
#include <cstdint>

#define _std_copy_limits_log2     ((643L) / (2136.0))

namespace std_copy
{
    /**
     * Contains values indicating the denorm style of 
     * different types.
    */
    enum float_denorm_style
    {
        denorm_indeterminate = -1,
        denorm_absent        = 0,
        denorm_present       = 1
    };
    /**
     * Contains values indicating how a value of a type 
     * is rounded.
    */
    enum float_round_style
    {
        round_indeterminate       = -1,
        round_toward_zero         = 0,
        round_to_nearest          = 1,
        round_toward_infinity     = 2,
        round_toward_neg_infinity = 3
    };


    template <class T>
    struct numeric_limits
    {
        static constexpr bool is_specialized    = false;
        static constexpr bool is_signed         = false;
        static constexpr bool is_integer        = false;
        static constexpr bool is_exact          = false;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = false;
        static constexpr int digits             = 0;
        static constexpr int digits10           = 0;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = false;
        static constexpr bool is_modulo         = false;
        static constexpr bool radix             = 0;

        static constexpr T min() noexcept { return T(); }

        static constexpr T lowest() noexcept { return T(); }

        static constexpr T max() noexcept { return T(); }

        static constexpr T epsilon() noexcept { return T(); }

        static constexpr T round_error() noexcept { return T(); }

        static constexpr T infinity() noexcept { return T(); }

        static constexpr T quite_NaN() noexcept { return T(); }
    };
    template <>
    struct numeric_limits<bool>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = false;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = 1;
        static constexpr int digits10           = 0;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = false;
        static constexpr bool radix             = 2;

        static constexpr bool min() noexcept { return false; }
        
        static constexpr bool lowest() noexcept { return false; }

        static constexpr bool max() noexcept { return true; }

        static constexpr bool epsilon() noexcept { return false; }

        static constexpr bool round_error() noexcept { return false; }

        static constexpr bool infinity() noexcept { return false; }

        static constexpr bool quiet_NaN() noexcept { return false; }
    };
    template <>
    struct numeric_limits<char>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = true;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT - 1;
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = false;
        static constexpr bool radix             = 2;

        static constexpr char min() noexcept { return CHAR_MIN; }

        static constexpr char lowest() noexcept { return CHAR_MIN; }

        static constexpr char max() noexcept { return CHAR_MAX; }

        static constexpr char epsilon() noexcept { return 0; }

        static constexpr char round_error() noexcept { return 0; }

        static constexpr char infinity() noexcept { return 0; }

        static constexpr char quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<signed char>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = true;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT - 1;
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = false;
        static constexpr bool radix             = 2;

        static constexpr signed char min() noexcept { return SCHAR_MIN; }

        static constexpr signed char lowest() noexcept { return SCHAR_MIN; }

        static constexpr signed char max() noexcept { return SCHAR_MAX; }

        static constexpr signed char epsilon() noexcept { return 0; }

        static constexpr signed char round_error() noexcept { return 0; }

        static constexpr signed char quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<unsigned char>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = false;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT;
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = true;
        static constexpr bool radix             = 2;

        static constexpr unsigned char min() noexcept { return 0; }

        static constexpr unsigned char lowest() noexcept { return 0; }

        static constexpr unsigned char max() noexcept { return UCHAR_MAX; }

        static constexpr unsigned char epsilon() noexcept { return 0; }

        static constexpr unsigned char round_error() noexcept { return 0; }

        static constexpr unsigned char infinity() noexcept { return 0; }

        static constexpr unsigned char quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<wchar_t>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = false;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT * sizeof(wchar_t) - 1;
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = true;
        static constexpr bool radix             = 2;

        static constexpr wchar_t min() noexcept { return WCHAR_MIN; }

        static constexpr wchar_t lowest() noexcept { return WCHAR_MIN; }

        static constexpr wchar_t max() noexcept { return WCHAR_MAX; }

        static constexpr wchar_t epsilon() noexcept { return 0; }

        static constexpr wchar_t round_error() noexcept { return 0; }

        static constexpr wchar_t infinity() noexcept { return 0; }

        static constexpr wchar_t quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<char8_t>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = false;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT * sizeof(char8_t) - 1;
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = true;
        static constexpr bool radix             = 2;

        static constexpr char8_t min() noexcept { return 0; }

        static constexpr char8_t lowest() noexcept { return 0; }

        static constexpr char8_t max() noexcept { return UCHAR_MAX; }

        static constexpr char8_t epsilon() noexcept { return 0; }

        static constexpr char8_t round_error() noexcept { return 0; }

        static constexpr char8_t infinity() noexcept { return 0; }

        static constexpr char8_t quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<char16_t>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = false;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT * sizeof(char16_t) - 1;
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = true;
        static constexpr bool radix             = 2;

        static constexpr char16_t min() noexcept { return 0; }

        static constexpr char16_t lowest() noexcept { return 0; }

        static constexpr char16_t max() noexcept { return UINT_LEAST16_MAX; }

        static constexpr char16_t epsilon() noexcept { return 0; }

        static constexpr char16_t round_error() noexcept { return 0; }

        static constexpr char16_t infinity() noexcept { return 0; }

        static constexpr char16_t quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<char32_t>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = false;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT * sizeof(char32_t) - 1;
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = true;
        static constexpr bool radix             = 2;

        static constexpr char32_t min() noexcept { return 0; }

        static constexpr char32_t lowest() noexcept { return 0; }

        static constexpr char32_t max() noexcept { return UINT_LEAST32_MAX; }

        static constexpr char32_t epsilon() noexcept { return 0; }

        static constexpr char32_t round_error() noexcept { return 0; }

        static constexpr char32_t infinity() noexcept { return 0; }

        static constexpr char32_t quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<short>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = true;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT * sizeof(short) - 1;
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = false;
        static constexpr bool radix             = 2;

        static constexpr short min() noexcept { return SHRT_MIN; }

        static constexpr short lowest() noexcept { return SHRT_MIN; }

        static constexpr short max() noexcept { return SHRT_MAX; }

        static constexpr short epsilon() noexcept { return 0; }

        static constexpr short round_error() noexcept { return 0; }

        static constexpr short infinity() noexcept { return 0; }

        static constexpr short quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<unsigned short>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = false;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT * sizeof(short);
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = true;
        static constexpr bool radix             = 2;

        static constexpr unsigned short min() noexcept { return 0; }

        static constexpr unsigned short lowest() noexcept { return 0; }

        static constexpr unsigned short max() noexcept { return USHRT_MAX; }

        static constexpr unsigned short epsilon() noexcept { return 0; }

        static constexpr unsigned short round_error() noexcept { return 0; }

        static constexpr unsigned short infinity() noexcept { return 0; }

        static constexpr unsigned short quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<int>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = true;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT * sizeof(int) - 1;
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = false;
        static constexpr bool radix             = 2;

        static constexpr int min() noexcept { return INT_MIN; }

        static constexpr int lowest() noexcept { return INT_MIN; }

        static constexpr int max() noexcept { return INT_MAX; }

        static constexpr int epsilon() noexcept { return 0; }

        static constexpr int round_error() noexcept { return 0; }

        static constexpr int infinity() noexcept { return 0; }

        static constexpr int quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<unsigned int>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = false;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT * sizeof(int);
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = true;
        static constexpr bool radix             = 2;

        static constexpr unsigned int min() noexcept { return 0; }

        static constexpr unsigned int lowest() noexcept { return 0; }

        static constexpr unsigned int max() noexcept { return UINT_MAX; }

        static constexpr unsigned int epsilon() noexcept { return 0; }

        static constexpr unsigned int round_error() noexcept { return 0; }

        static constexpr unsigned int infinity() noexcept { return 0; }

        static constexpr unsigned int quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<long>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = true;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT * sizeof(long) - 1;
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = false;
        static constexpr bool radix             = 2;

        static constexpr long min() noexcept { return LONG_MIN; }

        static constexpr long lowest() noexcept { return LONG_MIN; }

        static constexpr long max() noexcept { return LONG_MAX; }

        static constexpr long epsilon() noexcept { return 0; }

        static constexpr long round_error() noexcept { return 0; }

        static constexpr long infinity() noexcept { return 0; }

        static constexpr long quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<unsigned long>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = false;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT * sizeof(long);
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = true;
        static constexpr bool radix             = 2;

        static constexpr unsigned long min() noexcept { return 0; }

        static constexpr unsigned long lowest() noexcept { return 0; }

        static constexpr unsigned long max() noexcept { return ULONG_MAX; }

        static constexpr unsigned long epsilon() noexcept { return 0; }

        static constexpr unsigned long round_error() noexcept { return 0; }

        static constexpr unsigned long infinity() noexcept { return 0; }

        static constexpr unsigned long quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<long long>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = true;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT * sizeof(long long) - 1;
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = false;
        static constexpr bool radix             = 2;

        static constexpr long long min() noexcept { return LLONG_MIN; }

        static constexpr long long lowest() noexcept { return LLONG_MIN; }

        static constexpr long long max() noexcept { return LLONG_MAX; }

        static constexpr long long epsilon() noexcept { return 0; }

        static constexpr long long round_error() noexcept { return 0; }

        static constexpr long long infinity() noexcept { return 0; }

        static constexpr long long quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<unsigned long long>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = false;
        static constexpr bool is_integer        = true;
        static constexpr bool is_exact          = true;
        static constexpr bool is_iec559         = false;
        static constexpr bool has_infinity      = false;
        static constexpr bool has_quiet_NAN     = false;
        static constexpr bool has_signaling_NAN = false;
        static constexpr float_denorm_style has_denorm = denorm_absent;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_toward_zero;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = CHAR_BIT * sizeof(long long);
        static constexpr int digits10           = digits * _std_copy_limits_log2;
        static constexpr int min_exponent       = 0;
        static constexpr int max_exponent       = 0;
        static constexpr int max_exponent10     = 0;
        static constexpr int min_exponent10     = 0;
        static constexpr int max_digits10       = 0;
        static constexpr bool traps             = true;
        static constexpr bool is_modulo         = true;
        static constexpr bool radix             = 2;

        static constexpr unsigned long long min() noexcept { return 0; }

        static constexpr unsigned long long lowest() noexcept { return 0; }

        static constexpr unsigned long long max() noexcept { return ULLONG_MAX; }

        static constexpr unsigned long long epsilon() noexcept { return 0; }

        static constexpr unsigned long long round_error() noexcept { return 0; }

        static constexpr unsigned long long infinity() noexcept { return 0; }

        static constexpr unsigned long long quiet_NaN() noexcept { return 0; }
    };
    template <>
    struct numeric_limits<float>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = true;
        static constexpr bool is_integer        = false;
        static constexpr bool is_exact          = false;
        static constexpr bool is_iec559         = true;
        static constexpr bool has_infinity      = true;
        static constexpr bool has_quiet_NAN     = true;
        static constexpr bool has_signaling_NAN = true;
        static constexpr float_denorm_style has_denorm = denorm_present;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_to_nearest;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = FLT_MANT_DIG;
        static constexpr int digits10           = FLT_DIG;
        static constexpr int min_exponent       = FLT_MIN_EXP;
        static constexpr int max_exponent       = FLT_MAX_EXP;
        static constexpr int min_exponent10     = FLT_MIN_10_EXP;
        static constexpr int max_exponent10     = FLT_MAX_10_EXP;
        static constexpr int max_digits10       = (int) 2 + digits * _std_copy_limits_log2;
        static constexpr bool traps             = false;
        static constexpr bool is_modulo         = false;
        static constexpr bool radix             = FLT_RADIX;

        static constexpr float min() noexcept { return FLT_MIN; }

        static constexpr float lowest() noexcept { return -FLT_MAX; }

        static constexpr float max() noexcept { return FLT_MAX; }

        static constexpr float epsilon() noexcept { return FLT_EPSILON; }

        static constexpr float round_error() noexcept { return 0.5F; }

        static constexpr float infinity() noexcept { return __builtin_huge_valf(); }

        static constexpr float quiet_NaN() noexcept { return __builtin_nanf(""); }
    };
    template <>
    struct numeric_limits<double>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = true;
        static constexpr bool is_integer        = false;
        static constexpr bool is_exact          = false;
        static constexpr bool is_iec559         = true;
        static constexpr bool has_infinity      = true;
        static constexpr bool has_quiet_NAN     = true;
        static constexpr bool has_signaling_NAN = true;
        static constexpr float_denorm_style has_denorm  = denorm_present;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_to_nearest;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = DBL_MANT_DIG;
        static constexpr int digits10           = DBL_DIG;
        static constexpr int min_exponent       = DBL_MIN_EXP;
        static constexpr int max_exponent       = DBL_MAX_EXP;
        static constexpr int min_exponent10     = DBL_MIN_10_EXP;
        static constexpr int max_exponent10     = DBL_MAX_10_EXP;
        static constexpr int max_digits10       = (int) 2 + digits * _std_copy_limits_log2;
        static constexpr bool traps             = false;
        static constexpr bool is_modulo         = false;
        static constexpr bool radix             = FLT_RADIX;

        static constexpr double min() noexcept { return DBL_MIN; }
        
        static constexpr double lowest() noexcept { return -DBL_MAX; }

        static constexpr double max() noexcept { return DBL_MAX; }

        static constexpr double epsilon() noexcept { return DBL_EPSILON; }

        static constexpr double round_error() noexcept { return 0.5; }

        static constexpr double infinity() noexcept { return __builtin_huge_val(); }

        static constexpr double quiet_NaN() noexcept { return __builtin_nan(""); }
    };
    template <>
    struct numeric_limits<long double>
    {
        static constexpr bool is_specialized    = true;
        static constexpr bool is_signed         = true;
        static constexpr bool is_integer        = false;
        static constexpr bool is_exact          = false;
        static constexpr bool is_iec559         = true;
        static constexpr bool has_infinity      = true;
        static constexpr bool has_quiet_NAN     = true;
        static constexpr bool has_signaling_NAN = true;
        static constexpr float_denorm_style has_denorm = denorm_present;
        static constexpr bool has_denorm_loss   = false;
        static constexpr float_round_style round_style = round_to_nearest;
        static constexpr bool is_bounded        = true;
        static constexpr int digits             = LDBL_MANT_DIG;
        static constexpr int digits10           = LDBL_DIG;
        static constexpr int min_exponent       = LDBL_MIN_EXP;
        static constexpr int max_exponent       = LDBL_MAX_EXP;
        static constexpr int min_exponent10     = LDBL_MIN_10_EXP;
        static constexpr int max_exponent10     = LDBL_MAX_10_EXP;
        static constexpr int max_digits10       = (int) 2 + digits * _std_copy_limits_log2;
        static constexpr bool traps             = false;
        static constexpr bool is_modulo         = false;
        static constexpr bool radix             = FLT_RADIX;

        static constexpr long double min() noexcept { return LDBL_MIN; }

        static constexpr long double lowest() noexcept { return -LDBL_MAX; }

        static constexpr long double max() noexcept { return LDBL_MAX; }

        static constexpr long double epsilon() noexcept { return LDBL_EPSILON; }

        static constexpr long double round_error() noexcept { return 0.5L; }

        static constexpr long double infinity() noexcept { return __builtin_huge_vall(); }

        static constexpr long double quiet_NaN() noexcept { return __builtin_nanl(""); }
    };
}

#endif /* _STD_COPY_LIMITS */