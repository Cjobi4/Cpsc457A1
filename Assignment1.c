#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

#define BUFFER_SIZE 64

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


    if (argc < 2 || argc > 9) {
        fprintf(stderr, "Usage: %s x1 [x2 ... x9]\n", argv[0]);
        return 1;
    }

    if(pipe(pipefd) < 0){
        fprintf(stderr, "Failed to complete pipe\n");
        exit(1);
    }

    for(i = 1; i < argc; i++){
        n = atoi(argv[i]);
        pid = fork();

        if (pid < 0) {
            fprintf(stderr, "Failed to fork process\n");
            exit(1);
        }

        if (pid == 0) {
            char write_buffer[BUFFER_SIZE]; /* This is going to be used to send the message to the pipe by the Child Process*/

            close(pipefd[0]); /*We are closing this because we dont need the child to read only write*/
            p_write = fdopen(pipefd[1], "w" );

            snprintf(write_buffer, BUFFER_SIZE, "%d %d %d\n", getpid(), n, fibonacci(n));
            fprintf(p_write, "%s", write_buffer);
            fclose(p_write);

            exit(0);
        }
    }

    close(pipefd[1]); /* Closing the writing and now going to reading */
    p_read = fdopen(pipefd[0], "r");

    /* This allows the parent to reach each childs answers from the pipe and then print it*/
    for(i = 1; i < argc; i++){
        int child_pid, num, answer;
        fscanf(p_read, "%d %d %d ", &child_pid, &num, &answer);
        printf("Child Process (PID %d) Fib{%d} = %d\n", child_pid, num, answer);
        
    }
    fclose(p_read);


    /* This is to make sure the parent waits for each child*/
    for(i = 1; i < argc; i++){
        wait(NULL);
    }

    return 0;
}