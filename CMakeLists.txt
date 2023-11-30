cmake_minimum_required(VERSION 3.9)
project(picasso LANGUAGES CXX)

set(CMAKE_BUILD_TYPE Debug)

IF(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Debug build.")
  ELSE()
  message("Release build")
ENDIF()


add_subdirectory(Engine)
include_directories(Engine)


file(GLOB SRC_FILES *.cpp)
add_executable(PRunner ${SRC_FILES})

target_link_options(Engine PRIVATE -Wl,-z,defs)

target_link_libraries(PRunner Engine) 
    

