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

# ----------------------------------------------------------------------------
#  install data
# ----------------------------------------------------------------------------
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/para
	DESTINATION "share/rkap_aec"
	FILES_MATCHING PATTERN "*.bin"
)

add_subdirectory(test)
