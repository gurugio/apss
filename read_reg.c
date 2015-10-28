#include <stdio.h>
#include <stdint.h>


/*
 * reg is increased monotonicly.
 * When reg == 0x12ff, read_high() returns 0x12
 * and reg is increased so that read_low() returns 0x00.
 * Result value is 0x1200.
 * Therefore another checking of high value is necessary.
 */
uint16_t reg;

uint8_t read_low(void)
{
    return (uint8_t)reg & 0xff;
}

uint8_t read_high(void)
{
    return (uint8_t)(reg >> 8);
}

int main(void)
{
    int8_t h, l;
    reg = 0x12ff;
    printf("%x %x\n", read_high(), read_low());

    h = read_high();
    reg++;
    l = read_low();
    printf("%x,%x %x,%x\n", h, read_high(), l, read_low());
    reg++;

    if (read_high() != h) {
        reg++;
        h = read_high();
        reg++;
        l = read_low();
        reg++;
        printf("%x,%x %x,%x\n", h, read_high(), l, read_low());
    }

    return 0;
}
