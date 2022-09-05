aux_source_directory(. TESTAPP_SOURCES)

add_executable(testapp ${TESTAPP_SOURCES})
target_link_libraries(testapp foxglove)

target_include_directories(testapp PRIVATE ./)