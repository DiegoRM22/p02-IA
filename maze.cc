#include <fstream>

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
        /*Eliminar espacio en blaco de current_line*/
        int counterCols{0};
        for (int j{0}; counterCols < cols_; ++j) {
            if (current_line[j] != ' ') {
                if (current_line[j] == '3') {
                    enter_ = &map_[i][counterCols];
                } else if (current_line[j] == '4') {
                    exit_ = &map_[i][counterCols];
                }
                Square square(current_line[j]);
                map_[i][counterCols] = square;
                ++counterCols;
            }
        }
        ++i;
    }
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