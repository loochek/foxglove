aux_source_directory(. MODEL_IMPORTER_SOURCES)

add_executable(model_importer ${MODEL_IMPORTER_SOURCES})
target_link_libraries(model_importer assimp fmt::fmt json)

target_include_directories(model_importer PUBLIC ./)
target_include_directories(model_importer PRIVATE "$<TARGET_PROPERTY:foxglove,INTERFACE_INCLUDE_DIRECTORIES>")
