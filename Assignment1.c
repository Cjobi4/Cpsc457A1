#include <stdio.h>
#include <stdlib.h>

/* Function to calculate the nth Fibonacci number */
int fibonacci(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 9) {
        fprintf(stderr, "Usage: %s x1 [x2 ... x9]\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);
    printf("Fibonacci of %d is: %d\n", num, fibonacci(num));
    return 0;
}