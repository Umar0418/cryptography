#include <stdio.h>
#include <string.h>

// Function to encrypt the plaintext using the one-time pad Vigenère cipher
void encrypt(char *plaintext, int *key, int key_length) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            // Apply the shift corresponding to the key
            plaintext[i] = ((plaintext[i] - 'A' + key[i % key_length]) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            // Apply the shift corresponding to the key
            plaintext[i] = ((plaintext[i] - 'a' + key[i % key_length]) % 26) + 'a';
        }
    }
}

// Function to decrypt the ciphertext using the one-time pad Vigenère cipher
void decrypt(char *ciphertext, int *key, int key_length) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            // Apply the reverse shift corresponding to the key
            ciphertext[i] = ((ciphertext[i] - 'A' - key[i % key_length] + 26) % 26) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            // Apply the reverse shift corresponding to the key
            ciphertext[i] = ((ciphertext[i] - 'a' - key[i % key_length] + 26) % 26) + 'a';
        }
    }
}

int main() {
    char plaintext[] = "sendmoremoney";
    int key1[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9}; // Key stream for encryption
    int key2[] = {19, 18, 4, 14, 13, 4, 24, 17, 4, 3, 24, 4, 3}; // Example key for decryption
    int key_length = sizeof(key1) / sizeof(key1[0]);

    char ciphertext[strlen(plaintext) + 1]; // +1 for the null terminator
    char decryptedtext[strlen(plaintext) + 1]; // +1 for the null terminator

    printf("Plaintext: %s\n", plaintext);

    // Encrypt the plaintext
    strcpy(ciphertext, plaintext); // Copy plaintext to ciphertext to preserve original
    encrypt(ciphertext, key1, key_length);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    strcpy(decryptedtext, ciphertext); // Copy ciphertext to decryptedtext to preserve original
    decrypt(decryptedtext, key2, key_length);
    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

