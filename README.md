# Maze-Generator-Solver
A program that both generates a maze of custom size (upto 245 by 245) and then solves it, both using my own version of the depth first search algorithm.

### Algorithm 
For maze generation, the program first creates a path in a small square grid of size n using recursive backtracking. Then, the maze is 'carved' into a bigger square grid of size
2n - 1. After adding external border, the size of the maze becomes (2n • 1) × (2n - 1). The program uses recursive backtracking for solving as well. Whenever it reaches a dead-end, it backtracks to the last fork in the path. Once it reaches the end, the correct
path is stored and the robot is animated.
