#include <stdio.h>
#include <string.h>

#define SIZE 5

// Function to find the position of a character in the key square
void findPosition(char keySquare[SIZE][SIZE], char letter, int *row, int *col) {
    if (letter == 'J') // Replacing 'J' with 'I'
        letter = 'I';

    for (*row = 0; *row < SIZE; (*row)++)
        for (*col = 0; *col < SIZE; (*col)++)
            if (keySquare[*row][*col] == letter)
                return;
}

// Function to decrypt using Playfair Cipher
void decrypt(char *msg, char key[]) {
    // Key Square
    char keySquare[SIZE][SIZE];
    int i, j, k, len, row1, row2, col1, col2;

    // Assigning letters of the key to the key square
    k = 0;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++) {
            keySquare[i][j] = key[k++];
        }

    // Message length
    len = strlen(msg);

    // Adjusting the message
    for (i = 0; i < len; i++) {
        if (msg[i] == ' ') {
            for (j = i; j < len; j++) {
                msg[j] = msg[j + 1];
            }
            len--;
        }
    }

    // Decrypting the message
    for (i = 0; i < len; i += 2) {
        findPosition(keySquare, msg[i], &row1, &col1);
        findPosition(keySquare, msg[i + 1], &row2, &col2);

        if (row1 == row2) {
            printf("%c%c", keySquare[row1][(col1 - 1 + SIZE) % SIZE], keySquare[row2][(col2 - 1 + SIZE) % SIZE]);
        } else if (col1 == col2) {
            printf("%c%c", keySquare[(row1 - 1 + SIZE) % SIZE][col1], keySquare[(row2 - 1 + SIZE) % SIZE][col2]);
        } else {
            printf("%c%c", keySquare[row1][col2], keySquare[row2][col1]);
        }
    }
}

int main() {
    char message[] = "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ";
    char key[] = "PLAYFIREXMBCDGHKNOQSTUVWZ";

    printf("Decrypted message:\n");
    decrypt(message, key);

    return 0;
}

