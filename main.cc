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


    /*maze.ModifyExit(0, 9);
    maze.Print();
    maze.AStarSearch();*/
    return 0;
}