#include "kitty.hpp"
#include "game.hpp"

fff::kitty::kitty(){
    body = cpBodyNew(1.f, INFINITY);
}

fff::kitty::~kitty(){
    cpBodyFree(body);
}

void fff::kitty::setPosition(float x, float y){
    cpVect pos = {x, y};
    cpBodySetPos(body, pos);
}

float fff::kitty::getHeight(){
    cpVect pos = cpBodyGetPos(body);
    return pos.y;
}

void fff::kitty::Update(){
    cpVect pos = cpBodyGetPos(body);
    sprite.SetPosition(pos.x, pos.y);
}
