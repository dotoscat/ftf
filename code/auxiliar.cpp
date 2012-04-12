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
