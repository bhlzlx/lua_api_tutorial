add_executable(lua_oop)

target_sources(lua_oop
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(lua_oop
PRIVATE
    lua
)