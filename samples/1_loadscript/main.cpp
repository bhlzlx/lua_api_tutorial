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
        int rst = luaL_loadbuffer(state, script, strlen(script), "helloworld");
        if(rst != 0) {
            char const* msg = lua_tostring(state, -1);
            printf("load buffer error: %s\n", msg);
        }
        lua_call(state, 0, 0);
    }
    lua_close(state);
    return 0;
}