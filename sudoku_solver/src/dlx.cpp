#include "dlx.h"
#include <iostream>
#include <climits>

DancingLinks::DancingLinks(int max_rows, int max_cols) {
    header = new Node();
    solution_size = 0;
    found = false;
    
    Node* prev = header;
    for (int i = 0; i < max_cols; i++) {
        Node* col = new Node();
        col->name = i;
        prev->right = col;
        col->left = prev;
        prev = col;
    }
    prev->right = header;
    header->left = prev;
}

DancingLinks::~DancingLinks() {
    Node* col = header->right;
    while (col != header) {
        Node* next_col = col->right;
        Node* row = col->down;
        while (row != col) {
            Node* next_row = row->down;
            delete row;
            row = next_row;
        }
        delete col;
        col = next_col;
    }
    delete header;
}

void DancingLinks::cover(Node* col) {
    col->right->left = col->left;
    col->left->right = col->right;
    
    Node* row = col->down;
    while (row != col) {
        Node* right_node = row->right;
        while (right_node != row) {
            right_node->down->up = right_node->up;
            right_node->up->down = right_node->down;
            right_node->column->size--;
            right_node = right_node->right;
        }
        row = row->down;
    }
}

void DancingLinks::uncover(Node* col) {
    Node* row = col->up;
    while (row != col) {
        Node* left_node = row->left;
        while (left_node != row) {
            left_node->column->size++;
            left_node->down->up = left_node;
            left_node->up->down = left_node;
            left_node = left_node->left;
        }
        row = row->up;
    }
    
    col->right->left = col;
    col->left->right = col;
}

Node* DancingLinks::chooseColumn() {
    Node* col = header->right;
    Node* min_col = col;
    int min_size = col->size;
    
    while (col != header) {
        if (col->size < min_size) {
            min_size = col->size;
            min_col = col;
            if (min_size == 0) break;
        }
        col = col->right;
    }
    
    return min_col;
}

void DancingLinks::addRow(int row, int* cols, int count) {
    Node* first = nullptr;
    Node* prev = nullptr;
    
    for (int i = 0; i < count; i++) {
        int col_idx = cols[i];
        Node* col = header->right;
        for (int j = 0; j < col_idx; j++) {
            col = col->right;
        }
        
        Node* node = new Node();
        node->row = row;
        node->column = col;
        node->down = col;
        node->up = col->up;
        col->up->down = node;
        col->up = node;
        col->size++;
        
        if (first == nullptr) {
            first = node;
            prev = node;
        } else {
            prev->right = node;
            node->left = prev;
            prev = node;
        }
    }
    
    if (first != nullptr) {
        prev->right = first;
        first->left = prev;
    }
}

bool DancingLinks::search() {
    if (header->right == header) {
        found = true;
        return true;
    }
    
    Node* col = chooseColumn();
    if (col->size == 0) {
        return false;
    }
    
    cover(col);
    
    Node* row = col->down;
    while (row != col && !found) {
        solution[solution_size++] = row;
        
        Node* right_node = row->right;
        while (right_node != row) {
            cover(right_node->column);
            right_node = right_node->right;
        }
        
        if (search()) {
            return true;
        }
        
        solution_size--;
        
        Node* left_node = row->left;
        while (left_node != row) {
            uncover(left_node->column);
            left_node = left_node->left;
        }
        
        row = row->down;
    }
    
    uncover(col);
    return false;
}

void DancingLinks::getSolution(int* sol, int& size) {
    size = solution_size;
    for (int i = 0; i < solution_size; i++) {
        sol[i] = solution[i]->row;
    }
}

void DancingLinks::printSolution() {
    std::cout << "Solution found with " << solution_size << " rows:" << std::endl;
    for (int i = 0; i < solution_size; i++) {
        std::cout << solution[i]->row << " ";
    }
    std::cout << std::endl;
}