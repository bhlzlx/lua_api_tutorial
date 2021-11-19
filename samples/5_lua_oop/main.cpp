#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdint>
extern "C" {
    #include <lua/lua.h>
    #include <lua/lualib.h>
    #include <lua/lauxlib.h>
}

char const* script = R"(
)";

class GameObject {
private:
    uint32_t _id;
public:
    GameObject(uint32_t id)
        : _id(id)
    {}
    uint32_t id() const {
        return _id;
    }
    bool equal( GameObject* obj ) {
        return _id == obj->_id;
    }
};

int main() {
    lua_State* state = luaL_newstate();
    luaL_openlibs(state); 
    {
        auto rst = luaL_loadbuffer( state, script, strlen(script), "oop");
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