#include <cstdio>
extern "C" {
    #include <lua/lua.h>
    #include <lua/lualib.h>
    #include <lua/lauxlib.h>
}

int main() {
    lua_State* state = luaL_newstate();
    luaL_openlibs(state); {
        // some code
    }
    lua_close(state);
    return 0;
}