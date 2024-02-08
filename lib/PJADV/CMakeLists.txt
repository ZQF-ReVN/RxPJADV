# Project
project(PJADV)

# Source File
list(APPEND "${PROJECT_NAME}_SRC_FILE" 
    "src/PJADV/Pack_V2.cpp"
    "src/PJADV/Bin_Scenario.cpp"
    "src/PJADV/Bin_TextData.cpp"
    "src/PJADV/Bin_FileName.cpp")

# Set Library
add_library("${PROJECT_NAME}" "${${PROJECT_NAME}_SRC_FILE}")
target_include_directories("${PROJECT_NAME}" INTERFACE "src")
target_compile_features("${PROJECT_NAME}" PRIVATE cxx_std_23)
target_compile_options("${PROJECT_NAME}" PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

# Add Library
target_link_libraries("${PROJECT_NAME}" PRIVATE Rut)