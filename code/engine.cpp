#include "engine.hpp"

fff::engine::engine(){
    space = cpSpaceNew();
}

fff::engine::~engine(){
    cpSpaceFree(space);
}
