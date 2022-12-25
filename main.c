#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>
#include "graphics.h"

const int drawPath = 0;
const int gridSize = 20;
const int pathSize = 10; // Max value = 137

const int mazeSize = 2 * pathSize - 1;
int randCount = 1;

struct Robot {
    int robotX;
    int robotY;
    char* robotDir;
};

int giveRand(n) {
    srand(randCount * randCount * time(NULL));
    randCount++;
    return rand() % n;
}

void forward(struct Robot *r) {
    if (!strcmp((*r).robotDir, "E")) {
            (*r).robotX++;
    }
    else if (!strcmp((*r).robotDir, "W")) {
            (*r).robotX--;
    }
    else if (!strcmp((*r).robotDir, "N")) {
            (*r).robotY--;
    }
    else if (!strcmp((*r).robotDir, "S")) {
            (*r).robotY++;
    }
}

void left(struct Robot *r) {
    if (!strcmp((*r).robotDir, "N")) {(*r).robotDir = "W";} 
    else if (!strcmp((*r).robotDir, "W")) {(*r).robotDir = "S";}
    else if (!strcmp((*r).robotDir, "S")) {(*r).robotDir = "E";}
    else if (!strcmp((*r).robotDir, "E")) {(*r).robotDir = "N";}
}

void right(struct Robot *r) {
    if (!strcmp((*r).robotDir, "N")) {(*r).robotDir = "E";} 
    else if (!strcmp((*r).robotDir, "E")) {(*r).robotDir = "S";}
    else if (!strcmp((*r).robotDir, "S")) {(*r).robotDir = "W";}
    else if (!strcmp((*r).robotDir, "W")) {(*r).robotDir = "N";}
}

void drawRobot(struct Robot r) {
    if (!drawPath) {
        sleep(50);
        clear();
    }
    else {
        sleep(5);
    }
    setColour(green);
    if (!strcmp(r.robotDir, "E")) {
        int robotTriX[3] = {r.robotX * gridSize, r.robotX * gridSize, (r.robotX + 1) * gridSize};
        int robotTriY[3] = {r.robotY * gridSize, (r.robotY + 1) * gridSize, (r.robotY + 0.5) * gridSize};
        fillPolygon(3, robotTriX, robotTriY);
    }
    else if (!strcmp(r.robotDir, "W")) {
        int robotTriX[3] = {r.robotX * gridSize, (r.robotX + 1) * gridSize, (r.robotX + 1) * gridSize};
        int robotTriY[3] = {(r.robotY + 0.5) * gridSize, r.robotY * gridSize, (r.robotY + 1) * gridSize};
        fillPolygon(3, robotTriX, robotTriY);
    }
    else if (!strcmp(r.robotDir, "N")) {
        int robotTriX[3] = {r.robotX * gridSize, (r.robotX + 0.5) * gridSize, (r.robotX + 1) * gridSize};
        int robotTriY[3] = {(r.robotY + 1) * gridSize, r.robotY * gridSize, (r.robotY + 1) * gridSize};
        fillPolygon(3, robotTriX, robotTriY);
    }
    else if (!strcmp(r.robotDir, "S")) {
        int robotTriX[3] = {r.robotX * gridSize, (r.robotX + 0.5) * gridSize, (r.robotX + 1) * gridSize};
        int robotTriY[3] = {r.robotY * gridSize, (r.robotY + 1) * gridSize, r.robotY * gridSize};
        fillPolygon(3, robotTriX, robotTriY);
    }
}

void drawMaze(int maze[mazeSize][mazeSize]) {
    // Draw outer walls
    fillRect(0, 0, gridSize * (mazeSize + 2), gridSize);
    fillRect(0, 0, gridSize, gridSize * (mazeSize + 2));
    fillRect(0, gridSize * (mazeSize + 1), gridSize * (mazeSize + 2), gridSize);
    fillRect(gridSize * (mazeSize + 1), 0, gridSize, gridSize * (mazeSize + 2));
    
    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++) {
            setColour(black);
            if (maze[j][i] == 2) {
                setColour(gray);
                fillRect(gridSize * (i + 1), gridSize * (j + 1), gridSize, gridSize);
            }
            else if (maze[j][i]) {
                fillRect(gridSize * (i + 1),gridSize * (j + 1), gridSize, gridSize);
            }
            else {
                drawRect(gridSize * (i + 1), gridSize * (j + 1), gridSize, gridSize);
            }
        }
    }
}

