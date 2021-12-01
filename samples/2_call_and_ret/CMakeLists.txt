add_executable(call_and_ret)

target_sources(call_and_ret
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(call_and_ret
PRIVATE
    lua
)