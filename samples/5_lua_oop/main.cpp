#include <cstdio>
#include <cstring>
#include <cassert>
#include <cstdint>
#include <new>
extern "C" {
    #include <lua/lua.h>
    #include <lua/lualib.h>
    #include <lua/lauxlib.h>
}

char const* script = R"(
    local obj_1 = create_game_object(1);
    local obj_2 = create_game_object(1);
    local obj_3 = create_game_object(2);
    local rst1 = obj_1:equal(obj_2)
    local rst2 = obj_1:equal(obj_3)
    print(rst1,";",rst2)
    print(""..obj_1:id())
)";
class GameObject {
private:
    uint32_t _id;
public:
    static size_t registry_value;
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

size_t GameObject::registry_value = 0;
/**
 * userdata : {
 *      metatable : {
 *          __index = {
    *          equal = function() {},
    *          id = function() {}
*           }
 *      }
 * }
 * */

int GameObject_equal( lua_State* state ) {
    int arg_count = lua_gettop(state);
    if(arg_count != 2) {
        return 0;
    }
    if(lua_isuserdata(state, 1) && lua_isuserdata(state, 2)) {
        void* userdata_self = lua_touserdata(state, 1);
        void* userdata_that = lua_touserdata(state, 2);
        GameObject* obj1 = (GameObject*)userdata_self;
        GameObject* obj2 = (GameObject*)userdata_that;
        auto rst = obj1->equal(obj2);
        lua_pushboolean(state, rst);
        return 1;
    }
    return 0;
}

int GameObject_id(lua_State* state) {
    GameObject* this_obj = (GameObject*)lua_touserdata(state, 1);
    auto rst = this_obj->id();
    lua_pushinteger(state, rst);
    return 1;
}

int create_game_object(lua_State* state) {
    auto id = lua_tointeger(state, 1);
    void* p = lua_newuserdata(state, sizeof(GameObject));
    // placement new
    GameObject* obj = new(p)GameObject(id); // userdata
    lua_rawgetp(state, LUA_REGISTRYINDEX, &GameObject::registry_value); // userdata; metatable
    lua_setmetatable(state, -2); // userdata
    return 1;
}

int main() {
    lua_State* state = luaL_newstate();
    luaL_openlibs(state); 
    {
        // Regist create_object to lua
        lua_getglobal(state, "_G");
        lua_pushstring(state, "create_game_object");
        lua_pushcclosure(state, create_game_object, 0);
        lua_rawset(state, -3); // _G
        lua_pop(state, 1); 
        // reg GameObject metatable
        lua_newtable(state);    // metatable
        lua_pushstring(state, "__index"); // metatable; "__index"
        lua_newtable(state); // metatable, "__index", index_table
        lua_pushstring(state,"equal"); // metatable, "__index", index_table, "equal"
        lua_pushcclosure(state, GameObject_equal, 0); // metatable, "__index", index_table, "equal", GameObject_equal
        lua_rawset(state, -3);// metatable, "__index", index_table 
        lua_pushstring(state,"id"); // metatable, "__index", index_table, "equal"
        lua_pushcclosure(state, GameObject_id, 0); // metatable, "__index", index_table, "equal", GameObject_equal
        lua_rawset(state, -3);// metatable, "__index", index_table 
        //
        lua_rawset(state, -3); // metatable
        lua_rawsetp(state, LUA_REGISTRYINDEX, &GameObject::registry_value);
        //
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