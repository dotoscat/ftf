//Copyright (C) 2012 Oscar Triano Garcia <teritriano@gmail.com>

//This file is part of Free To Fall.

//Free To Fall is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//Free To Fall is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with Free To Fall.  If not, see <http://www.gnu.org/licenses/>.

#include <iostream>
#include <cmath>
#include <cstdio>
#include <chipmunk/chipmunk.h>
#include <chipmunk/chipmunk_unsafe.h>
#include "explosive.hpp"
#include "auxiliar.hpp"
#include "game.hpp"
#include "collisions.hpp"

fff::explosive::explosive(){
    exists = false;
    impulse = 0.f;
    meters.SetColor(sf::Color::Black);
    meters.SetCharacterSize(22);
    shape = NULL;
    soundbuffer = NULL;
    lifespan = 2500;//2.5 secs
}

fff::explosive::~explosive(){
    if (shape == NULL){
        return;}
    cpShapeFree(shape);
}

void fff::explosive::loadResources(){
    sf::Texture &explosiontexture = *game.textures["explosion"];
    explosion.SetOrigin( explosiontexture.GetWidth()/2, explosiontexture.GetHeight()/2 );
    explosion.SetTexture( explosiontexture );
}

void fff::explosive::prepareShape(cpSpace *space){
    shape = cpCircleShapeNew( cpSpaceGetStaticBody(space), 1.f, (cpVect){0.f, 0.f} );
    cpShapeSetUserData(shape, this);
    cpShapeSetCollisionType(shape, fff::collisions::types::explosive);
    cpShapeSetSensor(shape, cpTrue);
}

void fff::explosive::Configure(const char *object){
    fff::SetOriginByLua(game.vm, sprite, object);
    impulse = KMH_TO_PXS(fff::GetImpulseByLua(game.vm, object));
    sf::IntRect rect;
    sf::Texture *texture = game.textures[ const_cast<char *>(fff::GetTextureByLua(game.vm, object)) ];
    sprite.SetTexture( *texture );
    rect.Width = texture->GetWidth();
    rect.Height = texture->GetHeight();
    sprite.SetSubRect(rect);
    cpCircleShapeSetRadius(shape, fff::GetRadiusByLua(game.vm, object));
    exists = true;
    lua_getglobal(game.vm, object);
    lua_getfield(game.vm, -1, "sound");
    soundbuffer = game.soundbuffers[lua_tostring(game.vm, -1)];
    lua_pop(game.vm, 2);//sound and object
    status = normal;
    acumlifespan = 0;
    
    //signal
    lua_getglobal(game.vm, object);
    lua_getfield(game.vm, -1, "signal");
    sf::Vector2f origin;
    lua_getfield(game.vm, -1, "originx");
    origin.x = lua_tonumber(game.vm, -1);
    lua_pop(game.vm, 1);//originx
    lua_getfield(game.vm, -1, "originy");
    origin.y = lua_tonumber(game.vm, -1);
    lua_pop(game.vm, 1);//originy
    signal.SetOrigin(origin);
    lua_getfield(game.vm, -1, "texture");
    texture = game.textures[ lua_tostring(game.vm, -1) ];
    signal.SetTexture(*texture);
    rect.Width = texture->GetWidth();
    rect.Height = texture->GetHeight();
    signal.SetSubRect(rect);
    lua_pop(game.vm, 3);//texture, signal and object
    //
}

void fff::explosive::setPosition(float x, float y){
    cpCircleShapeSetOffset(shape, (cpVect){x, y});
    sprite.SetPosition(x, y);
    explosion.SetPosition(x, y);
    signal.SetX(x);
    meters.SetX(x);
}

void fff::explosive::setSignalAtBottom(){
    signal.SetY(400);
    meters.SetY(400);
    signal.FlipY(false);
}

void fff::explosive::setSignalAtTop(){
    signal.SetY(80);
    meters.SetY(80);
    signal.FlipY(true);
}

void fff::explosive::Update(float y){
    char buffer[8] = {0};
    sf::Vector2f pos = sprite.GetPosition();
    int m = fabsf(y) - fabsf(pos.y);
    snprintf(buffer, 8, "%d", abs(int(PIXELSTOMETERS(m))) );
    meters.SetString(buffer);
    //sf::FloatRectr rect = meter.GetRect();
}

int fff::explosive::Begin(cpArbiter *arb, cpSpace *space, void *pengine){
    CP_ARBITER_GET_SHAPES(arb, explosiveshape, kittyshape);
    fff::explosive *explosive = static_cast<fff::explosive *>( cpShapeGetUserData(explosiveshape) );
    fff::kitty *kitty = static_cast<fff::kitty *>( cpShapeGetUserData(kittyshape) );
    kitty->applyImpulse(explosive->impulse);
    explosive->setExploding();
    game.playExplosion(explosive->soundbuffer, explosive->sprite.GetPosition() );
    cpSpaceAddPostStepCallback(space, fff::explosive::postStep, explosiveshape, NULL);
    game.startTheme();
    return 0;
}

void fff::explosive::postStep(cpSpace *space, void *shape, void *data){
    cpSpaceRemoveShape(space, static_cast<cpShape *>(shape));
}

void fff::explosive::setExploding(){
    status = exploding;
    timeexploding = 0;
}

bool fff::explosive::isExploding(){
    if (status == exploding){
        return true;}
    return false;
}

bool fff::explosive::isExploded(){
    if (timeexploding > 250){
        return true;}
    return false;
}

bool fff::explosive::isOver(){
    if (acumlifespan > lifespan){
        return true;}
    return false;
}
