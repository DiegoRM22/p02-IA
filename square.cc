/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Informática Básica
  *
  * @author Diego Rodríguez alu0101464992@ull.edu.es
  * @brief Este programa implementa los metodos de la clase Square.
  * @bug No hay bugs conocidos
  */

#include "square.h"

bool operator<(const Square& square, const Square& other_square) {
  return (square.getFnCost() < other_square.getFnCost());
}

bool operator>(const Square& square, const Square& other_square) {
  return (square.getFnCost() > other_square.getFnCost());
}

bool operator==(const Square& square, const Square& other_square) {
  return (square.getRow() == other_square.getRow()) && (square.getColumn() == other_square.getColumn());
}

bool operator!=(const Square& square, const Square& other_square) {
  return (square.getRow() != other_square.getRow() || square.getColumn() != other_square.getColumn());
}

std::ostream& operator<<(std::ostream& os, const Square& square) {
  os << square.getRow() << ", " << square.getColumn() << " Identificador: " << square.getIdentifier() << " Coste: " <<
  square.getFnCost() << std::endl;
  return os;
}