int checkIn2DArray(int element1, int element2, int array[][2], int arrayTop) {
    for (int i = 0; i < arrayTop; i++) {
        if (array[i][0] == element1 && array[i][1] == element2) {
            return 1;
        }
    }
    return 0;
}

int checkSpot(int spotX, int spotY, int maze[mazeSize][mazeSize], int moves[mazeSize*mazeSize][2], int movesTop) {
    if (spotX > 0 && spotX <= mazeSize && spotY > 0 && spotY <= mazeSize) {
        if ((!maze[spotY - 1][spotX - 1] || maze[spotY - 1][spotX - 1] == 2) && !checkIn2DArray(spotX, spotY, moves, movesTop)) {
            return 1;
        }
    }
    return 0;
}

int numberOfForks(int pos[2], int maze[mazeSize][mazeSize], int moves[mazeSize*mazeSize][2], int movesTop) {
    int paths = 0;
    if (checkSpot(pos[0] + 1, pos[1], maze, moves, movesTop)) {
        paths++;
    }
    if (checkSpot(pos[0] - 1, pos[1], maze, moves, movesTop)) {
        paths++;
    }
    if (checkSpot(pos[0], pos[1] + 1, maze, moves, movesTop)) {
        paths++;
    }
    if (checkSpot(pos[0], pos[1] - 2, maze, moves, movesTop)) {
        paths++;
    }
    return paths;
}

void animateRobot(struct Robot r, int steps[mazeSize*mazeSize][2], int stepsTop) {
    for (int i = 0; i < stepsTop - 1; i++) {
        if (steps[i][0] < steps[i + 1][0]) {
            if (!strcmp(r.robotDir, "N")) {
                right(&r);
            }
            else if (!strcmp(r.robotDir, "S")) {
                left(&r);
            }
            forward(&r);
        }
        else if (steps[i][0] > steps[i + 1][0]) {
            if (!strcmp(r.robotDir, "N")) {
                left(&r);
            }
            else if (!strcmp(r.robotDir, "S")) {
                right(&r);
            }
            forward(&r);
        }
        else if (steps[i][1] < steps[i + 1][1]) {
            if (!strcmp(r.robotDir, "E")) {
                right(&r);
            }
            else if (!strcmp(r.robotDir, "W")) {
                left(&r);
            }
            forward(&r);
        }
        else if (steps[i][1] > steps[i + 1][1]) {
            if (!strcmp(r.robotDir, "E")) {
                left(&r);
            }
            else if (!strcmp(r.robotDir, "W")) {
                right(&r);
            }
            forward(&r);
        }
        drawRobot(r);
    }
}

void solveMaze(struct Robot r, int pos[2], int maze[mazeSize][mazeSize], int forks[mazeSize*mazeSize][2], int forksTop, int moves[mazeSize*mazeSize][2], int movesTop) {
    moves[movesTop][0] = pos[0];
    moves[movesTop][1] = pos[1];
    movesTop++;

    if (maze[pos[1] - 1][pos[0] - 1] == 2) {
        animateRobot(r, moves, movesTop);
        return;
    }

    if (numberOfForks(pos, maze, moves, movesTop) > 1) {
        forks[forksTop][0] = pos[0];
        forks[forksTop][1] = pos[1];
        forksTop++;
    }

    if (checkSpot(pos[0] + 1, pos[1], maze, moves, movesTop)) {
        pos[0]++;
    }
    else if (checkSpot(pos[0] - 1, pos[1], maze, moves, movesTop)) {
        pos[0]--;
    }
    else if (checkSpot(pos[0], pos[1] + 1, maze, moves, movesTop)) {
        pos[1]++;
    }
    else if (checkSpot(pos[0], pos[1] - 1, maze, moves, movesTop)) {
        pos[1]--;
    }
    else { // DEADEND
        if (!forksTop) { return; }     // No solution
        if (checkIn2DArray(pos[0], pos[1], forks, forksTop)) {
            forksTop--;
        }
        pos[0] = forks[forksTop - 1][0];
        pos[1] = forks[forksTop - 1][1];
        forksTop--;
        for (int i = 0; i < movesTop; i++) {
            if (moves[i][0] == pos[0] && moves[i][1] == pos[1]) {
                maze[moves[i+1][1] - 1][moves[i+1][0] - 1] = 1;
                movesTop = i;
            }
        }
    }

    solveMaze(r, pos, maze, forks, forksTop, moves, movesTop);
}

