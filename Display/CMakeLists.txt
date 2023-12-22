add_library(DisplayManager)

include_directories( ${OpenCV_INCLUDE_DIRS} )

target_sources(DisplayManager
  PUBLIC
    FILE_SET CXX_MODULES FILES
    DisplayManager.cpp
)

target_link_libraries(DisplayManager PRIVATE ${OpenCV_LIBS})