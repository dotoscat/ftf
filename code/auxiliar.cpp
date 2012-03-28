#include "auxiliar.hpp"

void fff::SetOriginByLua(lua_State *vm, sf::Drawable &drawable, const char *object){
    lua_Number x=0, y=0;
    lua_getglobal(vm, object);
    lua_getfield(vm, -1, "originx");
    x = lua_tonumber(vm, -1);
    lua_pop(vm, 1);//x
    lua_getfield(vm, -1, "originy");
    y = lua_tonumber(vm, -1);
    lua_pop(vm, 2);//y and object
    drawable.SetOrigin(x, y);
}

float fff::GetRadiusByLua(lua_State *vm, const char *object){
    lua_getglobal(vm, object);
    lua_getfield(vm, -1, "radius");
    float radius = lua_tonumber(vm, -1);
    lua_pop(vm, 2);//radius and object
    return radius;
}

int fff::GetAppereanceByLua(lua_State *vm, const char *object){
    lua_getglobal(vm, object);
    lua_getfield(vm, -1, "appareance");
    int appareance = lua_tonumber(vm, -1);
    lua_pop(vm, 2);//appareance and object
    return appareance;
}

float fff::GetImpulseByLua(lua_State *vm, const char *object){
    lua_getglobal(vm, object);
    lua_getfield(vm, -1, "impulse");
    float impulse = lua_tonumber(vm, -1);
    lua_pop(vm, 2);//impulse and object
    return impulse;
}

const char *fff::GetTextureByLua(lua_State *vm, const char *object){
    lua_getglobal(vm, object);
    lua_getfield(vm, -1, "texture");
    const char *texture = lua_tostring(vm, -1);
    lua_pop(vm, 2);//texture and object
    return texture;
}
