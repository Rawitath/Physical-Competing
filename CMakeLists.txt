cmake_minimum_required(VERSION 3.16)
project(phycompet LANGUAGES C VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>") #set runtime location
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>") #put dll in runtime location
set(RESOURCE_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res)

add_subdirectory(lib/SDL EXCLUDE_FROM_ALL)

set(SDLIMAGE_VENDORED ON) # THIS ONE IS VERY IMPORTANT
set(SDLIMAGE_AVIF OFF)	# disable formats we don't use to make the build faster and smaller.
set(SDLIMAGE_BMP OFF)
set(SDLIMAGE_WEBP OFF)
set(SDLIMAGE_TIF OFF)
add_subdirectory(lib/SDL_image EXCLUDE_FROM_ALL)

set(SDLTTF_VENDORED ON) # THIS ONE(1) IS VERY IMPORTANT
add_subdirectory(lib/SDL_ttf EXCLUDE_FROM_ALL)

file(GLOB_RECURSE phycompet_src CONFIGURE_DEPENDS "src/*.h" "src/*.c")

#create runtime
add_executable(phycompet ${phycompet_src})

#link libraries
target_link_libraries(phycompet PRIVATE SDL3::SDL3 SDL3_image::SDL3_image SDL3_ttf::SDL3_ttf)

# add_custom_target(delete_resources
#     COMMAND ${CMAKE_COMMAND} -E remove_directory ${RESOURCE_DIR}
# )

# add_custom_target(TARGET phycompet POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
#         ${CMAKE_SOURCE_DIR}/res
#         ${RESOURCE_DIR}
# )


### Uncomment to enable sync ###
# set(SYNC_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sync_res.cmake")

# # Add the custom command to run POST_BUILD
# add_custom_command(
#     TARGET phycompet POST_BUILD
    
#     # This is the command that will run
#     COMMAND ${CMAKE_COMMAND}
#         -DSOURCE_DIR=${CMAKE_SOURCE_DIR}/res
#         -DDEST_DIR=${RESOURCE_DIR}
#         -P ${SYNC_SCRIPT}
        
#     COMMENT "Syncing 'res' folder (with delete)..."
#     VERBATIM  # Important for correct path handling
# )

