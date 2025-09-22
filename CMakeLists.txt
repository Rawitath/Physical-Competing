cmake_minimum_required(VERSION 3.16)
project(phycompet LANGUAGES C VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>") #set runtime location
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>") #put dll in runtime location

add_subdirectory(lib/SDL EXCLUDE_FROM_ALL)

file(GLOB phycompet_src CONFIGURE_DEPENDS "src/*.h" "src/*.c")

#create runtime
add_executable(phycompet ${phycompet_src})

#link libraries
target_link_libraries(phycompet PRIVATE SDL3::SDL3)