void generateMaze(int cellX, int cellY, int paths[pathSize][pathSize], int emptyMaze[mazeSize][mazeSize], int visited[pathSize * pathSize][2], int visitedTop) {
    if (!checkIn2DArray(cellX, cellY, visited, visitedTop)) {
        visited[visitedTop][0] = cellX;
        visited[visitedTop][1] = cellY;
        visitedTop++;
    }

    paths[cellY][cellX] = 1;

    int cellNeighbours[4][2] = {
        {cellX - 1, cellY},
        {cellX + 1, cellY},
        {cellX, cellY - 1},
        {cellX, cellY + 1}
    };

    int movableNeighbours[4][2] = {};
    int mNtop = 0;

    for (int i = 0; i < 4; i++) {
        int neighbourX = cellNeighbours[i][0];
        int neighbourY = cellNeighbours[i][1];
        if ((neighbourX >= 0) && (neighbourY >= 0) && (neighbourX < pathSize) && (neighbourY < pathSize)) {
            if (!paths[neighbourY][neighbourX]) {
                movableNeighbours[mNtop][0] = neighbourX;
                movableNeighbours[mNtop][1] = neighbourY;
                mNtop++;
            }
        }
    }

    if (mNtop) {
        int oldX = cellX;
        int oldY = cellY;
        srand(time(NULL) * time(NULL));
        int randCell = giveRand(mNtop);
        cellX = movableNeighbours[randCell][0];
        cellY = movableNeighbours[randCell][1];
        emptyMaze[2 * cellY][2 * cellX] = 0;
        if (cellX > oldX) {
            emptyMaze[2 * cellY][2 * cellX - 1] = 0;
        }
        if (cellX < oldX) {
            emptyMaze[2 * cellY][2 * cellX + 1] = 0;
        }
        if (cellY > oldY) {
            emptyMaze[2 * cellY - 1][2 * cellX] = 0;
        }
        if (cellY < oldY) {
            emptyMaze[2 * cellY + 1][2 * cellX] = 0;
        }
    }

    else {
        if (visitedTop) {
            visitedTop -= 2;
            if (visitedTop) {
                cellX = visited[visitedTop][0];
                cellY = visited[visitedTop][1];
            }

            else {
                emptyMaze[mazeSize - 1][mazeSize - 1] = 2;
                return;
            }
        }

        else {
            emptyMaze[mazeSize - 1][mazeSize - 1] = 2;
            return;
        }
    }
    generateMaze(cellX, cellY, paths, emptyMaze, visited, visitedTop);
};

int main(void) {
    setWindowSize(gridSize * (mazeSize + 2), gridSize * (mazeSize + 2));
    
    int paths[pathSize][pathSize];
    for (int i = 0; i < pathSize; i++) {
        for (int j = 0; j < pathSize; j++) {
            paths[j][i] = 0;
        }
    }

    int maze[mazeSize][mazeSize];
    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++) {
            maze[j][i] = 1;
        }
    }
    maze[0][0] = 0;

    int visited[pathSize*pathSize][2];
    generateMaze(0, 0, paths, maze, visited, 0);

    int robX = 1;
    int robY = 1;
    char *robDir = "E";
    struct Robot robot = {robX, robY, robDir};

    background();
    drawMaze(maze);
    foreground();

    int forks[mazeSize*mazeSize][2] = {};
    int moves[mazeSize*mazeSize][2] = {};
    int pos[2] = {robot.robotX, robot.robotY};
    solveMaze(robot, pos, maze, forks, 0, moves, 0);
}