#ifndef _auxiliar_
#define _auxiliar_

#include <lua5.1/lua.hpp>
#include <SFML/Graphics.hpp>
//#include <chipmunk/chipmunk.h>

namespace fff{
    
    void SetOriginByLua(lua_State *, sf::Drawable &, const char *);
    
}

#endif
