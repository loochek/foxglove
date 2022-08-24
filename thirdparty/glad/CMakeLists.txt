aux_source_directory(src/ GLAD_SOURCES)
add_library(glad STATIC ${GLAD_SOURCES})
target_include_directories(glad PUBLIC include/)
