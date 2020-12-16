#1.cmake version
cmake_minimum_required(VERSION 3.2)

#2.project name
project(RKAP_3A)

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
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/libRKAP_3A.so
	DESTINATION "lib"
)

# ----------------------------------------------------------------------------
#  install data
# ----------------------------------------------------------------------------
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/para
    DESTINATION "share/rkap_3a"
	FILES_MATCHING PATTERN "*.bin"
)

if(COMPILES_EXAMPLES)
	add_subdirectory(test)
endif()
