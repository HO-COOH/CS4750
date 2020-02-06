# Homework 4 - Fall 2019
Use the minimax algorithm to find the optimal moves for a game of Nim.

---

## Project Overview
The source file in /src folder is a Visual studio 2019 solution file.
/src/HW4/HW4 -source code
/src/Release -the executable in Windows platform
#### Team Members:
Wenhao Li

#### Language/Environment Used:
C++/Windows X64

#### Description of Implementation:
Node.h - a vector of piles of sticks, functions for taking either one or two sticks and result comparing printing functions
Timer.h -an object to measure the cpu execution time used in one round of entire minimax search
Minimax search is implemented in a recursive function - recursively find the min or max values of the expanded nodes

#### System Hardware:
AMD Ryzen 7 CPU
(But I didn't use multi-threaded functions, so it shouldn't matter very much)

---

## Solutions

### Game 1: Nim(3, 4, 5)
1. __Player Move 1__:(1,4,5)
2. __Program Move 1__:(1,4,4)
    - Nodes Searched: 10784
    - CPU Execution Time: 0.077s
3. __Player Move 2__:(1,2,4)
4. __Program Move 2__:(1,1,4)
    - Nodes Searched: 503
    - CPU Execution Time: 0.077s
5. __Player Move 3__:(1,1,2)
6. __Program Move 3__:(1,1,1)
    - Nodes Searched: 17
    - CPU Execution Time: 0.001s
7. __Player Move 4__:(0,1,1)
8. __Program Move 4__:(0,0,1)
    - Nodes Searched: 2
    - CPU Execution Time: 0.001s


### Game 2: Nim(2, 3, 4, 5)
1. __Player Move 1__:(2,3,4,3)
2. __Program Move 1__:(0,3,4,3)
    - Nodes Searched: 143919
    - CPU Execution Time: 1.432s
3. __Player Move 2__:(0,1,4,3)
4. __Program Move 2__:(0,0,4,3)
    - Nodes Searched: 1397
    - CPU Execution Time: 0.013s
5. __Player Move 3__:(0,0,4,1)
6. __Program Move 3__:(0,0,3,1)
    - Nodes Searched: 43
    - CPU Execution Time: 0.001s
7. __Player Move 4__:(0,0,2,1)
8. __Program Move 4__:(0,0,0,1)
    - Nodes Searched: 9
    - CPU Execution Time: 0.001s

