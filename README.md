# Maze-Generator-Solver
A program that both generates a maze of custom size (upto 245 by 245) and then solves it, both using my own version of the depth first search algorithm.

### Algorithm 
For maze generation, the program first creates a path in a small square grid of size n using recursive backtracking. Then, the maze is 'carved' into a bigger square grid of size
2n - 1. After adding external border, the size of the maze becomes (2n - 1) × (2n - 1). The program uses recursive backtracking for solving as well. Whenever it reaches a dead-end, it backtracks to the last fork in the path. Once it reaches the end, the correct
path is stored and the robot is animated.

### Parameters
- *drawPath* (line 7) is a binary value that turns off / on drawing the path in the maze.
- *gridSize* (line 8) defines the size of each box in the maze, affecting the overall size of
the maze.
- *pathSize* (line 9) defines the size of the smaller grid used for maze generation.
Accordingly, the size of the final maze is:
(2 * gridSize - 1) × (2 * gridSize - 1)
Note: The value of *pathSize* can not be more than 137, as at this value the program
gives a segmentation fault, probably due to reaching maximum recursion depth.
- *robX, robY, robDir* (lines 326-328) all define the starting position of the robot. robDir
can only have four values: N, E, S, W.

### Screenshots
<img width="1235" alt="Screenshot of output maze" src="https://user-images.githubusercontent.com/75612147/215067777-b453b003-6f23-4626-976c-cb7298d283c7.png">
