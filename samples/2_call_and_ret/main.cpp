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
function my_pow(x,y)
    return x^y
end
)";

int main() {
    lua_State* state = luaL_newstate();
    luaL_openlibs(state); 
    {
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
        // call my_pow
        rst = lua_getglobal(state, "my_pow");
        if(!lua_isfunction(state, -1)) {
            printf("function named 'my_pow' not found!\n");
            return -1;
        }
        lua_pushnumber(state, 2);
        lua_pushnumber(state, 8);

        rst = lua_pcall(state, 2, 1, 0);
        if(rst != 0) {
            if(lua_isstring(state, -1)) {
                auto msg = lua_tostring(state, -1);
                printf("call function chunk failed : %s\n", msg);
                lua_pop(state, 1);
            }
        }
        if(lua_isnumber(state, -1)) {
            lua_Number val = lua_tonumber(state, -1);
            printf("my_pow ret : %f", (float)val);
        }
    }
    lua_close(state);
    return 0;
}