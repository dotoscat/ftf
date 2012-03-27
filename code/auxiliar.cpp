#include "auxiliar"

void fff::SetOriginByLua(lua_State *vm, sf::Drawable &drawable, const char *object){
    lua_Number x=0, y=0;
    lua_getglobal(vm, object);
    lua_getfield(vm, -1, "originx");
    x = lua_tonumber(vm, -1);
    lua_pop(vm, 1);//x
    lua_getfield(vm, -1, "originy");
    y = lua_tonumber(vm, -1);
    lua_pop(vm, 1);//y
    lua_pop(vm, 1);//object
    drawable.SetOrigin(x, y);
}
