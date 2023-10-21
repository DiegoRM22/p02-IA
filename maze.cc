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
    open_list.clear();
    closed_list.clear();
    other_open_list.clear();
    HeuristicCost(enter_);
    AccumulatedCost(enter_);
    TotalCost(enter_);
    open_list.insert(enter_);
    other_open_list.insert(*enter_);
    vector_open_list.push_back(*enter_);
    int counter{0};
    while (!other_open_list.empty()) {
        std::cout << "Iteracion: " << counter << std::endl;
        DeleteDuplicates();
        SortVector();
        //PrintOpenList();
        //PrintOtherList();
        PrintVectorList();
        PrintOtherClosedList();
        PrintClosedList();
        //Square other_square = *other_open_list.begin();
        Square other_square = vector_open_list[0];

        //other_open_list.erase(other_square);
        vector_open_list.erase(vector_open_list.begin());
        std::cout << "Sacamos la casilla: " << other_square << " de la lista de nodos abiertos" << std::endl;
        Square *square = new Square(other_square);
        closed_list.insert(square);
        other_closed_list.insert(*square);
        if (other_square.getIdentifier() == '4') {
            std::cout << "Se ha encontrado la salida" << std::endl;
            PrintPath(&other_square);
            break;
        }
        
        std::cout << '\n';
        CheckNeighbours(other_square);
        

        /* Esperar a que el usuario pulse enter*/
        
        std::cin.ignore();
        /*Limpiar la pantalla*/
        ++counter;

    }
}



void Maze::CheckNeighbours(Square current_square) {
    for (int i{current_square.getRow() - 1}; i <= current_square.getRow() + 1;++i) {
        for (int j{current_square.getColumn() - 1}; j <= current_square.getColumn() + 1; ++j) {
           Square neighbour = map_[i][j];
            if (j >= 0 && j < cols_ && i >= 0 && i < rows_ 
                && neighbour.getIdentifier() != '1' && neighbour != current_square) {
                std:: cout << "i: " << i << " j: " << j << std::endl;

                // Si no está en la lista C.
                if (other_closed_list.find(neighbour) == other_closed_list.end()) {
                    neighbour.setFather(&current_square);
                    HeuristicCost(&neighbour);
                    AccumulatedCost(&neighbour);
                    TotalCost(&neighbour);
                    std::cout << "Casilla: " << neighbour << "Coste Fn: " << neighbour.getFnCost() << std::endl;
                    // Si no está en A, lo metemos.
                    if (IsInVector(vector_open_list, neighbour) == false) {
                        std::cout << "LA METEMOS EN A" << std::endl;
                        //int prev_size = vector_open_list.size();
                        //Square node = SearchNode(other_open_list, neighbour);
                        //other_open_list.insert(neighbour);
                        vector_open_list.push_back(neighbour);
                        //int new_size = other_open_list.size();
                        /*if (prev_size < new_size) {
                            std::cout << "Se ha insertado correctamente" << std::endl;
                        } else {
                            PrintOtherList();
                            std::cout << "No se ha insertado correctamente, el nodo que habia era: " << node  << node.getFnCost() << std::endl;
                            //other_open_list.erase(node);
                            Square new_node(neighbour);
                            other_open_list.insert(new_node);
                            PrintOtherList();
                        }*/
                    } else {
                        // Si esta en A.
                        std::cout << "ESTA EN A" << std::endl;
                        Square* found_node = FindInVector(vector_open_list, neighbour);
                        if (found_node->getFnCost() > neighbour.getFnCost()) {
                            // Si el coste de la casilla actual es menor que el de la casilla encontrada en A, actualizamos el coste de la casilla encontrada en A.
                            std::cout << "Actualizamos el coste: " << found_node->getFnCost() << " -> " << neighbour.getFnCost() << std::endl;
                           // other_open_list.erase(found_node);
                            //other_open_list.insert(neighbour);
                            found_node->setFather(&current_square);
                            AccumulatedCost(found_node);
                            TotalCost(found_node);
                        }


                    }
                }
            }
        }
    } 
}




