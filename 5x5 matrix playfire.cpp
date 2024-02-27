#include <stdio.h>

// Function to perform modular exponentiation (a^b mod m)
long long power_mod(long long a, long long b, long long m) {
    long long result = 1;
    a %= m;

    while (b > 0) {
        if (b & 1) {
            result = (result * a) % m;
        }
        a = (a * a) % m;
        b >>= 1;
    }

    return result;
}

int main() {
    // Public parameters
    long long prime_modulus = 23; // Prime modulus (q)
    long long generator = 5; // Generator (a)

    // Alice's secret number
    long long alice_secret = 6; // Private key (x) for Alice

    // Bob's secret number
    long long bob_secret = 15; // Private key (x) for Bob

    // Calculate public values exchanged between Alice and Bob
    long long alice_public = alice_secret * generator % prime_modulus; // x * a mod q
    long long bob_public = bob_secret * generator % prime_modulus; // x * a mod q

    // Exchange public values between Alice and Bob

    // Compute shared secret key by both Alice and Bob
    long long shared_secret_alice = power_mod(bob_public, alice_secret, prime_modulus); // (x_b * a)^x_a mod q
    long long shared_secret_bob = power_mod(alice_public, bob_secret, prime_modulus); // (x_a * a)^x_b mod q

    printf("Shared secret key (Alice): %lld\n", shared_secret_alice);
    printf("Shared secret key (Bob): %lld\n", shared_secret_bob);

    return 0;
}#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char matrix[SIZE][SIZE];

void generateMatrix(char key[]) {
    int i, j, k;
    char *tempKey = (char *)calloc(26, sizeof(char));
    strcpy(tempKey, key);
    strcat(tempKey, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            for (k = 0; k < 26; k++) {
                if (tempKey[k] == 'J')
                    tempKey[k] = 'I';
                if (!matrix[i][j]) {
                    matrix[i][j] = tempKey[k];
                    break;
                }
            }
        }
    }
    free(tempKey);
}

void printMatrix() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void prepareInput(char text[], char newText[]) {
    int i, j;
    int k = 0;
    for (i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            newText[k++] = toupper(text[i]);
        }
    }
    newText[k] = '\0';
    for (i = 0; i < strlen(newText); i += 2) {
        if (newText[i] == newText[i + 1]) {
            for (j = strlen(newText); j > i + 1; j--) {
                newText[j] = newText[j - 1];
            }
            newText[i + 1] = 'X';
            newText[strlen(newText) + 1] = '\0';
        }
    }
    if (strlen(newText) % 2 != 0) {
        newText[strlen(newText) + 1] = '\0';
        newText[strlen(newText)] = 'X';
    }
}

void encrypt(char text[]) {
    char newText[100];
    prepareInput(text, newText);
    int i, j;
    int row1, col1, row2, col2;
    for (i = 0; i < strlen(newText); i += 2) {
        for (j = 0; j < SIZE; j++) {
            if (strchr(matrix[j], newText[i])) {
                row1 = j;
                col1 = strchr(matrix[j], newText[i]) - matrix[j];
            }
            if (strchr(matrix[j], newText[i + 1])) {
                row2 = j;
                col2 = strchr(matrix[j], newText[i + 1]) - matrix[j];
            }
        }
        if (row1 == row2) {
            printf("%c%c", matrix[row1][(col1 + 1) % SIZE], matrix[row2][(col2 + 1) % SIZE]);
        } else if (col1 == col2) {
            printf("%c%c", matrix[(row1 + 1) % SIZE][col1], matrix[(row2 + 1) % SIZE][col2]);
        } else {
            printf("%c%c", matrix[row1][col2], matrix[row2][col1]);
        }
    }
}

int main() {
    char key[100], text[100];
    printf("Enter the key: ");
    scanf("%s", key);
    generateMatrix(key);
    printf("Playfair Matrix:\n");
    printMatrix();
    printf("\nEnter the text to encrypt: ");
    getchar(); // to clear input buffer
    fgets(text, sizeof(text), stdin);
    printf("Encrypted text: ");
    encrypt(text);
    printf("\n");
    return 0;
}

