#include <cmath>
#include <iostream>
#include "kitty.hpp"
#include "game.hpp"
#include "auxiliar.hpp"
#include "collisions.hpp"

fff::kitty::kitty(){
    body = cpBodyNew(1.f, INFINITY);
    cpBodySetUserData(body, this);
    
    forecastspace = cpSpaceNew();
    cpBodyInit(&forecastbody, 1.f, INFINITY);
    cpSpaceSetGravity(forecastspace, (cpVect){0.f, METERSTOPIXELS(10.f)} );
    cpSpaceAddBody(forecastspace, &forecastbody);
    
}

fff::kitty::~kitty(){
    cpBodyFree(body);
    cpShapeFree(shape);
    cpSpaceFree(forecastspace);
}

void fff::kitty::Configure(){
    fff::SetOriginByLua(game.vm, sprite, "kitty");
    shape = cpCircleShapeNew(body, fff::GetRadiusByLua(game.vm, "kitty"), (cpVect){0.f, 0.f} );
    cpShapeSetUserData(shape, this);
    cpShapeSetCollisionType(shape, fff::collisions::types::kitty);
}

void fff::kitty::setInitialFallingSpeed(float speed){
    cpVect vel = {0, KMH_TO_PXS(speed)};
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
    return PXS_TO_KMH(vel.y);
}

float fff::kitty::getVerticalSpeedPxls(){
    cpVect vel = cpBodyGetVel(body);
    return vel.y;
}

bool fff::kitty::isFalling(){
    cpVect vel = cpBodyGetVel(body);
    if( vel.y > 0.f){
        return true;}
    return false;
}

bool fff::kitty::isClimbing(){
    cpVect vel = cpBodyGetVel(body);
    if( vel.y < 0.f){
        return true;}
    return false;
}

void fff::kitty::applyImpulse(float impulse){
    cpVect vel = cpBodyGetVel(body);
    if (vel.y > 0.f){
        //falling
        vel.y = impulse;
    }else{
        //climbing
        vel.y += impulse;
    }
    cpBodySetVel(body, vel);
}

void fff::kitty::Update(){
    cpVect pos = cpBodyGetPos(body);
    sprite.SetPosition(pos.x, pos.y);
}

float fff::kitty::forecastYPositionTo(float time){
    forecastbody = *body;
    cpSpaceStep(forecastspace, time);
    cpVect pos = cpBodyGetPos(&forecastbody);
    return pos.y;
}
