cmake_minimum_required(VERSION 3.11.0)
if(WIN32)
    # compiler names may vary depending on installation
    set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc.exe)
    set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++.exe)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static-libgcc")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
    set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_C_FLAGS} -static-libgcc -s")
    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -static-libgcc -static-libstdc++ -s")
endif()
set(CMAKE_CXX_STANDARD 11)
if(DEBUG)
    add_compile_options(-g)
    project(debug__opencv_webcam_test)
else()
    project(opencv_webcam_test)
endif()

include_directories(${PROJECT_SOURCE_DIR}/opencv/include ${PROJECT_SOURCE_DIR}/src)

# getting all *cpp files
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
# building an executable
add_executable(${PROJECT_NAME} ${SOURCES})
# linking a combined library
target_link_libraries(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/opencv/libs/libopencv_world4100.dll.a)