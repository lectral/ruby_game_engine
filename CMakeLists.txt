cmake_minimum_required(VERSION 3.0.2)
project (hello)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(TARGET_BINARY hack_game)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")




find_package(Mruby REQUIRED)
find_package(YamlCpp REQUIRED)
find_package(SFML 2.3 REQUIRED system window graphics audio)
find_package(Thor REQUIRED)

#find_package(Boost)

include_directories(${MRUBY_INCLUDE_DIR} ${SFML_INCLUDE_DIR} ${YAMLCPP_INCLUDE_DIR} ${THOR_INCLUDE_DIR})

set(ALL_LIBS ${LIBS} ${MRUBY_LIBRARIES} ${SFML_LIBRARIES} ${YAMLCPP_LIBRARY} ${THOR_LIBRARY})

include_directories(include)
include_directories(src)

add_subdirectory(src)
add_subdirectory(tests)


include(add_catch_tests)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable(${TARGET_BINARY} ${PROJECT_SOURCE_DIR}/src/main.cpp)

target_link_libraries(${TARGET_BINARY} ${ALL_LIBS} Engine)
enable_testing()
add_test(NAME "catch_tests" COMMAND catch_tests)