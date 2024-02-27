#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_LENGTH 26

char* encrypt(char* plaintext, char* key) {
    int pt_len = strlen(plaintext);
    int key_len = strlen(key);
    char* ciphertext = (char*)malloc(pt_len + 1);
    int i;

    for (i = 0; i < pt_len; i++) {
        char pt_char = plaintext[i];
        char key_char = key[i % key_len];
        if (isalpha(pt_char)) {
            int shift = (tolower(pt_char) - 'a' + tolower(key_char) - 'a') % ALPHABET_LENGTH;
            ciphertext[i] = islower(pt_char) ? 'a' + shift : 'A' + shift;
        } else {
            ciphertext[i] = pt_char;
        }
    }
    ciphertext[pt_len] = '\0';
    return ciphertext;
}

int main() {
    char plaintext[1000];
    char key[100];
    
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove trailing newline if present

    char* ciphertext = encrypt(plaintext, key);
    printf("Encrypted text: %s\n", ciphertext);

    free(ciphertext); // Free dynamically allocated memory
    return 0;
}


