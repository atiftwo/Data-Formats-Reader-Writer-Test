add_executable(SimpleViewer WIN32 "Main.cpp")

set(SDL3_IncludeDir "" CACHE STRING "SDL3 include directory")
target_include_directories(SimpleViewer PRIVATE "${SDL3_IncludeDir}")

set(SDL3_LibraryPath "" CACHE STRING "Path to a SDL3 static library (either for shared or static)")
target_link_libraries(SimpleViewer PRIVATE "${SDL3_LibraryPath}")