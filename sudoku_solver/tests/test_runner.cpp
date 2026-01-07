#include "sudoku_solver.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>

struct TestPuzzle {
    std::string name;
    int puzzle[9][9];
    bool shouldSucceed;
    std::string description;
};

bool runTest(const TestPuzzle& test) {
    std::cout << "测试: " << test.name;
    if (!test.description.empty()) {
        std::cout << " (" << test.description << ")";
    }
    std::cout << std::endl;
    
    SudokuSolver solver;
    solver.setGrid(const_cast<int(*)[9]>(test.puzzle));
    
    auto start = std::chrono::high_resolution_clock::now();
    bool solved = solver.solve();
    auto end = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    if (solved) {
        bool valid = solver.isSolved();
        if (valid) {
            std::cout << "  ✓ 成功 (耗时: " << duration.count() << "ms)" << std::endl;
            return true;
        } else {
            std::cout << "  ✗ 失败: 解无效 (耗时: " << duration.count() << "ms)" << std::endl;
            return false;
        }
    } else {
        if (test.shouldSucceed) {
            std::cout << "  ✗ 失败: 未找到解 (耗时: " << duration.count() << "ms)" << std::endl;
            return false;
        } else {
            std::cout << "  ✓ 成功: 正确识别无解 (耗时: " << duration.count() << "ms)" << std::endl;
            return true;
        }
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "    数独求解器 - 大规模测试验证       " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;
    
    std::vector<TestPuzzle> tests;
    
    TestPuzzle easy1 = {
        "Easy Puzzle 1",
        {
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9}
        },
        true,
        "经典简单数独"
    };
    tests.push_back(easy1);
    
    TestPuzzle mostlyEmpty = {
        "Mostly Empty",
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0}
        },
        true,
        "大部分空白"
    };
    tests.push_back(mostlyEmpty);
    
    TestPuzzle hard1 = {
        "Hard Puzzle 1",
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 3, 0, 8, 5},
            {0, 0, 1, 0, 2, 0, 0, 0, 0},
            {0, 0, 0, 5, 0, 7, 0, 0, 0},
            {0, 0, 4, 0, 0, 0, 1, 0, 0},
            {0, 9, 0, 0, 0, 0, 0, 0, 0},
            {5, 0, 0, 0, 0, 0, 0, 7, 3},
            {0, 0, 2, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 4, 0, 0, 0, 9}
        },
        true,
        "高难度数独"
    };
    tests.push_back(hard1);
    
    TestPuzzle medium1 = {
        "Medium Puzzle 1",
        {
            {0, 0, 0, 2, 6, 0, 7, 0, 1},
            {6, 8, 0, 0, 7, 0, 0, 9, 0},
            {1, 9, 0, 0, 0, 4, 5, 0, 0},
            {8, 2, 0, 1, 0, 0, 0, 4, 0},
            {0, 0, 4, 6, 0, 2, 9, 0, 0},
            {0, 5, 0, 0, 0, 3, 0, 2, 8},
            {0, 0, 9, 3, 0, 0, 0, 7, 4},
            {0, 4, 0, 0, 5, 0, 0, 3, 6},
            {7, 0, 3, 0, 1, 8, 0, 0, 0}
        },
        true,
        "中等难度"
    };
    tests.push_back(medium1);
    
    TestPuzzle medium2 = {
        "Medium Puzzle 2",
        {
            {0, 0, 0, 6, 0, 0, 4, 0, 0},
            {7, 0, 0, 0, 0, 3, 6, 0, 0},
            {0, 0, 0, 0, 9, 1, 0, 8, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 5, 0, 1, 8, 0, 0, 0, 3},
            {0, 0, 0, 3, 0, 6, 0, 4, 5},
            {0, 4, 0, 2, 0, 0, 0, 6, 0},
            {9, 0, 3, 0, 0, 0, 0, 0, 0},
            {0, 2, 0, 0, 0, 0, 1, 0, 0}
        },
        true,
        "中等难度2"
    };
    tests.push_back(medium2);
    
    TestPuzzle solved = {
        "Already Solved",
        {
            {5, 3, 4, 6, 7, 8, 9, 1, 2},
            {6, 7, 2, 1, 9, 5, 3, 4, 8},
            {1, 9, 8, 3, 4, 2, 5, 6, 7},
            {8, 5, 9, 7, 6, 1, 4, 2, 3},
            {4, 2, 6, 8, 5, 3, 7, 9, 1},
            {7, 1, 3, 9, 2, 4, 8, 5, 6},
            {9, 6, 1, 5, 3, 7, 2, 8, 4},
            {2, 8, 7, 4, 1, 9, 6, 3, 5},
            {3, 4, 5, 2, 8, 6, 1, 7, 9}
        },
        true,
        "已解决的数独"
    };
    tests.push_back(solved);
    
    TestPuzzle invalid1 = {
        "Invalid Puzzle 1",
        {
            {5, 5, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0}
        },
        false,
        "无效数独（重复数字）"
    };
    tests.push_back(invalid1);
    
    TestPuzzle invalid2 = {
        "Invalid Puzzle 2",
        {
            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {1, 2, 3, 4, 5, 6, 7, 8, 9},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0}
        },
        false,
        "无效数独（行重复）"
    };
    tests.push_back(invalid2);
    
    TestPuzzle nearlySolved = {
        "Nearly Solved",
        {
            {5, 3, 4, 6, 7, 8, 9, 1, 2},
            {6, 7, 2, 1, 9, 5, 3, 4, 8},
            {1, 9, 8, 3, 4, 2, 5, 6, 7},
            {8, 5, 9, 7, 6, 1, 4, 2, 3},
            {4, 2, 6, 8, 5, 3, 7, 9, 1},
            {7, 1, 3, 9, 2, 4, 8, 5, 6},
            {9, 6, 1, 5, 3, 7, 2, 8, 4},
            {2, 8, 7, 4, 1, 9, 6, 3, 5},
            {3, 4, 5, 2, 8, 0, 1, 7, 9}
        },
        true,
        "接近完成的数独"
    };
    tests.push_back(nearlySolved);
    
    TestPuzzle fewClues = {
        "Few Clues",
        {
            {0, 0, 0, 0, 0, 0, 0, 0, 1},
            {0, 0, 2, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 3, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0}
        },
        true,
        "较少提示"
    };
    tests.push_back(fewClues);
    
    std::cout << "共 " << tests.size() << " 个测试用例" << std::endl;
    std::cout << std::endl;
    
    int passed = 0;
    int total = tests.size();
    
    auto totalStart = std::chrono::high_resolution_clock::now();
    
    for (size_t i = 0; i < tests.size(); i++) {
        std::cout << "[" << (i + 1) << "/" << total << "] ";
        if (runTest(tests[i])) {
            passed++;
        }
        std::cout << std::endl;
    }
    
    auto totalEnd = std::chrono::high_resolution_clock::now();
    auto totalDuration = std::chrono::duration_cast<std::chrono::milliseconds>(totalEnd - totalStart);
    
    std::cout << "========================================" << std::endl;
    std::cout << "测试结果总结:" << std::endl;
    std::cout << "通过: " << passed << "/" << total << std::endl;
    std::cout << "失败: " << (total - passed) << "/" << total << std::endl;
    std::cout << "总耗时: " << totalDuration.count() << "ms" << std::endl;
    std::cout << "========================================" << std::endl;
    
    if (passed == total) {
        std::cout << "✓ 所有测试通过! 程序工作正常!" << std::endl;
        return 0;
    } else {
        std::cout << "✗ 部分测试失败! 需要检查程序!" << std::endl;
        return 1;
    }
}