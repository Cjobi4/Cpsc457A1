# Fibonacchi Sequence with Fork and Pipe

This is a prgram that computes the Fibonacci number for each command line argument given by the user. This is done by using a separate child process per argument, with results communicated back to the parent through a shared pipe. (The parent is the only thing fdoing the printing)

## Overview

The Idea of this program is to take every integer passed  in the argument, and call fork () to get a child process for each argument. What each child does:

1. They will compute the fibonacchi number of the argument they are given using the helper function 'fibonacchi'.
2. The it will get its pid from the fork, the input value/argument it worked on and then the result and send it to the pipe

The parent process reads each child's result from the pipe, printing it then waiting for all children to finish up.

## How to Build
In Terminal write

gcc Assignment1.c -o Assignment1

## Usage
In Terminal write 

./Assignment1 4 6 7 

The output will be 

Child Process (PID ....) Fib{4} = ....
Child Process (PID ....) Fib{6} = ....
Child Process (PID ....) Fib{7} = ....

The answer will be given when ran.