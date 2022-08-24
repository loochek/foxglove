aux_source_directory(src/ STB_SOURCES)
add_library(stb STATIC ${STB_SOURCES})
target_include_directories(stb PUBLIC include/)
