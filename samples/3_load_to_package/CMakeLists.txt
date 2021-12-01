add_executable(load_to_package)

target_sources(load_to_package
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(load_to_package
PRIVATE
    lua
)