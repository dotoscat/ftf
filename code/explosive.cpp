#include <chipmunk/chipmunk.h>
#include <chipmunk/chipmunk_unsafe.h>
#include "explosive.hpp"
#include "auxiliar.hpp"
#include "game.hpp"

fff::explosive::explosive(){
    exists = false;
    impulse = 0.f;
    shape = NULL;
}

fff::explosive::~explosive(){
    if (shape == NULL){
        return;}
    cpShapeFree(shape);
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
