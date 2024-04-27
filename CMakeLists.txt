cmake_minimum_required(VERSION 3.5)

project(custom_list_cpp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)
enable_testing()

set(
    SOURCE_FILES
    src/main.cxx
)

set(
    HEADER_FILES
    include/dependencies.hxx
)

set(
    EXECUTABLE_NAME
    custom_list_executable
)

add_executable(
    ${EXECUTABLE_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
