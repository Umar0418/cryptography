#include <stdio.h>
#include <stdint.h>

// Constants needed for block sizes of 64 and 128 bits
const uint64_t CONST_R64 = 0x1B;  // Constant for 64-bit block size
const uint64_t CONST_R128 = 0x87; // Constant for 128-bit block size

// Function to perform left shift on a block
uint64_t leftShift(uint64_t block, int shift) {
    return (block << shift) | (block >> (64 - shift)); // Rotate left
}

// Function to generate subkey
uint64_t generateSubkey(uint64_t key, int blockSize) {
    uint64_t subkey;
    if (blockSize == 64) {
        if (key & 0x8000000000000000) {
            subkey = (key << 1) ^ CONST_R64;
        } else {
            subkey = key << 1;
        }
    } else if (blockSize == 128) {
        if (key & 0x80000000000000000000000000000000) {
            subkey = (key << 1) ^ CONST_R128;
        } else {
            subkey = key << 1;
        }
    }
    return subkey;
}

int main() {
    uint64_t key = 0x00; // Key derived from a block of all zeros
    int blockSize = 64;  // Change to 128 for a block size of 128 bits

    // Generate and print the first subkey
    uint64_t subkey1 = generateSubkey(key, blockSize);
    printf("First Subkey: 0x%.16lX\n", subkey1);

    // Generate and print the second subkey
    uint64_t subkey2 = generateSubkey(subkey1, blockSize);
    printf("Second Subkey: 0x%.16lX\n", subkey2);

    return 0;
}

