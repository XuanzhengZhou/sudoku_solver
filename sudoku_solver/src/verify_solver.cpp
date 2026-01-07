#include "sudoku_solver.h"
#include <iostream>

int main() {
    std::cout << "验证数独求解器..." << std::endl;
    std::cout << std::endl;
    
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
    
    std::cout << "原始数独:" << std::endl;
    SudokuSolver solver;
    solver.setGrid(puzzle);
    solver.printGrid();
    
    std::cout << "求解中..." << std::endl;
    
    if (solver.solve()) {
        std::cout << "✓ 求解成功!" << std::endl;
        std::cout << std::endl;
        std::cout << "解:" << std::endl;
        solver.printGrid();
        
        if (solver.isSolved()) {
            std::cout << "✓ 验证通过: 解是有效的!" << std::endl;
        } else {
            std::cout << "✗ 验证失败: 解无效!" << std::endl;
            return 1;
        }
    } else {
        std::cout << "✗ 求解失败!" << std::endl;
        return 1;
    }
    
    std::cout << std::endl;
    std::cout << "==================" << std::endl;
    std::cout << "验证完成! 程序正常!" << std::endl;
    
    return 0;
}