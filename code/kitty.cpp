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
    cpSpaceSetIterations(forecastspace, 100);
    cpBodyInit(&forecastbody, 1.f, INFINITY);
    cpSpaceSetGravity(forecastspace, (cpVect){0.f, METERSTOPIXELS(10.f)} );
    cpSpaceAddBody(forecastspace, &forecastbody);
    
    iflames = 0;
    burstinflames = false;
    
    leftimpulse = false;
    rightimpulse = false;

}

fff::kitty::~kitty(){
    cpBodyFree(body);
    cpShapeFree(shape);
    cpSpaceFree(forecastspace);
}

void fff::kitty::Reset(){
    rightimpulse = false;
    leftimpulse = false;
    cpBodyResetForces(body);
}

void fff::kitty::Configure(){
    fff::SetOriginByLua(game.vm, sprite, "kitty");
    fff::SetOriginByLua(game.vm, flames[0], "flames");
    flames[1].SetOrigin( flames[0].GetOrigin() );
    flames[0].SetTexture(*game.textures["flames"]);
    flames[1].SetTexture(*game.textures["flames"]);
    flames[1].FlipX(true);
    burst.SetBuffer(*game.soundbuffers["burstinflames"]);
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
    lastpos = pos;
    cpBodySetPos(body, pos);
}

void fff::kitty::moveLeft(){
    if (leftimpulse){
        return;}
    cpBodyApplyImpulse(body, (cpVect){-640.f, 0.f}, cpvzero);
    leftimpulse = true;
}

void fff::kitty::stopMovingLeft(){
    if (!leftimpulse){
        return;}
    cpBodyApplyImpulse(body, (cpVect){640.f, 0.f}, cpvzero);
    leftimpulse = false;
}

void fff::kitty::moveRight(){
    if (rightimpulse){
        return;}
    cpBodyApplyImpulse(body, (cpVect){640.f, 0.f}, cpvzero);
    rightimpulse = true;
}

void fff::kitty::stopMovingRight(){
    if (!rightimpulse){
        return;}
    cpBodyApplyImpulse(body, (cpVect){-640.f, 0.f}, cpvzero);
    rightimpulse = false;
}

float fff::kitty::getHeight(){
    cpVect pos = cpBodyGetPos(body);
    return pos.y;
}

float fff::kitty::getX(){
    cpVect pos = cpBodyGetPos(body);
    return pos.x;
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

bool fff::kitty::isAscending(){
    cpVect vel = cpBodyGetVel(body);
    if( vel.y < 0.f){
        return true;}
    return false;
}

bool fff::kitty::burstInFlames(){
    return burstinflames;
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
    lastpos = pos;
    sprite.SetPosition(pos.x, pos.y);
    flames[0].SetPosition(pos.x, pos.y);
    flames[1].SetPosition(pos.x, pos.y);
    cpVect vel = cpBodyGetVel(body);
    if (vel.y > KMH_TO_PXS(500.f) && !burstinflames){
        burst.Play();
        burstinflames = true;
    }else if (vel.y <= KMH_TO_PXS(500.f) ){
        burstinflames = false;
    }
    iflames += 1;
    if (iflames > 1){
        iflames = 0;
    }
}

float fff::kitty::forecastYPositionTo(float time){
    forecastbody = *body;
    cpSpaceStep(forecastspace, time);
    cpVect pos = cpBodyGetPos(&forecastbody);
    return pos.y;
}

cpVect fff::kitty::getCurrentPos(){
    return cpBodyGetPos(body);
}

sf::Sprite fff::kitty::getCurrentFrame(){
    return flames[iflames];
}
