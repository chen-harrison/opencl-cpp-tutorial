cmake_minimum_required(VERSION 3.10)

project(opencl_tutorial)

find_package(OpenCL REQUIRED)

add_subdirectory(opencl_helper)

add_executable(test test.cpp)
target_include_directories(test PUBLIC
    ${OpenCL_INCLUDE_DIRS})
target_link_libraries(test
    ${OpenCL_LIBRARIES})

add_executable(hello_world hello_world.cpp)
target_include_directories(hello_world PUBLIC
    ${OpenCL_INCLUDE_DIRS})
target_link_libraries(hello_world
    ${OpenCL_LIBRARIES}
    opencl_helper_lib)

add_executable(process_array process_array.cpp)
target_include_directories(process_array PUBLIC
    ${OpenCL_INCLUDE_DIRS})
target_link_libraries(process_array
    ${OpenCL_LIBRARIES}
    opencl_helper_lib)