# Library Name
set(USER_PROJECT_NAME PJADV)

# Cpp Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add Library
link_libraries(Rut)

# Set Source File Path
list(APPEND SRC_FILE 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Pack_V2.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Bin_Scenario.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Bin_TextData.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Bin_FileName.cpp")

# Set Library
add_library(${USER_PROJECT_NAME} "${SRC_FILE}")
