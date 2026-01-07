#include "sudoku_solver.h"
#include <iostream>

int main() {
    std::cout << "Debug: Testing simple puzzle" << std::endl;
    
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
    
    std::cout << "Puzzle set successfully" << std::endl;
    
    bool solved = solver.solve();
    
    std::cout << "Solve returned: " << solved << std::endl;
    
    if (solved) {
        solver.printGrid();
    }
    
    return 0;
}