#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

class SudokuSolver {
private:
    static const int SIZE = 9;
    
    int grid[SIZE][SIZE];
    bool isValid(int row, int col, int num);
    
public:
    SudokuSolver();
    void setGrid(int g[SIZE][SIZE]);
    bool solve();
    void printGrid();
    bool isSolved();
    void getSolution(int solution[SIZE][SIZE]);
};

#endif