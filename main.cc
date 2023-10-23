#include <fstream>

#include "maze.h"

int main(int argc, char* argv[]) {
    std::string filename = argv[1];
    std::string output_name = argv[2];
    //std::ofstream output;
    //output.open(output_name);
    //output << "Escribe" << std::endl;
    Maze maze(filename);
    maze.Print();
    maze.AStarSearch(output_name);
    /*maze.ModifyExit(0, 9);
    maze.Print();
    maze.AStarSearch();*/
    return 0;
}