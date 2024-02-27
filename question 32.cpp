#include <openssl/dsa.h>

int main() {
    unsigned char message[] = "OpenSSL DSA Test";
    unsigned char hash[SHA_DIGEST_LENGTH];
    unsigned char *signature;
    unsigned int sig_len;
    DSA *dsa = DSA_new();

    // Generate DSA parameters
    DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL);

    // Generate DSA key pair
    DSA_generate_key(dsa);

    // Compute hash of the message
    SHA1(message, sizeof(message), hash);

    // Allocate memory for signature
    signature = (unsigned char *)malloc(DSA_size(dsa));

    // Sign the message
    DSA_sign(0, hash, SHA_DIGEST_LENGTH, signature, &sig_len, dsa);

    // Verify the signature
    int verified = DSA_verify(0, hash, SHA_DIGEST_LENGTH, signature, sig_len, dsa);
    if (verified == 1) {
        printf("DSA Signature verified successfully.\n");
    } else {
        printf("DSA Signature verification failed.\n");
    }

    // Free allocated memory
    DSA_free(dsa);
    free(signature);

    return 0;
}

