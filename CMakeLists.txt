CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(ColorCategorizer)

file(GLOB sources "src/*.cpp")

add_executable(ColorCategorizer ${sources})

target_include_directories(ColorCategorizer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
