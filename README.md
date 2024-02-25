# Memory Management in C

## Overview
This project explores memory management in C through a series of steps, each building on the concepts of dynamic memory allocation, deallocation, and management strategies.

## Steps Overview
- `step1.c`: Tests the initialization and cleanup of a simulated memory block.
- `step2.c`: Demonstrates stack-based memory allocation for string storage.
- `step3.c`: Implements heap allocation strategy, including allocation and deallocation of strings.
- `step4.c`: Engages heap memory management in an interactive session with the user, handling dynamic input.

## Compilation and Execution
Compile the files using:
```
gcc -o step1 step1.c functions.c -Wall
gcc -o step2 step2.c functions.c -Wall
gcc -o step3 step3.c functions.c -Wall
gcc -o step4 step4.c functions.c -Wall
```

Run each step as needed:
```
./step1
./step2
./step3
./step4
```

## Important Concepts Demonstrated
- Memory allocation (`malloc`, `calloc`) and deallocation (`free`).
- Handling of null pointers and memory leaks.
- User interaction with dynamic memory within a simulated environment.