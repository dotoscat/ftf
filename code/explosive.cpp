#include <iostream>
#include <cmath>
#include <cstdio>
#include <chipmunk/chipmunk.h>
#include <chipmunk/chipmunk_unsafe.h>
#include "explosive.hpp"
#include "auxiliar.hpp"
#include "game.hpp"

fff::explosive::explosive(){
    exists = false;
    impulse = 0.f;
    meters.SetColor(sf::Color::Black);
    meters.SetCharacterSize(14);
    shape = NULL;
}

fff::explosive::~explosive(){
    if (shape == NULL){
        return;}
    cpShapeFree(shape);
}

void fff::explosive::loadResources(){
    fff::SetOriginByLua(game.vm, arrow, "arrow");
    arrow.SetTexture(*game.textures["arrow"]);
}

void fff::explosive::prepareShape(cpSpace *space){
    shape = cpCircleShapeNew( cpSpaceGetStaticBody(space), 1.f, (cpVect){0.f, 0.f} );
}

void fff::explosive::Configure(const char *object){
    fff::SetOriginByLua(game.vm, sprite, object);
    impulse = fff::GetImpulseByLua(game.vm, object);
    sprite.SetTexture( *game.textures[ const_cast<char *>(fff::GetTextureByLua(game.vm, object)) ] );
    cpCircleShapeSetRadius(shape, fff::GetRadiusByLua(game.vm, object));
    exists = true;
}

void fff::explosive::setPosition(float x, float y){
    cpCircleShapeSetOffset(shape, (cpVect){x, y});
    sprite.SetPosition(x, y);
    arrow.SetX(x);
    meters.SetX(x);
}

void fff::explosive::setArrowAtBottom(){
    arrow.SetY(400);
    meters.SetY(400);
    arrow.FlipY(false);
}

void fff::explosive::setArrowAtTop(){
    arrow.SetY(80);
    meters.SetY(80);
    arrow.FlipY(true);
}

void fff::explosive::Update(float y){
    char buffer[8] = {0};
    sf::Vector2f pos = sprite.GetPosition();
    int m = fabsf(y) - fabsf(pos.y);
    snprintf(buffer, 8, "%d", abs(int(PIXELSTOMETERS(m))) );
    meters.SetString(buffer);
    //sf::FloatRectr rect = meter.GetRect();
}
