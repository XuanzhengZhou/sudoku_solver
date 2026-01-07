#include "sudoku_solver.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include <algorithm>

void printWelcome() {
    std::cout << "==========================================" << std::endl;
    std::cout << "      数独求解器 - Sudoku Solver         " << std::endl;
    std::cout << "==========================================" << std::endl;
    std::cout << std::endl;
}

void printHelp() {
    std::cout << "使用说明:" << std::endl;
    std::cout << "1. 输入数独题目，使用0-9的数字" << std::endl;
    std::cout << "2. 用0表示空格" << std::endl;
    std::cout << "3. 输入方式:" << std::endl;
    std::cout << "   - 一行一行输入，数字之间用空格分隔" << std::endl;
    std::cout << "   - 或者直接输入81个数字（9行x9列）" << std::endl;
    std::cout << "4. 输入'q'退出程序" << std::endl;
    std::cout << "5. 输入'h'显示帮助" << std::endl;
    std::cout << "6. 输入't'运行测试" << std::endl;
    std::cout << std::endl;
}

void printExample() {
    std::cout << "示例输入:" << std::endl;
    std::cout << "方式1 - 分行输入:" << std::endl;
    std::cout << "5 3 0 0 7 0 0 0 0" << std::endl;
    std::cout << "6 0 0 1 9 5 0 0 0" << std::endl;
    std::cout << "...（共9行）" << std::endl;
    std::cout << std::endl;
    std::cout << "方式2 - 连续输入81个数字:" << std::endl;
    std::cout << "530070000600195000098000060800060003400803001700020006060000280000419005000080079" << std::endl;
    std::cout << std::endl;
}

bool validateInput(const std::string& input) {
    if (input.length() == 0) return false;
    
    for (char c : input) {
        if (!std::isdigit(c) && c != ' ' && c != '\t') {
            return false;
        }
    }
    return true;
}

bool parseSudoku(const std::string& input, int puzzle[9][9]) {
    std::stringstream ss(input);
    std::string token;
    std::vector<int> numbers;
    
    while (ss >> token) {
        if (token.length() == 81 && std::all_of(token.begin(), token.end(), ::isdigit)) {
            for (char c : token) {
                numbers.push_back(c - '0');
            }
        } else {
            for (char c : token) {
                if (std::isdigit(c)) {
                    numbers.push_back(c - '0');
                }
            }
        }
    }
    
    if (numbers.size() != 81) {
        return false;
    }
    
    for (int i = 0; i < 81; i++) {
        int row = i / 9;
        int col = i % 9;
        puzzle[row][col] = numbers[i];
    }
    
    return true;
}

void printSudoku(const int puzzle[9][9]) {
    std::cout << std::endl;
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "------+-------+------" << std::endl;
        }
        
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                std::cout << " | ";
            }
            
            if (j == 0) {
                std::cout << " ";
            }
            
            if (puzzle[i][j] == 0) {
                std::cout << ".";
            } else {
                std::cout << puzzle[i][j];
            }
            
            if (j < 8) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool isValidSudoku(const int puzzle[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (puzzle[i][j] < 0 || puzzle[i][j] > 9) {
                return false;
            }
        }
    }
    return true;
}

void runTests() {
    std::cout << "\n运行内置测试..." << std::endl;
    std::cout << "=================" << std::endl;
    
    int easyPuzzle[9][9] = {
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
    
    int emptyPuzzle[9][9] = {0};
    
    int hardPuzzle[9][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3, 0, 8, 5},
        {0, 0, 1, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 5, 0, 7, 0, 0, 0},
        {0, 0, 4, 0, 0, 0, 1, 0, 0},
        {0, 9, 0, 0, 0, 0, 0, 0, 0},
        {5, 0, 0, 0, 0, 0, 0, 7, 3},
        {0, 0, 2, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 4, 0, 0, 0, 9}
    };
    
    int invalidPuzzle[9][9] = {
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
    
    struct TestCase {
        const char* name;
        int (*puzzle)[9];
        bool shouldSucceed;
    };
    
    TestCase tests[] = {
        {"Easy Puzzle", easyPuzzle, true},
        {"Empty Puzzle", emptyPuzzle, true},
        {"Hard Puzzle", hardPuzzle, true},
        {"Invalid Puzzle", invalidPuzzle, false}
    };
    
    int passed = 0;
    int total = sizeof(tests) / sizeof(tests[0]);
    
    for (int i = 0; i < total; i++) {
        std::cout << "\n测试 " << tests[i].name << ":" << std::endl;
        
        SudokuSolver solver;
        solver.setGrid(tests[i].puzzle);
        
        if (solver.solve()) {
            if (solver.isSolved()) {
                std::cout << "  ✓ 求解成功" << std::endl;
                passed++;
            } else {
                std::cout << "  ✗ 求解结果无效" << std::endl;
            }
        } else {
            if (tests[i].shouldSucceed) {
                std::cout << "  ✗ 未找到解" << std::endl;
            } else {
                std::cout << "  ✓ 正确识别为无解" << std::endl;
                passed++;
            }
        }
    }
    
    std::cout << "\n=================" << std::endl;
    std::cout << "测试结果: " << passed << "/" << total << " 通过" << std::endl;
    
    if (passed == total) {
        std::cout << "✓ 所有测试通过!" << std::endl;
    } else {
        std::cout << "✗ 部分测试失败!" << std::endl;
    }
}

int main() {
    printWelcome();
    printHelp();
    printExample();
    
    SudokuSolver solver;
    std::string input;
    int puzzle[9][9];
    
    while (true) {
        std::cout << "请输入数独题目 (或输入'h'查看帮助, 'q'退出, 't'运行测试): " << std::endl;
        
        std::getline(std::cin, input);
        
        if (input == "q" || input == "Q") {
            std::cout << "感谢使用数独求解器! 再见!" << std::endl;
            break;
        }
        
        if (input == "h" || input == "H") {
            printHelp();
            printExample();
            continue;
        }
        
        if (input == "t" || input == "T") {
            runTests();
            continue;
        }
        
        if (!validateInput(input)) {
            std::cout << "错误: 输入包含无效字符!" << std::endl;
            std::cout << "请输入数字0-9和空格!" << std::endl;
            continue;
        }
        
        if (!parseSudoku(input, puzzle)) {
            std::cout << "错误: 输入格式不正确!" << std::endl;
            std::cout << "请输入81个数字(9x9)!" << std::endl;
            continue;
        }
        
        if (!isValidSudoku(puzzle)) {
            std::cout << "错误: 输入包含无效数字!" << std::endl;
            std::cout << "数字必须在0-9之间!" << std::endl;
            continue;
        }
        
        std::cout << "\n输入的数独题目:" << std::endl;
        printSudoku(puzzle);
        
        solver.setGrid(puzzle);
        
        std::cout << "正在求解..." << std::endl;
        
        if (solver.solve()) {
            std::cout << "✓ 求解成功!" << std::endl;
            std::cout << "\n解:" << std::endl;
            solver.printGrid();
            
            if (solver.isSolved()) {
                std::cout << "✓ 验证: 解是有效的!" << std::endl;
            } else {
                std::cout << "✗ 验证: 解无效!" << std::endl;
            }
        } else {
            std::cout << "✗ 无解!" << std::endl;
        }
        
        std::cout << std::endl;
    }
    
    return 0;
}