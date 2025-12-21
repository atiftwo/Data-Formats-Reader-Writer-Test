cmake_minimum_required(VERSION 4.2)

project("Data-Formats-Reader-Writer-Test")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

include("CMake/Settings.cmake")

set(FMT_IncludeDir "" CACHE STRING "FMT include directory")
include_directories(Application PUBLIC "${FMT_IncludeDir}")

set(FMT_LibraryPath "" CACHE STRING "Path to a FMT static library (either for shared or static)")
link_libraries("${FMT_LibraryPath}")

add_subdirectory("Source")