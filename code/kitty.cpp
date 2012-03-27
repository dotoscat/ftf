#include <iostream>
#include "kitty.hpp"
#include "game.hpp"
#include "auxiliar.hpp"

fff::kitty::kitty(){
    body = cpBodyNew(1.f, INFINITY);
}

fff::kitty::~kitty(){
    cpBodyFree(body);
    cpShapeFree(shape);
}

void fff::kitty::Configure(){
    fff::SetOriginByLua(game.vm, sprite, "kitty");
    shape = cpCircleShapeNew(body, fff::GetRadiusByLua(game.vm, "kitty"), (cpVect){0.f, 0.f} );
}

void fff::kitty::setInitialFallingSpeed(float speed){
    cpVect vel = {0, speed};
    cpBodySetVel(body, vel);
}

void fff::kitty::setPosition(float x, float y){
    cpVect pos = {x, y};
    cpBodySetPos(body, pos);
}

void fff::kitty::moveLeft(){
    cpBodyApplyImpulse(body, (cpVect){-640.f, 0.f}, cpvzero);
}

void fff::kitty::stopMovingLeft(){
    cpBodyApplyImpulse(body, (cpVect){640.f, 0.f}, cpvzero);
}

void fff::kitty::moveRight(){
    cpBodyApplyImpulse(body, (cpVect){640.f, 0.f}, cpvzero);
}

void fff::kitty::stopMovingRight(){
    cpBodyApplyImpulse(body, (cpVect){-640.f, 0.f}, cpvzero);
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
