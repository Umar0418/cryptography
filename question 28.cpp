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
}
