cmake_minimum_required(VERSION 3.24)
project( Lightbox )

set(EXPORT_COMPILE_COMMANDS ON)

if(MSVC)

set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/../Dependencies/opencv/build")

add_compile_options(
    # Always generate pdb's
    /Zi
    # Always disable Frame-Pointer Omission.
    /Oy-
    # Enable the compiler warns when the initialization order isn't the same as the declaration order of data members or base classes.
    /w15038 
    # - SCL_SECURE_NO_WARNINGS, CRT_SECURE_NO_DEPRECATE squash warnings and errors that result from the
#   usage of certain "unsafe" functions from STL or the C library.
    /wd4996 
    /W4 
    /bigobj
    # Enable C++20.
    /std:c++20
    # Force warning as errors 
    # WX Treat warnings as errors.
    /WX
)
else()
set(CMAKE_CXX_STANDARD 20)
endif()

# include OpenCV
find_package(OpenCV 4 REQUIRED)


add_subdirectory(Lightbox)
