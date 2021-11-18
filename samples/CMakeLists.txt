project(3rd)

add_library( lua STATIC )
target_sources(lua
PRIVATE 
    ${TUTORIAL_ROOT}/3rd/lua/lapi.c
    ${TUTORIAL_ROOT}/3rd/lua/lauxlib.c
    ${TUTORIAL_ROOT}/3rd/lua/lbaselib.c
    ${TUTORIAL_ROOT}/3rd/lua/lcode.c
    ${TUTORIAL_ROOT}/3rd/lua/lcorolib.c
    ${TUTORIAL_ROOT}/3rd/lua/lctype.c
    ${TUTORIAL_ROOT}/3rd/lua/ldblib.c
    ${TUTORIAL_ROOT}/3rd/lua/ldebug.c
    ${TUTORIAL_ROOT}/3rd/lua/ldo.c
    ${TUTORIAL_ROOT}/3rd/lua/ldump.c
    ${TUTORIAL_ROOT}/3rd/lua/lfunc.c
    ${TUTORIAL_ROOT}/3rd/lua/lgc.c
    ${TUTORIAL_ROOT}/3rd/lua/linit.c
    ${TUTORIAL_ROOT}/3rd/lua/liolib.c
    ${TUTORIAL_ROOT}/3rd/lua/llex.c
    ${TUTORIAL_ROOT}/3rd/lua/lmathlib.c
    ${TUTORIAL_ROOT}/3rd/lua/lmem.c
    ${TUTORIAL_ROOT}/3rd/lua/loadlib.c
    ${TUTORIAL_ROOT}/3rd/lua/lobject.c
    ${TUTORIAL_ROOT}/3rd/lua/lopcodes.c
    ${TUTORIAL_ROOT}/3rd/lua/loslib.c
    ${TUTORIAL_ROOT}/3rd/lua/lparser.c
    ${TUTORIAL_ROOT}/3rd/lua/lstate.c
    ${TUTORIAL_ROOT}/3rd/lua/lstring.c
    ${TUTORIAL_ROOT}/3rd/lua/lstrlib.c
    ${TUTORIAL_ROOT}/3rd/lua/ltable.c
    ${TUTORIAL_ROOT}/3rd/lua/ltablib.c
    ${TUTORIAL_ROOT}/3rd/lua/ltablib.c
    ${TUTORIAL_ROOT}/3rd/lua/lua.c
    ${TUTORIAL_ROOT}/3rd/lua/ltm.c
    ${TUTORIAL_ROOT}/3rd/lua/lundump.c
    ${TUTORIAL_ROOT}/3rd/lua/lutf8lib.c
    ${TUTORIAL_ROOT}/3rd/lua/lvm.c
    ${TUTORIAL_ROOT}/3rd/lua/lzio.c
)

target_include_directories(lua
INTERFACE
    ${TUTORIAL_ROOT}/3rd
)

project(samples)

add_subdirectory(0_luastate)
add_subdirectory(1_loadscript)
add_subdirectory(2_call_and_ret)