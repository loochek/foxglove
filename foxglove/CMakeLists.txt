aux_source_directory(. FOXGLOVE_SOURCES)
aux_source_directory(core FOXGLOVE_SOURCES)
aux_source_directory(math FOXGLOVE_SOURCES)
aux_source_directory(renderer FOXGLOVE_SOURCES)
aux_source_directory(ecs FOXGLOVE_SOURCES)
aux_source_directory(asset FOXGLOVE_SOURCES)
aux_source_directory(asset/handlers FOXGLOVE_SOURCES)

add_executable(foxglove ${FOXGLOVE_SOURCES} asset/handlers/shader_asset_handler.cpp asset/handlers/shader_asset_handler.hpp asset/handlers/material_handler.cpp asset/handlers/material_handler.hpp)
target_link_libraries(foxglove ${OPENGL_LIBRARIES} glfw glad stb fmt::fmt json)

target_include_directories(foxglove PRIVATE ./)
