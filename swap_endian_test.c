// test for swap_endian
#include "swap_endian.h"
#include <stdio.h>
#include <assert.h>

int main(void)
{
#ifdef __LITTLE_ENDIAN__
    puts("little endian");
#elif defined(__BIG_ENDIAN__)
    puts("big endian");
#else
    puts("middle endian?");
#endif
    assert(swap_endian_8(0x11) == 0x11);
    assert(swap_endian_16(0x1122) == 0x2211);
    assert(swap_endian_32(0x11223344) == 0x44332211);
    assert(swap_endian_64(0x1122334455667788) == 0x8877665544332211);
    puts("OK");
    return 0;
}
