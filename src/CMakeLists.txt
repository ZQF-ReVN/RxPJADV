# RxValkyria
cmake_minimum_required(VERSION 3.25)

# Project Name
project(ReVN_RxPJADV)

# Export Symbols
if(BUILD_SHARED_LIBS)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# Set Source File Path
list(APPEND ReVN_RxPJADV_Core_Src_Files
    "src/ReVN/RxPJADV/Core/Pack_V2.cpp"
    "src/ReVN/RxPJADV/Core/Bin_TextData.cpp"
    "src/ReVN/RxPJADV/Core/Bin_Scenario.cpp"
    "src/ReVN/RxPJADV/Core/Bin_FileName.cpp"
    "src/ReVN/RxPJADV/Core/TextManager.cpp")

# Set Library
add_library(ReVN_RxPJADV_Core ${ReVN_RxPJADV_Core_Src_Files})
add_library(ReVN::RxPJADV::Core ALIAS ReVN_RxPJADV_Core)
target_include_directories(ReVN_RxPJADV_Core PUBLIC "src")
target_compile_features(ReVN_RxPJADV_Core PRIVATE cxx_std_23)
target_compile_options(ReVN_RxPJADV_Core PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
target_link_libraries(ReVN_RxPJADV_Core PRIVATE Zut::ZxFile Zut::ZxFS Zut::ZxCvt)
target_link_libraries(ReVN_RxPJADV_Core PUBLIC Zut::ZxMem Zut::ZxJson)

# Warning
if(MSVC)
    target_compile_options(ReVN_RxPJADV_Core PRIVATE /W4)
else()
    target_compile_options(ReVN_RxPJADV_Core PRIVATE -Wall -Wextra)
endif()

