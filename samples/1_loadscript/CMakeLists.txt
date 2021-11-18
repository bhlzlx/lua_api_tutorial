add_executable(load_script)

target_sources(load_script
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(load_script
PRIVATE
    lua
)