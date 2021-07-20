// swap_endian.h by katahiromz
#pragma once

#if __cplusplus >= 201103L /* C++11 */
    #include <cstdint>
#elif __STDC_VERSION__ >= 199901L /* C99 */
    #include <stdint.h>
#else
    #include "pstdint.h"
#endif

#if defined(__linux__) || defined(__ANDROID__)
    #include <endian.h>
#elif defined(__Apple__)
    #include <machine/endian.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__)
    #include <sys/endian.h>
#endif

#if !defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__) && !defined(__PDP_ENDIAN__)
    #if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
        #define __LITTLE_ENDIAN__
    #elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        #define __BIG_ENDIAN__
    #elif defined(__BYTE_ORDER__) && defined(__ORDER_PDP_ENDIAN__) && __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
        #define __PDP_ENDIAN__
    #elif defined(_WIN32) || defined(__i386__) || defined(__x86_64__)
        #define __LITTLE_ENDIAN__
    #else
        #error Please define either __LITTLE_ENDIAN__, __BIG_ENDIAN__, or __PDP_ENDIAN__.
    #endif
#endif

static __inline uint8_t swap_endian_8(uint8_t value)
{
    return value;
}

static __inline uint16_t swap_endian_16(uint16_t value)
{
    #ifdef _MSC_VER
        return _byteswap_ushort(value);
    #elif defined(__INTEL_COMPILER)
        return _bswap16(value);
    #elif defined(__Apple__)
        return Endian16_Swap(value);
    #elif defined(__GNUC__) || defined(__clang__)
        return __builtin_bswap16(value);
    #else
        const uint8_t lo = (uint8_t)value;
        const uint8_t hi = (uint8_t)(value >> 8);
        return (lo << 8) | (hi);
    #endif
}

static __inline uint32_t swap_endian_32(uint32_t value)
{
    #ifdef _MSC_VER
        return _byteswap_ulong(value);
    #elif defined(__INTEL_COMPILER)
        return _bswap(value);
    #elif defined(__Apple__)
        return Endian32_Swap(value);
    #elif defined(__GNUC__) || defined(__clang__)
        return __builtin_bswap32(value);
    #else
        const uint16_t lo = (uint16_t)value;
        const uint16_t hi = (uint16_t)(value >> 16);
        return (swap_endian_16(lo) << 16) | swap_endian_16(hi);
    #endif
}

static __inline uint64_t swap_endian_64(uint64_t value)
{
    #ifdef _MSC_VER
        return _byteswap_uint64(value);
    #elif defined(__INTEL_COMPILER)
        return _bswap64(value);
    #elif defined(__Apple__)
        return Endian64_Swap(value);
    #elif defined(__GNUC__) || defined(__clang__)
        return __builtin_bswap64(value);
    #else
        const uint32_t lo = (uint32_t)value;
        const uint32_t hi = (uint32_t)(value >> 32);
        return ((uint64_t)swap_endian_32(lo) << 32) | swap_endian_32(hi);
    #endif
}
