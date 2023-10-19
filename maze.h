#include <iostream>
#include <vector>
#include <set>

#include "square.h"

#ifndef MAZE_H
#define MAZE_H

class Maze {
public:
    
    Maze(const std::string filename);
    void Print() const;
    void Set(int, int, int);
    int get(int, int);
    int getRows() const { return rows_; }
    int getCols() const { return cols_; }
    void ModifyEnter(const int enter_row, const int enter_col);
    void ModifyExit(const int exit_row, const int exit_col);
    void AStarSearch();
    void HeuristicCost(Square* current_square);
    void AccumulatedCost(Square* current_square);
    void TotalCost(Square* current_square);
    void CheckNeighbours(Square* current_square);
    void PrintOpenList() const;
    void PrintOtherList() const;
    void PrintClosedList() const;
    void PrintPath(Square* exit) const;

private:
    const int kCostDiagonal{7};
    const int kCostStraight{3};
    int rows_;
    int cols_;
    std::vector<std::vector<Square>> map_;
    Square* enter_;
    Square* exit_;
    std::set<Square*> open_list;
    std::set<Square*> closed_list;
    std::set<Square> other_list;
};

#endif