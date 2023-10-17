#include "square.h"

bool operator<(const Square& square, const Square& other_square) {
  return square.getFnCost() < other_square.getFnCost();
}

bool operator==(const Square& square, const Square& other_square) {
  return (square.getRow() == other_square.getRow()) && (square.getColumn() == other_square.getColumn());
}

bool operator!=(const Square& square, const Square& other_square) {
  return !(square == other_square);
}