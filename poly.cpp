#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encrypt(char* plainText, char* key) {
    char cipherText[100];
    int i, j = 0, keyLen = strlen(key), textLen = strlen(plainText);

    for(i = 0; i < textLen; ++i){
        if(isalpha(plainText[i])) {
            char offset = isupper(plainText[i]) ? 'A' : 'a';
            cipherText[i] = ((plainText[i] - offset + (toupper(key[j]) - 'A')) % 26) + offset;
            j = (j + 1) % keyLen;
        } else {
            cipherText[i] = plainText[i];
        }
    }
    cipherText[i] = '\0';
    printf("Cipher Text: %s\n", cipherText);
}

int main() {
    char key[50];
    char plainText[100];
    printf("Enter the key: ");
    scanf("%s", key);
    printf("Enter the Plain Text: ");
    scanf("%s", plainText);
    encrypt(plainText, key);
    return 0;
}

