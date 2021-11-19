#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdint>
#include <cmath>
extern "C" {
    #include <lua/lua.h>
    #include <lua/lualib.h>
    #include <lua/lauxlib.h>
}

char const* script = R"(
    local val = pow_from_c(2,5)
    print(""..val)
)";

int __cdecl pow_from_c(lua_State* state) {
    int param_count = lua_gettop(state);
    if(param_count != 2) {
        return 0;
    }
    if(lua_isinteger(state, 1) && lua_isinteger(state, 2)) {
        auto x = lua_tointeger(state, 1);
        auto y = lua_tointeger(state, 2);
        int rst = (int)pow(x, y);
        lua_pushinteger(state, rst);
        return 1;
    }
    return 0;
}

/**
 * 
 * _G = {
 *     "pow_from_c" = pow_from_c;
 * }
 * */

int main() {
    lua_State* state = luaL_newstate();
    luaL_openlibs(state); 
    {
        lua_getglobal(state, "_G");
        lua_pushstring(state, "pow_from_c");
        lua_pushcclosure(state, pow_from_c, 0); // _G; "pow_from_c"; closure
        lua_rawset(state, -3); // _G
        lua_pop(state, 1); 
        //
        auto rst = luaL_loadbuffer( state, script, strlen(script), "reg_c_closure");
        if(rst != 0) {
            if(lua_isstring(state, -1)) {
                auto msg = lua_tostring(state, -1);
                printf("load script failed : %s\n", msg);
                lua_pop(state, 1);
            }
            return -1;
        }
        // 执行chunk
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