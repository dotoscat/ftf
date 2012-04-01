#ifndef _auxiliar_
#define _auxiliar_

#include <lua5.1/lua.hpp>
#include <SFML/Graphics.hpp>

namespace fff{
    
    void SetOriginByLua(lua_State *, sf::Drawable &, const char *);
    float GetRadiusByLua(lua_State *, const char *);
    int GetAppereanceByLua(lua_State *, const char *);
    float GetImpulseByLua(lua_State *, const char *);
    const char *GetTextureByLua(lua_State *, const char *);
    
}

#endif
