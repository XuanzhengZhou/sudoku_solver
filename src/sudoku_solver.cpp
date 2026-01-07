#include "sudoku_solver.h"
#include <iostream>

SudokuSolver::SudokuSolver() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = 0;
        }
    }
}

void SudokuSolver::setGrid(int g[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = g[i][j];
        }
    }
}

bool SudokuSolver::isValid(int row, int col, int num) {
    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == num) return false;
        if (grid[i][col] == num) return false;
    }
    
    int boxRow = (row / 3) * 3;
    int boxCol = (col / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[boxRow + i][boxCol + j] == num) return false;
        }
    }
    
    return true;
}

bool SudokuSolver::solve() {
    int emptyRow = -1;
    int emptyCol = -1;
    bool isEmpty = false;
    
    for (int i = 0; i < SIZE && !isEmpty; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
                isEmpty = true;
                break;
            }
        }
    }
    
    if (!isEmpty) {
        return true;
    }
    
    for (int num = 1; num <= 9; num++) {
        if (isValid(emptyRow, emptyCol, num)) {
            grid[emptyRow][emptyCol] = num;
            
            if (solve()) {
                return true;
            }
            
            grid[emptyRow][emptyCol] = 0;
        }
    }
    
    return false;
}

bool SudokuSolver::isSolved() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == 0) return false;
        }
    }
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int num = grid[i][j];
            
            for (int k = 0; k < SIZE; k++) {
                if (k != j && grid[i][k] == num) return false;
                if (k != i && grid[k][j] == num) return false;
            }
            
            int boxRow = (i / 3) * 3;
            int boxCol = (j / 3) * 3;
            for (int r = 0; r < 3; r++) {
                for (int c = 0; c < 3; c++) {
                    int curRow = boxRow + r;
                    int curCol = boxCol + c;
                    if ((curRow != i || curCol != j) && grid[curRow][curCol] == num) {
                        return false;
                    }
                }
            }
        }
    }
    
    return true;
}

void SudokuSolver::printGrid() {
    for (int i = 0; i < SIZE; i++) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "------+-------+------" << std::endl;
        }
        
        for (int j = 0; j < SIZE; j++) {
            if (j % 3 == 0 && j != 0) {
                std::cout << " | ";
            }
            
            if (j == 0) {
                std::cout << " ";
            }
            
            if (grid[i][j] == 0) {
                std::cout << ".";
            } else {
                std::cout << grid[i][j];
            }
            
            if (j < SIZE - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

void SudokuSolver::getSolution(int solution[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            solution[i][j] = grid[i][j];
        }
    }
}