#include <stdio.h>
#include <stdint.h>

// Initial permutation table
const int initial_permutation_table[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};
const int expansion_table[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// Simplified DES key schedule
const int key_schedule[16] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

// Simplified DES S-boxes
const int sbox[8][4][16] = {
    // S-box 1
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    // S-box 2
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    // S-box 3
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    // S-box 4
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    // S-box 5
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    // S-box 6
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    // S-box 7
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    // S-box 8
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};

// Permutation table after S-box substitution
const int permutation_table[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

// Perform permutation according to specified table
void permute(const uint32_t *input, uint32_t *output, const int *table, int size) {
    for (int i = 0; i < size; ++i) {
        int bit = table[i] - 1;
        int index = bit / 32;
        int offset = bit % 32;
        output[i] = (input[index] >> (32 - offset - 1)) & 0x01;
    }
}

// Perform initial permutation
void initial_permutation(const uint32_t *input, uint32_t *output) {
    permute(input, output, initial_permutation_table, 64);
}

// Perform expansion permutation
void expansion_permutation(const uint32_t *input, uint32_t *output) {
    permute(input, output, expansion_table, 48);
}

// Perform S-box substitution
void sbox_substitution(const uint32_t *input, uint32_t *output) {
    for (int i = 0; i < 8; ++i) {
        int row = (input[i * 6] << 1) + input[i * 6 + 5];
        int col = (input[i * 6 + 1] << 3) + (input[i * 6 + 2] << 2) + (input[i * 6 + 3] << 1) + input[i * 6 + 4];
        int val = sbox[i][row][col];
        for (int j = 0; j < 4; ++j) {
            output[i * 4 + j] = (val >> (3 - j)) & 0x01;
        }
    }
}

// Perform permutation after S-box substitution
void post_sbox_permutation(const uint32_t *input, uint32_t *output) {
    permute(input, output, permutation_table, 32);
}

// Encrypt a block of data using DES
void des_encrypt_block(const uint64_t *block, const uint64_t *key, uint64_t *output) {
    uint32_t expanded[48];
    uint32_t permuted[32];
    uint32_t sboxed[32];
    uint32_t post_sboxed[32];
    initial_permutation(block, permuted);
    expansion_permutation(permuted, expanded);
    for (int i = 0; i < 16; ++i) {
        uint32_t round_key[48]; // Generate round key using simplified key schedule
        // Generate round key (same for all rounds in this simplified version)
        for (int j = 0; j < 48; ++j) {
            round_key[j] = (key[j / 4] >> (31 - (j % 4) * 8)) & 0x01;
        }
        // XOR with round key
        for (int j = 0; j < 48; ++j) {
            expanded[j] ^= round_key[j];
        }
        sbox_substitution(expanded, sboxed);
        post_sbox_permutation(sboxed, post_sboxed);
        // XOR with permuted input
        for (int j = 0; j < 32; ++j) {
            post_sboxed[j] ^= permuted[j];
        }
        // Swap permuted and post-sboxed for next round
        for (int j = 0; j < 32; ++j) {
            permuted[j] = post_sboxed[j];
        }
    }
    // Final permutation (inverse initial permutation)
    permute(post_sboxed, output, initial_permutation_table, 64);
}

int main() {
    uint64_t block = 0x0123456789ABCDEF;
    uint64_t key = 0x133457799BBCDFF1; // 56-bit key
    uint64_t ciphertext;
    
    des_encrypt_block(&block, &key, &ciphertext);
    printf("Ciphertext: %016llx\n", ciphertext);
    
    return 0;
}

