/* swap_endian.h by katahiromz --- endianness-related C/C++ code collection */
/* See also: https://sourceforge.net/p/predef/wiki/Endianness/ */
#pragma once

/* Include <stdint.h> or something */
#if __cplusplus >= 201103L /* C++11 */
    #include <cstdint>
#elif __STDC_VERSION__ >= 199901L /* C99 */
    #include <stdint.h>
#else
    #include "pstdint.h"
#endif

/* Include endian header */
#if defined(__linux__) || defined(__ANDROID__)
    #include <endian.h>
#elif defined(__Apple__)
    #include <machine/endian.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
    #include <sys/endian.h>
#endif

/* Check __BYTE_ORDER and __BYTE_ORDER__ macros */
#if !defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__) && !defined(__PDP_ENDIAN__) && !defined(__BI_ENDIAN__) && !defined(__BIG_WORD_ENDIAN__)
    #ifdef __BYTE_ORDER
        #if (__BYTE_ORDER == __LITTLE_ENDIAN)
            #define __LITTLE_ENDIAN__ 1
        #elif  (__BYTE_ORDER == __BIG_ENDIAN)
            #define __BIG_ENDIAN__ 1
        #elif  (__BYTE_ORDER == __PDP_ENDIAN)
            #define __PDP_ENDIAN__ 1
        #endif
    #elif defined(__BYTE_ORDER__)
        #if defined(__ORDER_LITTLE_ENDIAN__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
            #define __LITTLE_ENDIAN__ 1
        #elif defined(__ORDER_BIG_ENDIAN__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
            #define __BIG_ENDIAN__ 1
        #elif defined(__ORDER_PDP_ENDIAN__) && (__BYTE_ORDER__ == __ORDER_PDP_ENDIAN__)
            #define __PDP_ENDIAN__ 1
        #endif
    #else
        /* Define __BI_ENDIAN__ if necessary */
        #if defined(__arm__) || defined(__aarch64__)
            #define __BI_ENDIAN__
        #elif defined(__ppc__) || defined(__powerpc) || defined(__powerpc__) || defined(__POWERPC__) || defined(_ARCH_PPC)
            #define __BI_ENDIAN__
        #elif defined(mips) || defined(__mips) || defined(__mips__) || defined(__MIPS__)
            #define __BI_ENDIAN__
        #elif defined(__alpha) || defined(__alpha__)
            #define __BI_ENDIAN__
        #elif defined(__sparc) || defined(__sparc__)
            #define __BI_ENDIAN__
        #endif
    #endif
#endif

/* Finish endianness detection at compile-time */
#if !defined(__LITTLE_ENDIAN__) && !defined(__BIG_ENDIAN__) && !defined(__PDP_ENDIAN__) && !defined(__BI_ENDIAN__) && !defined(__BIG_WORD_ENDIAN__)
    #if defined(_WIN64) || defined(__x86_64__) || defined(__x86_64) || defined(__amd64__)
        #define __LITTLE_ENDIAN__ 1
    #elif defined(__ia64__) || defined(__ia64) || defined(__itanium__)
        #define __LITTLE_ENDIAN__ 1
    #elif defined(__WINDOWS__) || defined(__WINDOWS_386__) || defined(_WIN32) || defined(__i386__)
        #define __LITTLE_ENDIAN__ 1
    #elif defined(__DOS__) || defined(M_I86)
        #define __LITTLE_ENDIAN__ 1
    #elif defined(__ARMEL__) || defined(__THUMBEL__) || defined(__AARCH64EL__)
        #define __LITTLE_ENDIAN__ 1
    #elif defined(_MIPSEL) || defined(__MIPSEL) || defined(__MIPSEL__)
        #define __LITTLE_ENDIAN__ 1
    #elif defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__)
        #define __BIG_ENDIAN__ 1
    #elif defined(_MIPSEB) || defined(__MIPSEB) || defined(__MIPSEB)
        #define __BIG_ENDIAN__ 1
    #else
        #error Please define either __LITTLE_ENDIAN__, __BIG_ENDIAN__, __PDP_ENDIAN__, __BI_ENDIAN__ or __BIG_WORD_ENDIAN__.
    #endif
#endif

typedef enum ENDIANNESS
{
    ENDIAN_UNKNOWN,
    ENDIAN_BIG,
    ENDIAN_LITTLE,
    ENDIAN_BIG_WORD,   /* Middle-endian, Honeywell 316 style */
    ENDIAN_LITTLE_WORD /* Middle-endian, PDP-11 style */
} ENDIANNESS;

/* endianness() function */
static __inline ENDIANNESS endianness(void)
{
    union
    {
        uint32_t value;
        uint8_t data[sizeof(uint32_t)];
    } number;

    number.data[0] = 0x00;
    number.data[1] = 0x01;
    number.data[2] = 0x02;
    number.data[3] = 0x03;

    switch (number.value)
    {
    case 0x00010203: return ENDIAN_BIG;
    case 0x03020100: return ENDIAN_LITTLE;
    case 0x02030001: return ENDIAN_BIG_WORD;
    case 0x01000302: return ENDIAN_LITTLE_WORD;
    default: return ENDIAN_UNKNOWN;
    }
}

/* COMPILETIME_ENDIANNESS macro */
#ifdef __LITTLE_ENDIAN__
    #define COMPILETIME_ENDIANNESS ENDIAN_LITTLE
#elif defined(__BIG_ENDIAN__)
    #define COMPILETIME_ENDIANNESS ENDIAN_BIG
#elif defined(__BIG_WORD_ENDIAN__)
    #define COMPILETIME_ENDIANNESS ENDIAN_BIG_WORD
#elif defined(__PDP_ENDIAN__)
    #define COMPILETIME_ENDIANNESS ENDIAN_LITTLE_WORD
#else
    #define COMPILETIME_ENDIANNESS endianness()
#endif

/*
 * swap_endian_8/16/32/64 inline functions
 */
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

#if !defined(__DOS__) && !defined(M_I86)
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
#endif
