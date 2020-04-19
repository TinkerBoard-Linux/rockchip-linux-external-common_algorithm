#1.cmake version
cmake_minimum_required(VERSION 3.2)

#2.project name
project(AEC)

# ----------------------------------------------------------------------------
#  install headers
# ----------------------------------------------------------------------------
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
	DESTINATION "include"
	FILES_MATCHING PATTERN "*.h"
)

# ----------------------------------------------------------------------------
#  install libs
# ----------------------------------------------------------------------------
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/libRKAP_AEC.so
	DESTINATION "lib"
)

add_subdirectory(test)
