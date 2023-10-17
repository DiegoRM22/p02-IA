#include <iostream>
#include <vector>

#include "square.h"



class Maze {
public:
    
    Maze(const std::string filename);
    void Print() const;
    void Set(int, int, int);
    int get(int, int);
    int getRows() const { return rows_; }
    int getCols() const { return cols_; }
private:
    int rows_;
    int cols_;
    std::vector<std::vector<Square>> map_;

};