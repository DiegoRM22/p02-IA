

#include "maze.h"

int main(int argc, char* argv[]) {
    std::string filename = argv[1];
    Maze maze(filename);
    maze.Print();
    std::cout << '\n';
    maze.Print();
    return 0;
}