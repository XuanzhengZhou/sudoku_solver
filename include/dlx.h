#ifndef DLX_H
#define DLX_H

struct Node {
    Node* left;
    Node* right;
    Node* up;
    Node* down;
    Node* column;
    int row;
    int size;
    int name;
    
    Node() : left(this), right(this), up(this), down(this), column(nullptr), row(0), size(0), name(0) {}
};

class DancingLinks {
private:
    Node* header;
    Node* solution[1000];
    int solution_size;
    bool found;
    
    void cover(Node* col);
    void uncover(Node* col);
    Node* chooseColumn();
    
public:
    DancingLinks(int max_rows, int max_cols);
    ~DancingLinks();
    
    void addRow(int row, int* cols, int count);
    bool search();
    void getSolution(int* sol, int& size);
    void printSolution();
};

#endif