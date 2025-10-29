# sync_res.cmake
#
# This script performs a one-way sync from SOURCE_DIR to DEST_DIR,
# deleting any files in DEST_DIR that do not exist in SOURCE_DIR.
#
# It is called with:
#   cmake -DSOURCE_DIR=... -DDEST_DIR=... -P sync_res.cmake

if(NOT SOURCE_DIR OR NOT DEST_DIR)
    message(FATAL_ERROR "SOURCE_DIR and DEST_DIR must be defined.")
endif()

message(STATUS "Syncing: ${SOURCE_DIR}")
message(STATUS "     to: ${DEST_DIR}")

# 1. Get a relative list of all files in the source directory
file(GLOB_RECURSE SOURCE_FILES
    RELATIVE "${SOURCE_DIR}"
    "${SOURCE_DIR}/*"
)

# 2. Get a relative list of all files in the destination directory
#    (Create it if it doesn't exist)
if(NOT EXISTS "${DEST_DIR}")
    file(MAKE_DIRECTORY "${DEST_DIR}")
endif()

file(GLOB_RECURSE DEST_FILES
    RELATIVE "${DEST_DIR}"
    "${DEST_DIR}/*"
)

# 3. Copy/Update all files from source to destination
foreach(SRC_FILE ${SOURCE_FILES})
    set(SRC_PATH "${SOURCE_DIR}/${SRC_FILE}")
    set(DEST_PATH "${DEST_DIR}/${SRC_FILE}")

    # Ensure the subdirectory exists in the destination
    get_filename_component(DEST_SUBDIR ${DEST_PATH} DIRECTORY)
    file(MAKE_DIRECTORY "${DEST_SUBDIR}")
    
    # This only copies if the source is newer
    file(COPY ${SRC_PATH} DESTINATION ${DEST_SUBDIR})
endforeach()


# 4. Find all files in destination that are NOT in source
set(FILES_TO_DELETE "")
foreach(DEST_FILE ${DEST_FILES})
    # Check if this destination file exists in the source list
    list(FIND SOURCE_FILES "${DEST_FILE}" IS_IN_SOURCE)
    
    if(IS_IN_SOURCE EQUAL -1)
        # Not found. Add its full path to the delete list.
        list(APPEND FILES_TO_DELETE "${DEST_DIR}/${DEST_FILE}")
    endif()
endforeach()

# 5. Delete the extraneous files
if(FILES_TO_DELETE)
    message(STATUS "Removing ${FILES_TO_DELETE}")
    file(REMOVE ${FILES_TO_DELETE})
endif()