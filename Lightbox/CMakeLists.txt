
include_directories( ${OpenCV_INCLUDE_DIRS} )

set(SOURCE
  main.cpp
)

set(HEADERS
)

add_executable(Lightbox ${SOURCE} ${HEADERS} )
target_link_libraries(Lightbox PRIVATE ${OpenCV_LIBS} DisplayManager)