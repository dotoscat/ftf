#include "engine.hpp"
#include "game.hpp"

fff::engine::engine(){
    space = cpSpaceNew();
}

fff::engine::~engine(){
    cpSpaceFree(space);
}

void fff::engine::Event(sf::Event &event){
}

void fff::engine::Run(sf::RenderTarget &rendertarget){
    cpSpaceStep(space, game.realwindow.GetFrameTime()/1000.f);
}
