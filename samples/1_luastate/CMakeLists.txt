add_executable(lua_state)

target_sources(lua_state
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(lua_state
PRIVATE
    lua
)