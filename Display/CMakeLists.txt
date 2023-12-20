add_library(Display)

include_directories( ${OpenCV_INCLUDE_DIRS} )

target_sources(Display
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
    Display.cpp
)

target_link_libraries(Display PRIVATE ${OpenCV_LIBS})