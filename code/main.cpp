#include <cstdlib>
#include "game.hpp"

int main(int argc, char *argv[]){
    srand( time(NULL) );
    fff::game.loadResources();
    fff::game.Run();
    return EXIT_SUCCESS;
}
