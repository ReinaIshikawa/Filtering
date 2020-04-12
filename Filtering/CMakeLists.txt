cmake_minimum_required(VERSION 3.13)

project(SpacialFiltering)
add_executable(SpacialFiltering filtering.cpp filters.h)

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT "SpacialFiltering")

set(CMAKE_CXX_STANDARD 14)

include_directories(
${PROJECT_SOURCE_DIR}
)

# For OpenCV
find_package(OpenCV 3.4 REQUIRED)

if(OpenCV_FOUND)
  include_directories(${OpenCV_INCLUDE_DIRS})
  message(${OpenCV_INCLUDE_DIRS})
  target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
endif(OpenCV_FOUND)

add_executable(EdgeDetection edge.cpp)
target_link_libraries(EdgeDetection ${OpenCV_LIBS})

add_executable(Labeling labeling.cpp)
target_link_libraries(Labeling ${OpenCV_LIBS})

add_executable(DilateErode DilateErode.cpp)
target_link_libraries(DilateErode ${OpenCV_LIBS})
