#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t count[20];

/* hash_long() function from Linux kernel */
uint32_t hash_long(uint32_t val, uint32_t bits)
{
    uint32_t hash = val * 0x9e370001UL;
    return hash >> (32 - bits);
}

int main(void)
{
    int i;

    /* 0~1024 ==> 0~8 */
    /* The generating random number of small range from wide range
     * can be done with hash_long().
     * But hash_long() can generate only bit range number:
     * 2bit, 3bit, 4bit ...
     */
    for (i = 0; i < 100000; i++) {
        int v = random() % 1024;
        int h = hash_long(v, 3);
        /* printf("r=%d h=%d\n", v, h); */
        count[h]++;
    };
    for (i = 0; i < 10; i++) {
        printf("count-%d=%d\n", i, count[i]);
        count[i] = 0;
    }

    srandom(time(NULL));

    /* This cannot be equally distributed.
     * Since 32/33/34/35 are generated and
     * 36, 37, 38, 39 are not generated,
     * 0/1/2/3 (after %8 operation)are more often than others.
     */
    for (i = 0; i < 1000000; i++) {
        /* generate random number 0 ~ 55(6) => 0 ~ 35 (decimal) */
        int v = (random() % 6) + ((random() % 6) * 6);
        int h = v % 8;
        count[h]++;
    };
    for (i = 0; i < 10; i++) {
        printf("count-%d=%d\n", i, count[i]);
        count[i] = 0;
    }

    /* This can be equally distributed.
     * Huge number 0 ~ 5555(6) are generated
     * and the difference of 0/1/2/3 and 4/5/6/7 can be ignored.
     * The range of the generated value can be arbitrary.
     */
    for (i = 0; i < 1000000; i++) {
        /* generate random number 0 ~ 5555(6) => 0 ~  (decimal) */
        int v = (random() % 6) + ((random() % 6) * 6) +
            ((random() % 6) * 36) + ((random() % 6) * 216);
        int h = v % 9;
        count[h]++;
    };
    for (i = 0; i < 10; i++) {
        printf("count-%d=%d\n", i, count[i]);
        count[i] = 0;
    }

    return 0;
}

/* test result:
  count-0=12765
count-1=12599
count-2=12384
count-3=12279
count-4=12552
count-5=12664
count-6=12298
count-7=12459
count-8=0
count-9=0
count-0=139272
count-1=138899
count-2=138371
count-3=139306
count-4=110507
count-5=110728
count-6=111656
count-7=111261
count-8=0
count-9=0
count-0=124452
count-1=124773
count-2=125012
count-3=125124
count-4=124931
count-5=125028
count-6=125613
count-7=125067
count-8=0
count-9=0
*/
