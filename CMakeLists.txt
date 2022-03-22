cmake_minimum_required(VERSION 3.0.0)
project(raytracer-tp VERSION 0.1.0)

include(CTest)
enable_testing()

add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories("${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE all_SRCS CONFIGURE_DEPENDS
        "${PROJECT_SOURCE_DIR}/src/*.hxx"
        "${PROJECT_SOURCE_DIR}/src/*.cc"
        "${PROJECT_SOURCE_DIR}/src/*.c"
        )

add_executable(raytracer-tp ${all_SRCS})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
