#include <cstdio>
#include <cstring>
extern "C" {
    #include <lua/lua.h>
    #include <lua/lualib.h>
    #include <lua/lauxlib.h>
}

char const* script = R"(
function helloworld()
    print('hello,world!')
end
helloworld()
)";

int main() {
    lua_State* state = luaL_newstate();
    luaL_openlibs(state); {
        auto rst = luaL_loadbuffer( state, script, strlen(script), "helloworld");
        if(rst != 0) {
            if(lua_isstring(state, -1)) {
                auto msg = lua_tostring(state, -1);
                printf("load script failed : %s\n", msg);
                lua_pop(state, 1);
            }
            return -1;
        }
        if(lua_pcall(state, 0, 0, 0)) {
            if(lua_isstring(state, -1)) {
                auto msg = lua_tostring(state, -1);
                printf("call function chunk failed : %s\n", msg);
                lua_pop(state, 1);
            }
        }
    }
    lua_close(state);
    return 0;
}