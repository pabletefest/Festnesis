set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(${PROJECT_NAME} main.cpp)

target_sources(${PROJECT_NAME} PRIVATE
  // CPU
  ${CMAKE_CURRENT_SOURCE_DIR}/cpu/m68000.cpp  
)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
