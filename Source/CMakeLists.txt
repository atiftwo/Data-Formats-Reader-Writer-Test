add_executable(Application "Application.cpp")
target_include_directories(Application PRIVATE "DataFormats")
add_subdirectory("DataFormats")