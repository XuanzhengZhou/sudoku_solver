# 数独求解器项目 Makefile
# 支持回溯算法和DLX算法两种实现

# 编译器设置
CXX = g++
CXXFLAGS = -std=c++11 -Wall -O2 -I./include
LDFLAGS = 

# 目录结构
SRC_DIR = src
INC_DIR = include
TEST_DIR = tests
BUILD_DIR = build

# 可执行文件
TARGETS = $(BUILD_DIR)/sudoku_solver $(BUILD_DIR)/test_sudoku

# 源文件
MAIN_SRC = $(SRC_DIR)/main.cpp
SOLVER_SRC = $(SRC_DIR)/sudoku_solver.cpp $(SRC_DIR)/dlx.cpp
TEST_SRC = $(TEST_DIR)/test_sudoku.cpp

# 对象文件
MAIN_OBJ = $(BUILD_DIR)/main.o
SOLVER_OBJ = $(BUILD_DIR)/sudoku_solver.o $(BUILD_DIR)/dlx.o
TEST_OBJ = $(BUILD_DIR)/test_sudoku.o

# 默认目标
all: $(BUILD_DIR) $(TARGETS)

# 创建build目录
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 主程序：交互式数独求解器
$(BUILD_DIR)/sudoku_solver: $(MAIN_OBJ) $(SOLVER_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# 测试程序
$(BUILD_DIR)/test_sudoku: $(TEST_OBJ) $(SOLVER_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# 编译对象文件
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INC_DIR)/sudoku_solver.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/sudoku_solver.o: $(SRC_DIR)/sudoku_solver.cpp $(INC_DIR)/sudoku_solver.h $(INC_DIR)/dlx.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/dlx.o: $(SRC_DIR)/dlx.cpp $(INC_DIR)/dlx.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/test_sudoku.o: $(TEST_DIR)/test_sudoku.cpp $(INC_DIR)/sudoku_solver.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 运行测试
test: $(BUILD_DIR)/test_sudoku
	@echo "运行数独求解器测试..."
	@$(BUILD_DIR)/test_sudoku

# 运行主程序
run: $(BUILD_DIR)/sudoku_solver
	@echo "启动数独求解器..."
	@$(BUILD_DIR)/sudoku_solver

# 清理编译文件
clean:
	@echo "清理编译文件..."
	@rm -rf $(BUILD_DIR)/*.o $(TARGETS)

# 深度清理（包括build目录）
distclean: clean
	@echo "深度清理..."
	@rm -rf $(BUILD_DIR)

# 安装（可选）
install: $(BUILD_DIR)/sudoku_solver
	@echo "安装数独求解器到/usr/local/bin..."
	@cp $(BUILD_DIR)/sudoku_solver /usr/local/bin/
	@echo "安装完成!"

# 卸载
uninstall:
	@echo "卸载数独求解器..."
	@rm -f /usr/local/bin/sudoku_solver
	@echo "卸载完成!"

# 帮助信息
help:
	@echo "数独求解器 Makefile 帮助:"
	@echo ""
	@echo "目标:"
	@echo "  all       - 编译所有目标 (默认)"
	@echo "  test      - 编译并运行测试"
	@echo "  run       - 编译并运行主程序"
	@echo "  clean     - 清理编译文件"
	@echo "  distclean - 深度清理（删除build目录）"
	@echo "  install   - 安装到系统 (需要权限)"
	@echo "  uninstall - 从系统卸载"
	@echo "  help      - 显示此帮助信息"
	@echo ""
	@echo "示例:"
	@echo "  make        # 编译所有程序"
	@echo "  make test   # 运行测试"
	@echo "  make run    # 运行交互式求解器"
	@echo "  make clean  # 清理"

.PHONY: all test run clean distclean install uninstall help
