
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(Lightbox main.cpp )
target_link_libraries(Lightbox ${OpenCV_LIBS})