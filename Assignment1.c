#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

#define Buffer_size 64

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
    int n;
    int i;
    int pipefd[2];
    FILE *p_read, *p_write;

    if(pipe(pipefd) < 0){
        fprintf(stderr, "Failed to complete pipe\n");
        exit(1);
    }

    if (argc < 2 || argc > 9) {
        fprintf(stderr, "Usage: %s x1 [x2 ... x9]\n", argv[0]);
        return 1;
    }

    for(i = 1; i < argc; i++){
        n = atoi(argv[i]);
        pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Failed to fork process\n");
            exit(1);
        }

        if (pid == 0) {
            printf("Child Process (PID %d) F{%d} = %d\n", getpid(), n, fibonacci(n));
            exit(0);
        }
    }

    /* This is to make sure the parent waits for each child*/
    for(i = 1; i < argc; i++){
        wait(NULL);
    }

    return 0;
}