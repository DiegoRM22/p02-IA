#include "square.h"

bool operator<(const Square& square, const Square& other_square) {
  return (square.getHnCost() < other_square.getHnCost());
}

bool operator>(const Square& square, const Square& other_square) {
  return (square.getHnCost() > other_square.getHnCost());
}

bool operator==(const Square& square, const Square& other_square) {
  return (square.getRow() == other_square.getRow()) && (square.getColumn() == other_square.getColumn());
}

bool operator!=(const Square& square, const Square& other_square) {
  return !(square == other_square);
}

std::ostream& operator<<(std::ostream& os, const Square& square) {
  os << square.getRow() << ", " << square.getColumn() << " Identificador: " << square.getIdentifier() << std::endl;
  return os;
}