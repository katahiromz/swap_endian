/* pstdint.h -- portable standard integers                      -*- C++ -*- */

#ifndef MZC4_PSTDINT_H_
#define MZC4_PSTDINT_H_  22 /* Version 22 */

#if __cplusplus >= 201103L /* C++11 */
    #include <cstdint>
#elif __STDC_VERSION__ >= 199901L /* C99 */
    #include <stdint.h>
#elif (defined(__WINDOWS_386__) || defined(_WIN32)) && !defined(WONVER)
    typedef signed char int8_t;
    typedef short int16_t;
    typedef int int32_t;
    typedef __int64 int64_t;
    typedef unsigned char uint8_t;
    typedef unsigned short uint16_t;
    typedef unsigned int uint32_t;
    typedef unsigned __int64 uint64_t;
    #ifdef _WIN64
        typedef __int64 intptr_t;
        typedef unsigned __int64 uintptr_t;
    #else
        typedef int intptr_t;
        typedef unsigned int uintptr_t;
    #endif
#else
    #ifdef __cplusplus
        #include <cstddef>
        #include <climits>
    #else
        #include <stddef.h>
        #include <limits.h>
    #endif
    typedef signed char int8_t;
    typedef unsigned char uint8_t;
    typedef short int16_t;
    typedef unsigned short uint16_t;
    #if defined(__DOS__) || defined(M_I86)
        typedef int           intptr_t;
        typedef long          int32_t;
        typedef unsigned int  uintptr_t;
        typedef unsigned long uint32_t;
    #else
        typedef int           int32_t;
        typedef unsigned int  uint32_t;
        #ifndef INT64_MAX
            #ifdef _I64_MAX
                #define INT64_MIN  _I64_MIN
                #define INT64_MAX  _I64_MAX
                #define UINT64_MAX _UI64_MAX
                typedef __int64          int64_t;
                typedef __int64          intptr_t;
                typedef unsigned __int64 uint64_t;
                typedef unsigned __int64 uintptr_t;
            #else
                #if defined(__LP64__) && !defined(__APPLE__)
                    #define INT64_MIN (-9223372036854775807L - 1)
                    #define INT64_MAX 9223372036854775807L
                    #define UINT64_MAX 0xFFFFFFFFFFFFFFFFL
                    typedef long          int64_t;
                    typedef unsigned long uint64_t;
                #else
                    #define INT64_MIN (-9223372036854775807LL - 1)
                    #define INT64_MAX 9223372036854775807LL
                    #define UINT64_MAX 0xFFFFFFFFFFFFFFFFLL
                    typedef long long          int64_t;
                    typedef unsigned long long uint64_t;
                #endif
                typedef long           intptr_t;
                typedef unsigned long  uintptr_t;
            #endif
        #endif
    #endif
#endif

#ifndef INT8_MIN
    #define INT8_MIN (-128)
    #define INT8_MAX 127
    #define UINT8_MAX 0xFF
#endif
#ifndef INT16_MIN
    #define INT16_MIN (-32768)
    #define INT16_MAX 32767
    #define UINT16_MAX 0xFFFF
#endif
#ifndef INT32_MIN
    #define INT32_MIN (-2147483647L - 1)
    #define INT32_MAX 2147483647L
    #define UINT32_MAX 0xFFFFFFFFL
#endif

typedef char PSTDINT_TEST_01_[(sizeof(int8_t) == 1) ? 1 : -1];
typedef char PSTDINT_TEST_02_[(sizeof(uint8_t) == 1) ? 1 : -1];
typedef char PSTDINT_TEST_03_[(sizeof(int16_t) == 2) ? 1 : -1];
typedef char PSTDINT_TEST_04_[(sizeof(uint16_t) == 2) ? 1 : -1];
typedef char PSTDINT_TEST_05_[(sizeof(int32_t) == 4) ? 1 : -1];
typedef char PSTDINT_TEST_06_[(sizeof(uint32_t) == 4) ? 1 : -1];
#if !defined(__DOS__) && !defined(M_I86)
    typedef char PSTDINT_TEST_07_[(sizeof(int64_t) == 8) ? 1 : -1];
    typedef char PSTDINT_TEST_08_[(sizeof(uint64_t) == 8) ? 1 : -1];
#endif
typedef char PSTDINT_TEST_09_[(sizeof(intptr_t) == sizeof(void *)) ? 1 : -1];
typedef char PSTDINT_TEST_10_[(sizeof(uintptr_t) == sizeof(void *)) ? 1 : -1];

#endif  /* ndef MZC4_PSTDINT_H_ */
