# Main CMakeLists
cmake_minimum_required(VERSION 3.12)

# Project Name
project(PJADV_Tools)

# Tool Chain
set(CMAKE_TOOLCHAIN_FILE "toolchain.cmake")

# MSVC Setting
if(MSVC)
    add_compile_options("$<$<CONFIG:Release>:/source-charset:utf-8>;$<$<CONFIG:Release>:/GL>;$<$<CONFIG:Release>:/Gy>;$<$<CONFIG:Release>:/GS>;$<$<CONFIG:Release>:/Zc:inline>;$<$<CONFIG:Release>:/Zc:forScope>")
    add_link_options("$<$<CONFIG:Release>:/LTCG:INCREMENTAL>;$<$<CONFIG:Release>:/OPT:REF>")
    add_definitions(-DUNICODE -D_UNICODE)
endif()

# Value Define
set(LIB_DIR "${CMAKE_CURRENT_LIST_DIR}/lib")
set(THIRD_DIR "${CMAKE_CURRENT_LIST_DIR}/third")

# Out Path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/.out/exe)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_LIST_DIR}/.out/lib)

# Library
    add_subdirectory("lib/Rut")
    add_subdirectory("lib/PJADV")

# Project
    add_subdirectory("src/Pack_V2_Editor")
    add_subdirectory("src/TextDataDat_Cryptor")
    add_subdirectory("src/Text_Editor")

# Test
    add_subdirectory("test/FileNameDat_Test")
    add_subdirectory("test/ScenarioDat_Test")
    add_subdirectory("test/TextDataDat_Test")