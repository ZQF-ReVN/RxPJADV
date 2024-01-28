# Main CMakeLists
cmake_minimum_required(VERSION 3.15)

# Project Name
project(PJADV_Tools)

# option
set(STATIC_MSVC_RUNTIME ON)

# MSVC Setting
if(MSVC)
    # Macro
    add_definitions(-DUNICODE -D_UNICODE)

    # Runtime
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        if (STATIC_MSVC_RUNTIME)
            set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDebug)
        else()
            set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDebugDLL)
        endif()
    else()
        if (STATIC_MSVC_RUNTIME)
            set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded)
        else()
            set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
        endif()
    endif()

    # Compiler
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        #set(CMAKE_CXX_FLAGS_DEBUG)
    else()
        add_link_options(/LTCG:INCREMENTAL /OPT:REF)
        set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /source-charset:utf-8 /GL /Gy /GS /Zc:inline /Zc:forScope")
        #set(CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        #set(CMAKE_CXX_FLAGS_MINSIZEREL)
    endif()
endif()

# Value Define
set(ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(LIB_DIR "${ROOT_DIR}/lib")
set(THIRD_DIR "${ROOT_DIR}/third")

# Out Path
if (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(EXECUTABLE_OUTPUT_PATH "${ROOT_DIR}/.bin/x32")
    set(LIBRARY_OUTPUT_PATH "${ROOT_DIR}/.bin/x32")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(EXECUTABLE_OUTPUT_PATH "${ROOT_DIR}/.bin/x64")
    set(LIBRARY_OUTPUT_PATH "${ROOT_DIR}/.bin/x64")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/debug")
    set(LIBRARY_OUTPUT_PATH "${LIBRARY_OUTPUT_PATH}/debug")
else()
    set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/release")
    set(LIBRARY_OUTPUT_PATH "${LIBRARY_OUTPUT_PATH}/release")
endif()

# Library
    include_directories("${ROOT_DIR}")
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