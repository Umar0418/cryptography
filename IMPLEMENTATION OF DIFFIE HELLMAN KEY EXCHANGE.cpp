#include<stdio.h>
#include<math.h>

// Function to compute a^m mod n
long long int power(long long int a, long long int b, long long int P)
{ 
    if (b == 1)
        return a;
    else
        return (((long long int)pow(a, b)) % P);
}

int main()
{
    long long int P, G, x, a, y, b, ka, kb; 

    printf("Enter a prime number P: ");
    scanf("%lld",&P);

    printf("Enter a primitive root for P, G: ");
    scanf("%lld",&G);

    printf("Alice will choose the private key a: ");
    scanf("%lld",&a);
    x = power(G, a, P); // gets the generated key

    printf("Bob will choose the private key b: ");
    scanf("%lld",&b);
    y = power(G, b, P); // gets the generated key

    // Generating the secret key after the exchange of keys
    ka = power(y, a, P); // Secret key for Alice
    kb = power(x, b, P); // Secret key for Bob

    printf("Secret key for the person1 is : %lld\n", ka);
    printf("Secret key for the person2 is : %lld\n", kb);

    return 0;
}

