cmake_minimum_required(VERSION 3.9)
project(picasso LANGUAGES CXX)

set(ENV{VULKAN_SDK} "Lib/Linux/Vulkan")

set(CMAKE_BUILD_TYPE Debug)



IF(CMAKE_BUILD_TYPE MATCHES Debug)
  message("Debug build.")
  add_compile_options(-fsanitize=address)
  add_link_options(-fsanitize=address)
ELSE()
  message("Release build")
ENDIF()


add_subdirectory(PEngine)
include_directories(PEngine)



file(GLOB SRC_FILES *.cpp)
add_executable(PRunner ${SRC_FILES})

target_link_options(PEngine PRIVATE -Wl,-z,defs)

target_link_libraries(PRunner PEngine) 
    

