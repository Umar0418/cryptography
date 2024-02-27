#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define SIGN_LENGTH 256 // Length of the signature buffer

// Function to generate RSA key pair
RSA *generate_key_pair() {
    RSA *rsa_key = RSA_new();
    BIGNUM *bn = BN_new();
    unsigned long exponent = RSA_F4;

    if (!rsa_key || !bn) {
        printf("Error: Unable to allocate memory for RSA key generation.\n");
        return NULL;
    }

    BN_set_word(bn, exponent);
    if (!RSA_generate_key_ex(rsa_key, 2048, bn, NULL)) {
        printf("Error: RSA key generation failed.\n");
        return NULL;
    }

    BN_free(bn);
    return rsa_key;
}ure

// Function to generate digital signat
int generate_signature(const char *message, unsigned char *signature, RSA *rsa_key) {
    int signature_length = 0;
    unsigned int md_len;
    unsigned char md[SHA256_DIGEST_LENGTH];

    if (!RSA_sign(NID_sha256, (unsigned char *)message, strlen(message), md, &md_len, rsa_key)) {
        printf("Error: Unable to generate signature.\n");
        return -1;
    }

    if (!RSA_sign(NID_sha256, (unsigned char *)message, strlen(message), signature, &signature_length, rsa_key)) {
        printf("Error: Unable to generate signature.\n");
        return -1;
    }

    return signature_length;
}

int main() {
    RSA *rsa_key = NULL;
    unsigned char signature[SIGN_LENGTH];
    const char *message = "This is a test message for digital signature.";

    // Generate RSA key pair
    rsa_key = generate_key_pair();
    if (!rsa_key) {
        printf("Error: Unable to generate RSA key pair.\n");
        return -1;
    }

    // Generate digital signature
    int signature_length = generate_signature(message, signature, rsa_key);
    if (signature_length < 0) {
        printf("Error: Unable to generate digital signature.\n");
        RSA_free(rsa_key);
        return -1;
    }

    // Print signature
    printf("Digital Signature: ");
    for (int i = 0; i < signature_length; i++) {
        printf("%02X", signature[i]);
    }
    printf("\n");

    RSA_free(rsa_key);
    return 0;
}

