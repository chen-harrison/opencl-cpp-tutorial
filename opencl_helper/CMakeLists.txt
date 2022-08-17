project(opencl_helper_lib)

file(GLOB ALLSOURCES "src/*.cpp")

add_library(${PROJECT_NAME} STATIC ${ALLSOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${OPENCL_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
    ${OPENCL_LIBRARIES})