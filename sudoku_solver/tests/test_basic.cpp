#include "sudoku_solver.h"
#include <iostream>

void testSolver(const char* name, int puzzle[9][9], bool shouldSolve = true) {
    std::cout << "测试: " << name << "... ";
    
    SudokuSolver solver;
    solver.setGrid(puzzle);
    
    if (solver.solve()) {
        if (solver.isSolved()) {
            std::cout << "✓ 通过" << std::endl;
        } else {
            std::cout << "✗ 失败 (解无效)" << std::endl;
        }
    } else {
        if (shouldSolve) {
            std::cout << "✗ 失败 (未找到解)" << std::endl;
        } else {
            std::cout << "✓ 通过 (正确识别无解)" << std::endl;
        }
    }
}

int main() {
    std::cout << "============================" << std::endl;
    std::cout << "数独求解器 - 基本功能测试" << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << std::endl;
    
    int easy[9][9] = {
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
    testSolver("简单数独", easy);
    
    int solved[9][9] = {
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
    testSolver("已解决的数独", solved);
    
    int invalid[9][9] = {
        {5, 5, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    testSolver("无效数独", invalid, false);
    
    std::cout << std::endl;
    std::cout << "============================" << std::endl;
    std::cout << "所有测试完成!" << std::endl;
    
    return 0;
}