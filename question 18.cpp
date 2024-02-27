#include <stdio.h>
unsigned long long circularLeftShift28(unsigned long long val, int shift) {
    return ((val << shift) | (val >> (28 - shift))) & 0xFFFFFFF;
}

void generateSubkeys(unsigned long long initial_key, unsigned long long *subkeys) {
    unsigned long long key_left = (initial_key >> 28) & 0xFFFFFFF;
    unsigned long long key_right = initial_key & 0xFFFFFFF;

    for (int round = 0; round < 16; ++round) {
        int shift = (round == 0 || round == 1 || round == 8 || round == 15) ? 1 : 2;

        key_left = circularLeftShift28(key_left, shift);
        key_right = circularLeftShift28(key_right, shift);

        subkeys[round] = (key_left << 28) | key_right;
    }
}

int main() {
    unsigned long long initial_key = 0x0123456789ABCDE;
    unsigned long long subkeys[16];

    generateSubkeys(initial_key, subkeys);

    printf("Initial Key: %llX\n", initial_key);

    for (int round = 0; round < 16; ++round) {
        printf("Subkey %2d: %llX\n", round + 1, subkeys[round]);
    }

    return 0;
}
