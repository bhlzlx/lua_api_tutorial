add_executable(reg_c_closure)

target_sources(reg_c_closure
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(reg_c_closure
PRIVATE
    lua
)