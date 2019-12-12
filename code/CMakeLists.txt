# include root directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR})



# static library
add_subdirectory(common)

# main project
add_subdirectory(client)
