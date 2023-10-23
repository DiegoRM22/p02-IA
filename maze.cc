#include <fstream>
#include <set>

#include "maze.h"

void FilePutContents(const std::string& name, const std::string& content, bool append) {
    //std::cout << "ESCRIBIENDO EN EL ARCHIVO " << name  << " " << content << std::endl;
    std::ofstream outfile;
    //outfile << "Filas: " << std::endl;
    if (append) {
        outfile.open(name, std::ios_base::app);
    } else {
        outfile.open(name);
    }
    outfile << content;
}

Maze::Maze(const std::string filename) {
    std::ifstream file(filename);
    //std::cout << "Leyendo el archivo " << filename << std::endl;
    file >> rows_;
    file >> cols_;
    std::string current_line;
    getline(file, current_line);
    //std::cout << "El laberinto tiene " << rows_ << " filas y " << cols_ << " columnas" << std::endl;
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

void Maze::AStarSearch(const std::string& filename) {
    FilePutContents(filename, "Filas: " + std::to_string(rows_) + '\n', true); 
    FilePutContents(filename, "Columnas: " + std::to_string(cols_) + '\n', true);
    FilePutContents(filename, "Entrada: " + std::to_string(enter_->getRow()) + ", " + std::to_string(enter_->getColumn()) + '\n', true);
    FilePutContents(filename, "Salida: " + std::to_string(exit_->getRow()) + ", " + std::to_string(exit_->getColumn()) + '\n', true);
    vector_open_list.clear();
    vector_closed_list.clear();
    HeuristicCost(enter_);
    AccumulatedCost(enter_);
    TotalCost(enter_);
    vector_open_list.push_back(enter_);
    int counter{0};
    while (!vector_open_list.empty()) {
        //std::cout << "Iteracion: " << counter << std::endl;
        DeleteDuplicates();
        SortVector();
        
        //PrintVectorOpenList();
        //PrintVectorClosedList();
        //Square other_square = *other_open_list.begin();
        Square* other_square = vector_open_list.front();
        //other_open_list.erase(other_square);
        vector_open_list.erase(vector_open_list.begin());
        vector_closed_list.push_back(other_square);
        analysed_nodes.push_back(other_square);
        
        //std::cout << "Sacamos la casilla: " << *other_square << " de la lista de nodos abiertos" << std::endl;
        if (other_square->getIdentifier() == '4') {
            std::cout << "Se ha encontrado la salida" << std::endl;
            PrintPath(other_square, filename);
            PrintGeneratedNodes(filename);
            FilePutContents(filename, "\n", true);
            PrintAnalysedNodes(filename);
            return;
        }
        
        //std::cout << '\n';
        CheckNeighbours(other_square);
        //std::cout << "sale de aqui" << std::endl;

        /* Esperar a que el usuario pulse enter*/
        
        //std::cin.ignore();
        /*Limpiar la pantalla*/
        ++counter;

    }
    //std::cout << "El laberinto no tiene solucion" << std::endl;
    FilePutContents(filename, "El laberinto no tiene solucion\n", true);
    PrintGeneratedNodes(filename);
    FilePutContents(filename, "\n", true);
    PrintAnalysedNodes(filename);
}



void Maze::CheckNeighbours(Square* current_square) {
    for (int i{current_square->getRow() - 1}; i <= current_square->getRow() + 1;++i) {
        for (int j{current_square->getColumn() - 1}; j <= current_square->getColumn() + 1; ++j) {
            //std::cout << "viendo vecinos" << std::endl;
           if (j >= 0 && j < cols_ && i >= 0 && i < rows_) {
                Square* neighbour =  new Square(map_[i][j]);
                if (neighbour->getIdentifier() != '1' && *neighbour != *current_square) {
                    //std:: cout << "i: " << i << " j: " << j << std::endl;

                    // Si no está en la lista C.
                    if (IsInVector(vector_closed_list, neighbour) == false) {
                        neighbour->setFather(current_square);
                        HeuristicCost(neighbour);
                        AccumulatedCost(neighbour);
                        TotalCost(neighbour);
                        //std::cout << "Casilla: " << *neighbour << "Coste Fn: " << neighbour->getFnCost() << std::endl;
                        // Si no está en A, lo metemos.
                        if (IsInVector(vector_open_list, neighbour) == false) {
                            //std::cout << "LO METEMOS EN A" << std::endl;
                            vector_open_list.push_back(neighbour);
                            generated_nodes.push_back(neighbour);
                            //std::cout << "ENtro" << std::endl;
                            
                        } else {
                            // Si esta en A.
                            //std::cout << "ESTA EN A" << std::endl;
                            Square* found_node = FindInVector(vector_open_list, neighbour);
                            if (found_node->getFnCost() > neighbour->getFnCost()) {
                                // Si el coste de la casilla actual es menor que el de la casilla encontrada en A, actualizamos el coste de la casilla encontrada en A.
                                //std::cout << "Actualizamos el coste: " << found_node->getFnCost() << " -> " << neighbour->getFnCost() << std::endl;
                            // other_open_list.erase(found_node);
                                //other_open_list.insert(neighbour);
                                found_node->setFather(current_square);
                                AccumulatedCost(found_node);
                                TotalCost(found_node);
                                generated_nodes.push_back(found_node);
                            }


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
    FilePutContents("output.txt", "Laberinto de dimensiones " + std::to_string(rows_) + "x" + std::to_string(cols_) + '\n', false);
    for (int i{0}; i < rows_; ++i) {
        for (int j{0}; j < cols_; ++j) {
            FilePutContents("output.txt", std::string(1, map_[i][j].getIdentifier()) + " ", true);
        }
        FilePutContents("output.txt", "\n", true);
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

void Maze::PrintPath(Square* exit, const std::string& filename) const {
    Square* current_square = exit;
    FilePutContents(filename, "Solución: ", true);
    while (current_square->getFather() != nullptr) {
        //outfile << *current_square << std::endl;
        std::string content = "(" + std::to_string(current_square->getRow()) + "," + std::to_string(current_square->getColumn()) + ")" + " <- ";
        FilePutContents(filename, content, true);
        current_square = current_square->getFather();
    }
    std::string content = "(" + std::to_string(current_square->getRow()) + "," + std::to_string(current_square->getColumn()) + ")" + '\n';
    FilePutContents(filename, content, true);
    //outfile << *current_square << std::endl;
}

void Maze::PrintVectorOpenList() const {
    std::cout << "lista abierta: " << std::endl;
  for (int i{0}; i < vector_open_list.size(); ++i) {
    std::cout << *vector_open_list[i];
  }
}

void Maze::PrintVectorClosedList() const {
    std::cout << "lista cerrada: " << std::endl;
  for (int i{0}; i < vector_closed_list.size(); ++i) {
    std::cout << *vector_closed_list[i];
  }
}

void Maze::PrintGeneratedNodes(const std::string& filename) const {
    FilePutContents(filename, "Nodos generados: ", true);
    for (int i{0}; i < generated_nodes.size(); ++i) {
        std::string content = "(" + std::to_string(generated_nodes[i]->getRow()) + "," + std::to_string(generated_nodes[i]->getColumn()) + ")" + " , ";
        FilePutContents(filename, content, true);
    }
}

void Maze::PrintAnalysedNodes(const std::string& filename) const {
    FilePutContents(filename, "Nodos analizados: ", true);
    for (int i{0}; i < analysed_nodes.size(); ++i) {
        std::string content = "(" + std::to_string(analysed_nodes[i]->getRow()) + "," + std::to_string(analysed_nodes[i]->getColumn()) + ")" + " , ";
        FilePutContents(filename, content, true);
    }
}

void Maze::SortVector() {
    /*Ordenar, poniendo primero los de menor coste Fn*/
    for (int i{0}; i < vector_open_list.size(); ++i) {
        for (int j{0}; j < vector_open_list.size(); ++j) {
            if (vector_open_list[i]->getFnCost() < vector_open_list[j]->getFnCost()) {
                Square* aux = vector_open_list[i];
                vector_open_list[i] = vector_open_list[j];
                vector_open_list[j] = aux;
            }
        }
    }
}

void Maze::DeleteDuplicates() {
    for (int i{0}; i < vector_open_list.size(); ++i) {
        for (int j{0}; j < vector_open_list.size(); ++j) {
            if (*vector_open_list[i] == *vector_open_list[j] && i != j) {
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

Square* FindInVector(std::vector<Square*> vector, Square* node) {
  for (int i{0}; i < vector.size(); ++i) {
    if (*vector[i] == *node) {
      return vector[i];
    }
  }
  return nullptr;
}

bool IsInVector(std::vector<Square*> vector, Square* node) {  
  for (int i{0}; i < vector.size(); ++i) {
    if (*vector[i] == *node) {
      return true;
    }
  }
  return false;
}

