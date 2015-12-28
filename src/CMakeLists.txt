

file(GLOB SOURCES "engine/*.cpp" "engine/data_structs/*.cpp" "app/*.cpp")
add_library(Engine ${SOURCES})

add_custom_target(
    generateBinds
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND ruby scripts/generate_binds.rb
)
add_dependencies(Engine generateBinds)


target_include_directories (Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
