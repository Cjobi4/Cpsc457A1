#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    pid_t pid;

    if (argc < 2 || argc > 9) {
        fprintf(stderr, "Usage: %s x1 [x2 ... x9]\n", argv[0]);
        return 1;
    }

    for(int i = 1; i < argc; i++){
        int n = atoi(argv[i]);
        pid + fork();
    }

    int num = atoi(argv[1]);
    printf("Fibonacci of %d is: %d\n", num, fibonacci(num));
    return 0;
}