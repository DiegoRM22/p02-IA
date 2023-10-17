#include <iostream>

#ifndef SQUARE_H
#define SQUARE_H

class Square {
 public:

  Square() : identifier_(' ') {}
  Square(char identifier) : identifier_(identifier) {}
  Square(int row, int column, char identifier) : row_(row), column_(column), identifier_(identifier) {}
  char getIdentifier() const { return identifier_; }
  void setIdentifier(char identifier) { identifier_ = identifier; }
  int getFnCost() const { return fnCost_; }
  int getGnCost() const { return gnCost_; }
  int getHnCost() const { return hnCost_; }
  int getRow() const { return row_; }
  int getColumn() const { return column_; }
  Square* getFather() const { return father_; }

  void setFnCost(int fnCost) { fnCost_ = fnCost; }
  void setGnCost(int gnCost) { gnCost_ = gnCost; }
  void setHnCost(int hnCost) { hnCost_ = hnCost; }
  void setFather(Square* father) { father_ = father; }

 private:
  int row_;
  int column_;
  char identifier_;
  int fnCost_;
  int gnCost_;
  int hnCost_;
  Square* father_;
};



bool operator<(const Square& square, const Square& other_square);

bool operator==(const Square& square, const Square& other_square);

bool operator!=(const Square& square, const Square& other_square);

#endif