#include <fstream>
#include <set>

#include "maze.h"

Maze::Maze(const std::string filename) {
    std::ifstream file(filename);
    std::cout << "Leyendo el archivo " << filename << std::endl;
    file >> rows_;
    file >> cols_;
    std::string current_line;
    getline(file, current_line);
    std::cout << "El laberinto tiene " << rows_ << " filas y " << cols_ << " columnas" << std::endl;
    int i{0};
    map_.resize(rows_, std::vector<Square>(cols_));
    while(file.peek() != EOF) {
        getline(file, current_line);
        int counterCols{0};
        for (int j{0}; counterCols < cols_; ++j) {
            if (current_line[j] != ' ') {
                if (current_line[j] == '3') {
                    enter_ = &map_[i][counterCols];
                } else if (current_line[j] == '4') {
                    exit_ = &map_[i][counterCols];
                }
                Square square(i, counterCols, current_line[j]);
                map_[i][counterCols] = square;
                ++counterCols;
            }
        }
        ++i;
    }
}

void Maze::AStarSearch() {
    std::set<Square*> open_list;
    std::vector<Square*> closed_list;
    HeuristicCost(enter_);
    AccumulatedCost(enter_);
    TotalCost(enter_);
    open_list.insert(enter_);
    std::cout << "Costo heuristico de la casilla de entrada: " << enter_->getHnCost() << std::endl;
    std::cout << "Costo acumulado de la casilla de entrada: " << enter_->getGnCost() << std::endl;
    std::cout << "Costo total de la casilla de entrada: " << enter_->getFnCost() << std::endl;
}

void Maze::HeuristicCost(Square* current_square) {
    // Diferencia de casillas en la fila.
    int row_difference{abs(current_square->getRow() - exit_->getRow())};
    // diferencia de casillas en la columna.
    int column_difference{abs(current_square->getColumn() - exit_->getColumn())};
    // Suma de las casillas de diferencia por el precio de movimiento horizontal o vertical.
    current_square->setHnCost((row_difference + column_difference) * kCostStraight);
}

void Maze::AccumulatedCost(Square* current_square) {
    // Si la casilla actual no tiene padre, su costo acumulado es 0, porque es la de Entrada.
    if (current_square->getFather() == nullptr) {
        current_square->setGnCost(0);
    } else {
        Square* father = current_square->getFather();
        // Si están en la misma fila o columna padre e hijo, el costo acumulado es el del padre más el costo de movimiento horizontal o vertical.
        if (current_square->getRow() == father->getRow() || current_square->getColumn() == father->getColumn()) {
            current_square->setGnCost(current_square->getFather()->getGnCost() + kCostStraight);
        } else {
            // Si no, el costo acumulado es el del padre más el costo de movimiento diagonal.
            current_square->setGnCost(current_square->getFather()->getGnCost() + kCostDiagonal);
        }
    }
}

void Maze::TotalCost(Square* current_square) {
    // f(n) = g(n) + h(n)
    current_square->setFnCost(current_square->getGnCost() + current_square->getHnCost());
}

void Maze::Print() const{
    std::cout << "Laberinto de dimensiones " << rows_ << "x" << cols_ << std::endl;
    for (int i{0}; i < rows_; ++i) {
        for (int j{0}; j < cols_; ++j) {
            std::cout << map_[i][j].getIdentifier() << " ";
        }
        std::cout << std::endl;
    }
}

void Maze::ModifyEnter(const int enter_row, const int enter_col) {
    enter_->setIdentifier(map_[enter_row][enter_col].getIdentifier());
    map_[enter_row][enter_col].setIdentifier('3');
    enter_ = &map_[enter_row][enter_col];
}

void Maze::ModifyExit(const int exit_row, const int exit_col) {
    exit_->setIdentifier(map_[exit_row][exit_col].getIdentifier());
    map_[exit_row][exit_col].setIdentifier('4');
    exit_ = &map_[exit_row][exit_col];
}