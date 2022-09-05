aux_source_directory(. FOXGLOVE_SOURCES)
aux_source_directory(utils FOXGLOVE_SOURCES)
aux_source_directory(core FOXGLOVE_SOURCES)
aux_source_directory(math FOXGLOVE_SOURCES)
aux_source_directory(renderer FOXGLOVE_SOURCES)
aux_source_directory(ecs FOXGLOVE_SOURCES)
aux_source_directory(asset FOXGLOVE_SOURCES)
aux_source_directory(asset/handlers FOXGLOVE_SOURCES)

add_library(foxglove ${FOXGLOVE_SOURCES})
target_link_libraries(foxglove ${OPENGL_LIBRARIES} glfw glad stb fmt::fmt json)

target_include_directories(foxglove PUBLIC ./)
target_include_directories(foxglove PRIVATE "$<TARGET_PROPERTY:model_importer,INTERFACE_INCLUDE_DIRECTORIES>")