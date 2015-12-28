add_executable (catch_tests catch.cpp sound_engine_tests.cpp strings_manager_tests.cpp input_engine_tests.cpp graphics_engine_tests.cpp drawable_tests.cpp animation_tests.cpp)
target_link_libraries(catch_tests ${ALL_LIBS} Engine)
