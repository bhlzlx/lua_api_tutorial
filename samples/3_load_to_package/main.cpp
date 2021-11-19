#include <cstdio>
#include <cstring>
#include <cassert>
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

char const* script_1 = R"(
    pkg.helloworld()
)";
/*
_G = {
    "helloworld" = function print("hello,world")
}
_G = {
    "pgk" = {
        metatable = {
            "__index" = _G
        }
        "helloworld" = function print("hello,world")
    }
}
```lua
pkg.helloworld()
```
*/
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
        // call the code chunk
        lua_getglobal(state, "_G");
        if(lua_istable(state, -1)) { // chunk; _G 
            lua_newtable(state);     // chunk;_G ; new_table
            lua_pushstring(state, "pkg"); //chunk;_G; new_table; "pkg";
            lua_pushvalue(state, -2); //chunk; _G; new_table; "pkg"; new_table
            lua_rawset(state, -4); // chunk;_G; new_table;
            char const* upvalueName = lua_setupvalue(state, -3, 1); // chunk; _G
            assert(strcmp(upvalueName, "_ENV") == 0 && "upvalue name must be '_ENV'");
            lua_newtable(state); // chunk; _G; metatable
            lua_pushstring(state, "__index"); // chunk; _G; metatable; "__index";
            lua_pushvalue(state, -3); // chunk; _G; metatable; "__index"; _G
            lua_rawset(state, -3); // chunk; _G; metatable
            lua_pushstring(state, "pkg"); // chunk; _G; metatable; "pkg"(string)
            lua_rawget(state, -3); // chunk; _G; metatable; "pkg"(table)
            lua_pushvalue(state, -2); // chunk; _G; metatable; "pkg"(table); metatable;
            lua_setmetatable(state, -2); // chunk; _G; metatable;"pkg"(table);
            lua_pop(state, 3); // chunk
            // lua_pop(state, 1);
        } // chunk
        // 执行chunk
        if(lua_pcall(state, 0, 0, 0)) {
            if(lua_isstring(state, -1)) {
                auto msg = lua_tostring(state, -1);
                printf("call function chunk failed : %s\n", msg);
                lua_pop(state, 1);
            }
        }
        // 加载 script_1
        rst = luaL_loadbuffer( state, script_1, strlen(script_1), "script_1");
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