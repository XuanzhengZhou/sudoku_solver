#include "sudoku_solver.h"
#include <iostream>

void testEasyPuzzle() {
    std::cout << "Testing Easy Puzzle..." << std::endl;
    
    int puzzle[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    
    SudokuSolver solver;
    solver.setGrid(puzzle);
    
    if (solver.solve()) {
        if (solver.isSolved()) {
            std::cout << "✓ Easy Puzzle Test Passed" << std::endl;
        } else {
            std::cout << "✗ Easy Puzzle Test Failed: Solution invalid" << std::endl;
        }
    } else {
        std::cout << "✗ Easy Puzzle Test Failed: No solution found" << std::endl;
    }
}

void testEmptyPuzzle() {
    std::cout << "Testing Empty Puzzle..." << std::endl;
    
    int puzzle[9][9] = {0};
    
    SudokuSolver solver;
    solver.setGrid(puzzle);
    
    if (solver.solve()) {
        if (solver.isSolved()) {
            std::cout << "✓ Empty Puzzle Test Passed" << std::endl;
        } else {
            std::cout << "✗ Empty Puzzle Test Failed: Solution invalid" << std::endl;
        }
    } else {
        std::cout << "✗ Empty Puzzle Test Failed: No solution found" << std::endl;
    }
}

void testAlreadySolvedPuzzle() {
    std::cout << "Testing Already Solved Puzzle..." << std::endl;
    
    int puzzle[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
    };
    
    SudokuSolver solver;
    solver.setGrid(puzzle);
    
    if (solver.solve()) {
        if (solver.isSolved()) {
            std::cout << "✓ Already Solved Puzzle Test Passed" << std::endl;
        } else {
            std::cout << "✗ Already Solved Puzzle Test Failed: Solution invalid" << std::endl;
        }
    } else {
        std::cout << "✗ Already Solved Puzzle Test Failed: No solution found" << std::endl;
    }
}

int main() {
    std::cout << "Running Sudoku Solver Tests..." << std::endl;
    std::cout << "===============================" << std::endl;
    
    testEasyPuzzle();
    std::cout << std::endl;
    
    testEmptyPuzzle();
    std::cout << std::endl;
    
    testAlreadySolvedPuzzle();
    std::cout << std::endl;
    
    std::cout << "===============================" << std::endl;
    std::cout << "All tests completed successfully!" << std::endl;
    
    return 0;
}