/*void Maze::CheckNeighbours(Square* current_square) {
    for (int i{current_square->getRow() - 1}; i <= current_square->getRow() + 1;++i) {
        for (int j{current_square->getColumn() - 1}; j <= current_square->getColumn() + 1; ++j) {
            //std::cout << "i: " << i << " j: " << j << std::endl;
            Square* neighbour =  new Square(map_[i][j]);
            if (*neighbour != *current_square && neighbour->getIdentifier() != '1' && i >= 0 && i < rows_ && j >= 0 && j < cols_) {
                if (other_closed_list.find(*neighbour) == other_closed_list.end()) {
                    std::cout << "Casilla: " << *neighbour;
                    // Si no está ni en A ni en C.
                    //std::cout << "Casilla: " << *neighbour << std::endl;
                    if (other_open_list.find(map_[i][j]) == other_open_list.end()) {
                        //std::cout << "No esta ni en A ni en C" << std::endl;
                        std:: cout << "... No esta ni en A ni en C" << std::endl;
                        neighbour->setFather(current_square);
                        HeuristicCost(neighbour);
                        AccumulatedCost(neighbour);
                        TotalCost(neighbour);
                        open_list.insert(neighbour);
                        other_open_list.insert(*neighbour);
                        //std::cout << "tamaño de la lista abierta: " << open_list.size() << std::endl;

                    } else if (other_open_list.find(map_[i][j]) != other_open_list.end() && other_closed_list.find(*neighbour) == other_closed_list.end()) {
                        // Si el nodo está en A, actualizar su coste g(n) y por tanto su padre en el camino.
                        std:: cout << "... Esta en A, quizas haya que actualizar su coste." << std::endl;
                        //std::cout << "Esta en A" << std::endl;
                        PrintOpenList();
                        neighbour->setFather(current_square);
                        AccumulatedCost(neighbour);
                    }
                }
            }
        }
    } 
}*/

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

void Maze::PrintOpenList() const {
    std::cout << "Lista abierta: " << std::endl;
    for (std::set<Square*>::iterator it = open_list.begin(); it != open_list.end(); ++it) {
        std::cout << (*it)->getRow() << ", " << (*it)->getColumn() << " " << (*it)->getFnCost() << std::endl;
    }
}

void Maze::PrintOtherList() const{
    std::cout << "Lista abierta de otros: " << std::endl;
    for (std::set<Square>::iterator it = other_open_list.begin(); it != other_open_list.end(); ++it) {
        std::cout << it->getRow() << ", " << it->getColumn() << " " << it->getFnCost() << std::endl;
    }
}

void Maze::PrintClosedList() const {
    std::cout << "Lista cerrada: " << std::endl;
    for (std::set<Square*>::iterator it = closed_list.begin(); it != closed_list.end(); ++it) {
        std::cout << (*it)->getRow() << ", " << (*it)->getColumn() << " " << (*it)->getFnCost() << std::endl;
    }
}

void Maze::PrintOtherClosedList() const {
    std::cout << "Lista cerrada de otros: " << std::endl;
    for (std::set<Square>::iterator it = other_closed_list.begin(); it != other_closed_list.end(); ++it) {
        std::cout << it->getRow() << ", " << it->getColumn() << " " << it->getFnCost() << std::endl;
    }
}

void Maze::PrintPath(Square* exit) const {
    Square* current_square = exit;
    while (current_square->getFather() != nullptr) {
        std::cout << *current_square << std::endl;
        current_square = current_square->getFather();
    }
    std::cout << *current_square << std::endl;
}

void Maze::PrintVectorList() const {
    std::cout << "lista abierta: " << std::endl;
  for (int i{0}; i < vector_open_list.size(); ++i) {
    std::cout << vector_open_list[i];
  }
}

void Maze::SortVector() {
    /*Ordenar, poniendo primero los de menor coste Fn*/
    for (int i{0}; i < vector_open_list.size(); ++i) {
        for (int j{0}; j < vector_open_list.size(); ++j) {
            if (vector_open_list[i].getFnCost() < vector_open_list[j].getFnCost()) {
                Square aux = vector_open_list[i];
                vector_open_list[i] = vector_open_list[j];
                vector_open_list[j] = aux;
            }
        }
    }
}

void Maze::DeleteDuplicates() {
    for (int i{0}; i < vector_open_list.size(); ++i) {
        for (int j{0}; j < vector_open_list.size(); ++j) {
            if (vector_open_list[i] == vector_open_list[j] && i != j) {
                vector_open_list.erase(vector_open_list.begin() + j);
            }
        }
    }
}


bool IsInList(std::set<Square> list, Square node) {
    for (std::set<Square>::iterator it = list.begin(); it != list.end(); ++it) {
        if (*it == node) {
            return true;
        }
    }
    return false;
}

Square SearchNode(std::set<Square> list, Square node) {
    for (std::set<Square>::iterator it = list.begin(); it != list.end(); ++it) {
        if (*it == node) {
            return *it;
        }
    }
    return node;
}

Square* FindInVector(std::vector<Square> vector, Square node) {
  for (int i{0}; i < vector.size(); ++i) {
    if (vector[i] == node) {
      return &vector[i];
    }
  }
  return nullptr;
}

bool IsInVector(std::vector<Square> vector, Square node) {  
  for (int i{0}; i < vector.size(); ++i) {
    if (vector[i] == node) {
      return true;
    }
  }
  return false;
}