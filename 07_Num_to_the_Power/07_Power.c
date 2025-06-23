#include <stdio.h>

long power(long base, long n){
    long p;

    for (p = 1; n > 0; --n)
    {
        p = p*base;
    }
    
    printf("Para %ld^%ld ",base, n);

    return p;
}

int main(){

    printf("el resultado es: %ld\n", power(2,4));
    printf("el resultado es: %ld\n", power(8,4));
    printf("el resultado es: %ld\n", power(15,8));

    return 0;
}

