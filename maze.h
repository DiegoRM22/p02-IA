/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Informática Básica
  *
  * @author Diego Rodríguez alu0101464992@ull.edu.es
  * @brief Este programa implementa la clase Maze.
  * @bug No hay bugs conocidos
  */

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
    void AStarSearch(const std::string& filename, const int heuristicType);
    void HeuristicCost(Square* current_square);
    void EucledianDistance(Square* current_square);
    void AccumulatedCost(Square* current_square);
    void TotalCost(Square* current_square);
    void CheckNeighbours(Square* current_square, const int heuristicType);
    void PrintOpenList() const;
    void PrintOtherList() const;
    void PrintOtherClosedList() const;
    void PrintClosedList() const;
    void PrintPath(Square* exit, const std::string& filename) const;
    void PrintVectorOpenList() const;
    void PrintVectorClosedList() const;
    void PrintGeneratedNodes(const std::string& filename) const;
    void PrintAnalysedNodes(const std::string& filename) const;
    void SortVector();
    void DeleteDuplicates();

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
    std::set<Square> other_open_list;
    std::set<Square> other_closed_list;
    std::vector<Square*> vector_open_list;
    std::vector<Square*> vector_closed_list;
    std::vector<Square*> generated_nodes;
    std::vector<Square*> analysed_nodes;
};

bool IsInList(std::set<Square> list, Square node);

Square SearchNode(std::set<Square> list, Square node);

void ModifyFnCost(std::set<Square> list, Square node, int new_cost);


Square* FindInVector(std::vector<Square*> vector, Square* node);

bool IsInVector(std::vector<Square*> vector, Square* node);

void FilePutContents(const std::string& name, const std::string& content, bool append = false);




#endif