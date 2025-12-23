target_sources(SimpleViewer PRIVATE "BMPFile/BMPFile.cpp")
target_sources(SimpleViewer PRIVATE "JPEGFile/JPEGFile.cpp")

target_include_directories(SimpleViewer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")