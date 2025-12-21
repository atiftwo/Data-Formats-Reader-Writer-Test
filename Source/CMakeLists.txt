add_executable(Application WIN32 "Application.cpp")

set(SDL3_IncludeDir "" CACHE STRING "SDL3 include directory")
target_include_directories(Application PRIVATE "${SDL3_IncludeDir}")

set(SDL3_LibraryPath "" CACHE STRING "Path to a SDL3 static library (either for shared or static)")
target_link_libraries(Application PRIVATE "${SDL3_LibraryPath}")

target_include_directories(Application PRIVATE "DataFormats")
add_subdirectory("DataFormats")