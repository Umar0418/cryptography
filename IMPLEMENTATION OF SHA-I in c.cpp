#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#define LE2BE64(a) \
a = ((a>>56)&0xff) | ((a>>40)&0xff00) | ((a>>24)&0xff0000) | ((a>>8)&0xff000000) | \
((a<<8)&0xff00000000) | ((a<<24)&0xff0000000000) | ((a<<40)&0xff000000000000) | \
((a<<56)&0xff00000000000000)

#define cycleWord(a, n) \
((a << n) | (a >> (32 - n)))

#define f0(B, C, D) \
((B & C) | ((~B) & D))

#define f13(B, C, D) \
(B ^ C ^ D)

#define f2(B, C, D)\
((B & C) | (B & D) | (C & D))

#define K0 0x5A827999
#define K1 0x6ED9EBA1
#define K2 0x8F1BBCDC
#define K3 0xCA62C1D6


uint32_t H0 = 0x67452301;
uint32_t H1 = 0xEFCDAB89;
uint32_t H2 = 0x98BADCFE;
uint32_t H3 = 0x10325476;
uint32_t H4 = 0xC3D2E1F0;

void padMessage(char *buf, uint64_t buflen) {
    uint64_t msg_len = strlen(buf);
    buf[msg_len] = 0x80;

    if((msg_len + 1) % 64 < 56) {
        for(int i = 0; i < 56 - (msg_len + 1); i++) {
            buf[msg_len + 1 + i] = 0x00;
        }
    } else {
        for(int i = 0; 1; i++) {
            buf[msg_len + 1 + i] = 0x00;
            if((msg_len + 2 + i) % 64 == 0)
                break;
        }
        for(int i = 64; buflen - i < buflen - 9; i--) {
            buf[buflen - i] = 0x00;
        }
    }

    LE2BE64(msg_len);
    memcpy(&buf[buflen - 8], &msg_len, 8);
}

void processBlock(unsigned char block[64]) {
    uint32_t W[80] = { 0 };
    uint32_t A, B, C, D, E, TEMP;

    for(int t = 0; t < 16; t++) {
        W[t] |= (uint32_t)block[t * 4];
        W[t] |= ((((uint32_t)block[t * 4 + 1])<<8)&0xff00);
        W[t] |= ((((uint32_t)block[t * 4 + 2])<<16)&0xff0000);
        W[t] |= ((((uint32_t)block[t * 4 + 3])<<24)&0xff000000);
    }

    for(int t = 16; t < 80; t++) {
        W[t] = cycleWord(W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16], 1);
    }

    A = H0;
    B = H1;
    C = H2;
    D = H3;
    E = H4;

    for(int t = 0; t < 20; t++) {
        TEMP = cycleWord(A, 5) + f0(B, C, D) + E + W[t] + K0;
        E = D;
        D = C;
        C = cycleWord(B, 30);
        B = A;
        A = TEMP;
    }    

    for(int t = 20; t < 40; t++) {
        TEMP = cycleWord(A, 5) + f13(B, C, D) + E + W[t] + K1;
        E = D;
        D = C;
        C = cycleWord(B, 30);
        B = A;
        A = TEMP;
    }    

    for(int t = 40; t < 60; t++) {
        TEMP = cycleWord(A, 5) + f2(B, C, D) + E + W[t] + K2;
        E = D;
        D = C;
        C = cycleWord(B, 30);
        B = A;
        A = TEMP;
    }    

    for(int t = 60; t < 80; t++) {
        TEMP = cycleWord(A, 5) + f13(B, C, D) + E + W[t] + K3;
        E = D;
        D = C;
        C = cycleWord(B, 30);
        B = A;
        A = TEMP;
    }    

    H0 = H0 + A;
    H1 = H1 + B;
    H2 = H2 + C;
    H3 = H3 + D;
    H4 = H4 + E;
}

void main(int argc, char *argv[]) {
    char *cmd_str;
    uint64_t buflen;
    if(argc < 2) {
        buflen = 0;
        cmd_str = calloc(buflen + 1, sizeof(char));
        cmd_str = "";
    } else {
        buflen = strlen(argv[1]);
        cmd_str = argv[1];
    }

    if(buflen % 64 < 56) {
        buflen = ((buflen / 64) + 1) * 64;
    } else {
        buflen = ((buflen / 64) + 2) * 64;
    }
    unsigned char *buffer = calloc(buflen, sizeof(unsigned char));
    strcpy(buffer, cmd_str);
    padMessage(buffer, buflen);

    unsigned char tmp[64];
    for(uint64_t i = 0; i < buflen / 64; i++) {
        memcpy(tmp, &buffer[i * 64], 64);
        processBlock(tmp);
    }
    
    printf("%x%x%x%x%x\n", H0, H1, H2, H3, H4);
}
