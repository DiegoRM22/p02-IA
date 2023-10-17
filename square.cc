#include "square.h"

bool operator<(const Square& square, const Square& other_square) {
  return square.getFnCost() < other_square.getFnCost();
}