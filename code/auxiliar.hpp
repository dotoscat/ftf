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

#ifndef _auxiliar_
#define _auxiliar_

#include <lua5.1/lua.hpp>
#include <SFML/Graphics.hpp>
//#include <chipmunk/chipmunk.h>

namespace fff{
    
    void SetOriginByLua(lua_State *, sf::Drawable &, const char *);
    float GetRadiusByLua(lua_State *, const char *);
    int GetAppereanceByLua(lua_State *, const char *);
    float GetImpulseByLua(lua_State *, const char *);
    const char *GetTextureByLua(lua_State *, const char *);
    
}

#endif
