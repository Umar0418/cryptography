#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Function to count the frequency of letters in a given text
void countFrequency(const char *text, int *frequency) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            frequency[text[i] - 'a']++;
        } else if (text[i] >= 'A' && text[i] <= 'Z') {
            frequency[text[i] - 'A']++;
        }
    }
}

// Function to decrypt the ciphertext using a given key
void decrypt(const char *ciphertext, int key) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            printf("%c", ((ciphertext[i] - 'a' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a');
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            printf("%c", ((ciphertext[i] - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A');
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

// Function to perform frequency attack and print top n possible plaintexts
void frequencyAttack(const char *ciphertext, int n) {
    int frequency[ALPHABET_SIZE] = {0};
    countFrequency(ciphertext, frequency);

    printf("Possible plaintexts in rough order of likelihood:\n");

    int i, j;
    for (i = 0; i < n; i++) {
        int maxIndex = 0;
        for (j = 1; j < ALPHABET_SIZE; j++) {
            if (frequency[j] > frequency[maxIndex]) {
                maxIndex = j;
            }
        }

        printf("[%d] Key = %d: ", i + 1, maxIndex);
        decrypt(ciphertext, maxIndex);

        frequency[maxIndex] = 0; // Set the frequency of the max occurrence to 0 to find next max
    }
}

int main() {
    const char *ciphertext = "Khoor zruog";
    int n = 10; // Number of possible plaintexts to print

    printf("Ciphertext: %s\n", ciphertext);
    frequencyAttack(ciphertext, n);

    return 0;
}

