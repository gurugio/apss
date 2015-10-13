#include <stdio.h>


int bitCount(int x)
{
    if (x == 0) return 0;
    return (x & 0x1) + bitCount(x >> 1);
}

int main(void)
{
    printf("%d\n", bitCount(0x34));
    printf("%d\n", bitCount(0xa5));
    printf("%d\n", bitCount(0x5a));
    printf("%d\n", bitCount(0x17));
    printf("%d\n", bitCount(0xa517));
    return 0;
}

