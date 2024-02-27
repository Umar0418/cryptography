#include <stdio.h>
#include <stdlib.h> // Include stdlib.h for malloc function
#include <string.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26

char* encrypt(char* plaintext, char* key) {
    int i;
    int len = strlen(plaintext);

    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            if (islower(plaintext[i])) {
                ciphertext[i] = tolower(key[plaintext[i] - 'a']);
            } else {
                ciphertext[i] = toupper(key[plaintext[i] - 'A']);
            }
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[len] = '\0';
    return ciphertext;
}

int main() {
    char plaintext[1000];
    char key[ALPHABET_LENGTH + 1]; // We'll use this as the substitution key

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove trailing newline if present

    printf("Enter the substitution key (26 unique characters): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove trailing newline if present

    // Validate the key
    if (strlen(key) != ALPHABET_LENGTH) {
        printf("Error: Key must be exactly 26 characters long.\n");
        return 1;
    }
    for (int i = 0; i < ALPHABET_LENGTH; i++) {
        if (!isalpha(key[i])) {
            printf("Error: Key must contain only alphabetic characters.\n");
            return 1;
        }
        key[i] = toupper(key[i]); // Convert the key to uppercase
    }

    char* ciphertext = encrypt(plaintext, key);
    printf("Encrypted text: %s\n", ciphertext);

    free(ciphertext); // Free dynamically allocated memory
    return 0;
}

