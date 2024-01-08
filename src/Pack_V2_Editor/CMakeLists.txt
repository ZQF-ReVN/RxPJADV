# Value Define
set(PROJECT_NAME Pack_V2_Editor)

# Cpp Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add Library
link_libraries(PJADV)

# Current Project
project("${PROJECT_NAME}")
add_executable(${PROJECT_NAME} "main.cpp")
