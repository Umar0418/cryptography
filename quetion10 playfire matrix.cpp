#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MATRIX_SIZE 5
void generatePlayfairMatrix(const char* key, char matrix[MATRIX_SIZE][MATRIX_SIZE]);
void encryptMessage(const char* message, const char matrix[MATRIX_SIZE][MATRIX_SIZE], char* encrypted);
int main() {
    const char key[] = "MFHI/JKUNOPQZVWXYZELARGDSTBC";
    char matrix[MATRIX_SIZE][MATRIX_SIZE];
    char message[] = "MustseeyouoverCadoganWest.Comingatonce.";
    char encrypted[1000];
    generatePlayfairMatrix(key, matrix);
    encryptMessage(message, matrix, encrypted);
	printf("Encrypted message: %s\n", encrypted);
	return 0;
}
void generatePlayfairMatrix(const char* key, char matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int i, j, k = 0;
    int key_length = strlen(key);
    int used[26] = {0}; 
	for (i = 0; i < key_length; i++) {
        char current = toupper(key[i]);
        if (current == 'J') current = 'I'; 
        if (!isalpha(current)) continue; 
		if (!used[current - 'A']) {
            matrix[k / MATRIX_SIZE][k % MATRIX_SIZE] = current;
            used[current - 'A'] = 1;
            k++;
        }
    }
    for (i = 0; i < 26; i++) {
        if (i != ('J' - 'A') && !used[i]) {
            matrix[k / MATRIX_SIZE][k % MATRIX_SIZE] = 'A' + i;
            k++;
        }
    }
}
void findPosition(const char matrix[MATRIX_SIZE][MATRIX_SIZE], char ch, int* row, int* col) {
    int i, j;
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptMessage(const char* message, const char matrix[MATRIX_SIZE][MATRIX_SIZE], char* encrypted) {
    int i, j;
    int len = strlen(message);
    int row1, col1, row2, col2;
    int idx = 0;
	for (i = 0; i < len; i += 2) {
        char ch1 = toupper(message[i]);
        char ch2 = (i + 1 < len) ? toupper(message[i + 1]) : 'X'; 
        if (ch1 == 'J') ch1 = 'I';
        if (ch2 == 'J') ch2 = 'I';
        findPosition(matrix, ch1, &row1, &col1);
        findPosition(matrix, ch2, &row2, &col2);
        if (row1 == row2) {
            encrypted[idx++] = matrix[row1][(col1 + 1) % MATRIX_SIZE];
            encrypted[idx++] = matrix[row1][(col2 + 1) % MATRIX_SIZE];
        }
        else if (col1 == col2) {
            encrypted[idx++] = matrix[(row1 + 1) % MATRIX_SIZE][col1];
            encrypted[idx++] = matrix[(row2 + 1) % MATRIX_SIZE][col1];
        }
        else {
            encrypted[idx++] = matrix[row1][col2];
            encrypted[idx++] = matrix[row2][col1];
        }
    }
    encrypted[idx] = '\0';
}
