

#include "maze.h"

int main(int argc, char* argv[]) {
    std::string filename = argv[1];
    Maze maze(filename);
    maze.Print();
    maze.AStarSearch();
    /*maze.ModifyExit(0, 9);
    maze.Print();
    maze.AStarSearch();*/
    return 0;
}