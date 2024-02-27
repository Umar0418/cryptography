#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Example block cipher (dummy function)
void block_cipher_encrypt(uint8_t *input, uint8_t *output, uint8_t *key) {
    // Dummy implementation, simply copying input to output
    memcpy(output, input, 8); // Assuming 8 bytes block size
}

void cbc_mac(uint8_t *message, uint8_t *key, uint8_t *mac) {
    uint8_t IV[8]; // Initialization Vector
    memset(IV, 0, sizeof(IV)); // Initializing IV with zeros

    uint8_t temp[8];
    block_cipher_encrypt(message, temp, key); // Encrypt the message block

    // XOR operation between the result of the encryption and IV
    for (int i = 0; i < 8; i++) {
        temp[i] ^= IV[i];
    }

    memcpy(mac, temp, 8); // Copying the resulting MAC
}

int main() {
    uint8_t key[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    uint8_t message[8] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
    uint8_t mac[8];

    // Computing MAC for one-block message
    cbc_mac(message, key, mac);
    printf("MAC for one-block message: ");
    for (int i = 0; i < 8; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    // Constructing two-block message X || (X ? T)
    uint8_t two_block_message[16];
    memcpy(two_block_message, message, 8); // First block is X
    for (int i = 0; i < 8; i++) {
        two_block_message[8 + i] = message[i] ^ mac[i]; // Second block is X ? T
    }

    // Computing MAC for two-block message
    cbc_mac(two_block_message, key, mac);
    printf("MAC for two-block message: ");
    for (int i = 0; i < 8; i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    return 0;
}

