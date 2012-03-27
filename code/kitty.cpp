#include <iostream>
#include "kitty.hpp"
#include "game.hpp"

fff::kitty::kitty(){
    body = cpBodyNew(1.f, INFINITY);
}

fff::kitty::~kitty(){
    cpBodyFree(body);
}

void fff::kitty::setInitialFallingSpeed(float speed){
    //this speed in in km/h transform to meters/s
    cpVect vel = {0, speed*1000.f/60.f/60.f};
    cpBodySetVel(body, vel);
}

void fff::kitty::setPosition(float x, float y){
    cpVect pos = {x, y};
    cpBodySetPos(body, pos);
}

float fff::kitty::getHeight(){
    cpVect pos = cpBodyGetPos(body);
    return pos.y;
}

float fff::kitty::getVerticalSpeed(){
    cpVect vel = cpBodyGetVel(body);
    return vel.y;
}

void fff::kitty::Update(){
    cpVect pos = cpBodyGetPos(body);
    sprite.SetPosition(pos.x, pos.y);
}
