# 数独求解器 (Sudoku Solver)

一个功能完整的C++数独求解器项目，支持回溯算法和DLX（Dancing Links）算法两种实现方式，提供交互式命令行界面和完整的测试套件。

[![C++ Version](https://img.shields.io/badge/C%2B%2B-11-blue.svg)](https://en.cppreference.com/w/cpp/11)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](docs/VERIFICATION_REPORT.md)

## 项目特点

- **双算法支持**：回溯算法 + DLX（Dancing Links）精确覆盖算法
- **交互式界面**：友好的命令行交互体验
- **多种输入格式**：支持分行输入和连续输入81个数字
- **智能验证**：输入验证、解的正确性验证
- **完整测试**：单元测试和集成测试
- **标准项目结构**：遵循专业C++项目组织规范
- **跨平台**：支持Linux、macOS和Windows

## 算法原理

### 1. 回溯算法 (Backtracking)

回溯算法是一种深度优先搜索的递归算法，通过尝试填充数独的每个空格来寻找解。

#### 算法步骤：

1. **寻找空格**：从左到右、从上到下找到第一个空格（值为0）
2. **尝试数字**：尝试填入1-9的数字
3. **验证合法性**：检查该数字在行、列、3x3宫格中是否已存在
4. **递归求解**：如果合法，递归尝试填充下一个空格
5. **回溯**：如果无法继续，撤销当前选择，尝试下一个数字

#### 时间复杂度：
- 最坏情况：O(9^(n×n))，其中n=9
- 实际运行：由于剪枝优化，通常在毫秒到秒级完成

#### 空间复杂度：
- O(n×n)，用于存储数独网格

#### 优点：
- 实现简单直观
- 易于理解和调试
- 对于大多数数独题目效率足够

#### 缺点：
- 对于极难题目可能较慢
- 无法保证是最优解（但数独解唯一）

### 2. DLX算法 (Dancing Links)

DLX（Dancing Links X）算法是Donald Knuth提出的解决精确覆盖问题的高效算法。数独可以转化为精确覆盖问题。

#### 转换思路：

数独的约束条件可以转化为精确覆盖的列：
1. 每个格子必须有数字（81列）
2. 每行的每个数字只能出现一次（81列）
3. 每列的每个数字只能出现一次（81列）
4. 每个3x3宫格的每个数字只能出现一次（81列）

总共324个约束条件，每个可能的数字放置对应一行。

#### 算法步骤：

1. **构建矩阵**：创建稀疏矩阵表示约束关系
2. ** dancing links **：使用双向循环链表高效删除和恢复行列
3. ** 递归搜索 **：选择列、覆盖列、尝试行、递归、回溯
4. ** 解提取 **：从选中的行提取数独解

#### 时间复杂度：
- 理论上仍然是指数级
- 实际运行极快，通常比回溯算法更快

#### 空间复杂度：
- O(N×M)，N为行数，M为列数

#### 优点：
- 算法优雅高效
- 特别适合精确覆盖问题
- 实际运行速度快

#### 缺点：
- 实现复杂
- 内存占用较大
- 不易理解和调试

## 项目结构

```
sudoku/
├── build/                      # 编译生成的可执行文件和对象文件
├── docs/                       # 文档
│   └── VERIFICATION_REPORT.md  # 验证报告
├── examples/                   # 示例输入文件（可创建）
├── include/                    # 头文件
│   ├── dlx.h                   # DLX算法头文件
│   └── sudoku_solver.h         # 回溯算法头文件
├── scripts/                    # 脚本文件
│   ├── demo.sh                 # 演示脚本
│   └── test_interactive.sh     # 交互式测试脚本
├── src/                        # 源代码
│   ├── dlx.cpp                 # DLX算法实现
│   ├── debug_sudoku.cpp        # 调试程序
│   ├── main.cpp                # 主程序（交互式界面）
│   ├── sudoku_solver.cpp       # 回溯算法实现
│   └── verify_solver.cpp       # 验证程序
├── tests/                      # 测试代码
│   ├── test_basic.cpp          # 基础测试
│   ├── test_runner.cpp         # 测试运行器
│   └── test_sudoku.cpp         # 数独求解器测试
├── Makefile                    # 编译配置
└── README.md                   # 本文档
```

## 编译和安装

### 系统要求

- C++11兼容的编译器（g++、clang++等）
- make工具
- Linux、macOS或Windows（使用MinGW或WSL）

### 编译步骤

```bash
# 克隆项目（或解压到本地）
# git clone <repository-url> sudoku
# cd sudoku

# 编译所有目标
make

# 或编译特定目标
make all          # 编译所有程序
make test         # 编译并运行测试
make run          # 编译并运行主程序
```

### 安装到系统（可选）

```bash
# 需要管理员权限
sudo make install

# 安装后可全局使用
sudoku_solver

# 卸载
sudo make uninstall
```

### 清理

```bash
# 清理编译文件
make clean

# 深度清理（删除build目录）
make distclean
```

## 使用方法

### 方式1：交互式程序

运行主程序进入交互模式：

```bash
./build/sudoku_solver
```

或

```bash
make run
```

#### 交互式命令：

- `h` - 显示帮助信息
- `t` - 运行内置测试
- `q` - 退出程序

#### 输入格式：

**格式1：分行输入**
```
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9
```

**格式2：连续输入81个数字**
```
530070000600195000098000060800060003400803001700020006060000280000419005000080079
```

### 方式2：运行测试

```bash
./build/test_sudoku
```

或

```bash
make test
```

### 方式3：使用脚本

```bash
# 运行演示脚本
./scripts/demo.sh

# 运行交互式测试
./scripts/test_interactive.sh
```

## 使用示例

### 示例1：简单数独

输入：
```
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9
```

输出：
```
 5 3 4 | 6 7 8 | 9 1 2
 6 7 2 | 1 9 5 | 3 4 8
 1 9 8 | 3 4 2 | 5 6 7
 ------+-------+------
 8 5 9 | 7 6 1 | 4 2 3
 4 2 6 | 8 5 3 | 7 9 1
 7 1 3 | 9 2 4 | 8 5 6
 ------+-------+------
 9 6 1 | 5 3 7 | 2 8 4
 2 8 7 | 4 1 9 | 6 3 5
 3 4 5 | 2 8 6 | 1 7 9
```

### 示例2：空数独（生成完整解）

输入：
```
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
```

程序将生成一个有效的完整数独解。

### 示例3：连续输入格式

```
请输入数独题目 (或输入'h'查看帮助, 'q'退出, 't'运行测试):
530070000600195000098000060800060003400803001700020006060000280000419005000080079
```

程序将自动识别为连续格式并求解。

### 示例4：运行测试

```bash
$ make test
运行数独求解器测试...
Testing Easy Puzzle...
✓ Easy Puzzle Test Passed

Testing Empty Puzzle...
✓ Empty Puzzle Test Passed

Testing Already Solved Puzzle...
✓ Already Solved Puzzle Test Passed

===============================
All tests completed successfully!
```

## 性能表现

### 回溯算法

- **简单数独**：< 10ms
- **中等数独**：10-100ms
- **困难数独**：100ms-几秒（取决于难度）

### DLX算法

- **简单数独**：< 5ms
- **中等数独**：5-50ms
- **困难数独**：50ms-1秒

### 内存使用

- **回溯算法**：约 1-2 MB
- **DLX算法**：约 5-10 MB（取决于矩阵大小）

## 验证报告

详细的验证报告请查看：[docs/VERIFICATION_REPORT.md](docs/VERIFICATION_REPORT.md)

验证内容包括：
- ✓ 程序编译验证
- ✓ 核心算法验证
- ✓ 输入格式验证
- ✓ 错误处理验证
- ✓ 交互式功能验证
- ✓ 性能测试

## 开发说明

### 代码结构

```
核心类：
- SudokuSolver: 回溯算法实现
  - setGrid(): 设置数独题目
  - solve(): 求解数独
  - printGrid(): 打印结果
  - isSolved(): 验证解的正确性

- DancingLinks: DLX算法实现
  - addRow(): 添加约束行
  - search(): 搜索解
  - cover()/uncover(): 覆盖/恢复列
```

### 添加新功能

1. **添加新的求解算法**：
   - 在`src/`目录创建新的算法实现
   - 在`include/`目录添加头文件
   - 更新Makefile添加编译规则

2. **添加新的输入格式**：
   - 修改`src/main.cpp`中的`parseSudoku()`函数
   - 添加格式验证逻辑

3. **添加性能测试**：
   - 在`tests/`目录创建新的测试文件
   - 使用`clock()`或`chrono`测量运行时间

### 调试技巧

```bash
# 使用gdb调试
gdb ./build/sudoku_solver

# 使用valgrind检查内存泄漏
valgrind --leak-check=full ./build/sudoku_solver

# 编译调试版本
make CXXFLAGS="-std=c++11 -Wall -g -O0"
```

## 常见问题

### Q1: 输入格式错误怎么办？

A: 请检查：
- 是否输入了81个数字（9行×9列）
- 数字是否在0-9之间（0表示空格）
- 是否包含非法字符

### Q2: 程序求解很慢？

A: 可能原因：
- 数独题目极难（回溯算法特性）
- 可以尝试使用DLX算法（如果已实现）
- 检查是否陷入无限循环（调试模式）

### Q3: 如何验证解的正确性？

A: 程序内置验证功能：
- `solver.isSolved()` 验证解的合法性
- 手动检查：每行、每列、每个3x3宫格都包含1-9

### Q4: 如何生成数独题目？

A: 本项目专注于求解，生成数独题目的方法：
1. 先求解一个空数独得到完整解
2. 随机移除一些数字
3. 确保题目有唯一解（需要额外验证）

## 贡献指南

欢迎贡献代码、报告问题或提出改进建议！

### 如何贡献

1. Fork本项目
2. 创建功能分支：`git checkout -b feature/new-algorithm`
3. 提交更改：`git commit -am 'Add new algorithm'`
4. 推送到分支：`git push origin feature/new-algorithm`
5. 创建Pull Request

### 代码规范

- 使用C++11标准
- 遵循Google C++ Style Guide
- 添加必要的注释
- 为新功能编写测试

## 许可证

本项目采用MIT许可证 - 查看[LICENSE](LICENSE)文件了解详情。

## 致谢

- Donald Knuth - 提出DLX算法
- 回溯算法 - 经典的递归算法
- 所有贡献者和测试者

## 联系方式

如有问题或建议，请：
- 提交Issue到项目仓库
- 发送邮件到项目维护者

## 更新日志

### v1.0.0 (2026-01-06)
- ✓ 初始版本发布
- ✓ 回溯算法实现
- ✓ DLX算法实现
- ✓ 交互式界面
- ✓ 完整测试套件
- ✓ 标准项目结构

## 相关链接

- [数独规则](https://en.wikipedia.org/wiki/Sudoku)
- [DLX算法详解](https://arxiv.org/abs/cs/0011047)
- [回溯算法](https://en.wikipedia.org/wiki/Backtracking)

---

** 享受数独求解的乐趣！**
