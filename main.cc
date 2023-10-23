#include <fstream>
#include <chrono>

#include "maze.h"

int main(int argc, char* argv[]) {
    std::string filename = argv[1];
    std::string output_name = argv[2];
    //std::ofstream output;
    //output.open(output_name);
    //output << "Escribe" << std::endl;
    Maze maze(filename);
    maze.Print();
    std::cout << "Elija una opción:" << std::endl;
    std::cout << "0. Heurística Manhattan\n" << "1. Heurística de distancia euclídea" << std::endl;
    int option;
    std::cin >> option;
    //auto start = std::chrono::high_resolution_clock::now(); // get start time
    maze.AStarSearch(output_name, option);
    /*auto end = std::chrono::high_resolution_clock::now(); // get end time
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // calculate duration in microseconds
    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl; // print duration
    auto start2 = std::chrono::high_resolution_clock::now(); // get start time
    maze.AStarSearch(output_name, 1);
    auto end2 = std::chrono::high_resolution_clock::now(); // get end time
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2); // calculate duration in microseconds
    std::cout << "Execution time: " << duration2.count() << " microseconds" << std::endl; // print duration*/

    /*Calcular el tiempo de ejecucion*/

    std::cout << "Desea cambiar la entrada/salida(S/N)?" << std::endl;
    char answer;
    std::cin >> answer;
    if (answer == 'S') {
        std::cout << "Introduzca la nueva entrada (fila, columna): ";
        int enter_row, enter_col;
        std::cin >> enter_row >> enter_col;
        maze.ModifyEnter(enter_row, enter_col);
        std::cout << "Introduzca la nueva salida (fila, columna): ";
        int exit_row, exit_col;
        std::cin >> exit_row >> exit_col;
        maze.ModifyExit(exit_row, exit_col);
        maze.Print();
        maze.AStarSearch(output_name, option);
    }
    
    return 0;
}