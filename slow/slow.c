#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const long long DELAY_ITER = 7203796438858066709ULL;  // 21

uint8_t slow_add(uint8_t c) {
    volatile uint8_t res = c;
    for (uint64_t i = 0; i < DELAY_ITER; i++) {
        res = (uint8_t)(res + 1);
    }
    return res;
}

int main(void) {
    unsigned char encoded[] = {
        0x16, 0x01, 0x09, 0x04, 0x74, 0x65, 0x6B, 0x3C,
        0x05, 0x09, 0x16, 0x03, 0x0C, 0x04, 0x10, 0x16,
        0x01, 0x01, 0x07, 0x0A, 0x14, 0x0E, 0x16, 0x05,
        0x0A, 0x10, 0x0E, 0x05, 0x10, 0x46, 0x46, 0x14,
        0x44, 0x7A, 0x16, 0x15, 0x79, 0x0B, 0x7E, 0x32
    };
    size_t len = sizeof(encoded);

    char *decoded = malloc(len + 1);
    if (!decoded) return 1;

    for (size_t i = 0; i < len; i++) {
        uint8_t temp = encoded[i] ^ 0x5A;
        decoded[i] = slow_add(temp);
    }
    decoded[len] = '\0';

    printf("%s\n", decoded);
    free(decoded);
    return 0;
}

