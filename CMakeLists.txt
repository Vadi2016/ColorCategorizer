CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
	 
PROJECT(ColorCategorizer)

set(CMAKE_CXX_FLAGS "-std=c++14")

file(GLOB sources "src/*.cpp")

add_executable(ColorCategorizer ${sources})

target_include_directories(ColorCategorizer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
