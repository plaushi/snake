cmake_minimum_required(VERSION 3.0.0)
project(snake VERSION 0.1.0)

find_package(OpenCV REQUIRED PATHS C:/opencv/build)
include_directories(( ${OpenCV_INCLUDE_DIRS}))


file(GLOB_RECURSE SRC "*.cpp" "*.h")

add_executable(snake ${SRC}
			   )

target_link_libraries(snake ${OpenCV_LIBS} winmm.lib)

 set_property(TARGET snake PROPERTY CXX_STANDARD 11)