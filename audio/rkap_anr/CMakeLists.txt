cmake_minimum_required(VERSION 3.2)

project(ANR)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
	DESTINATION "include/rkap_anr"
	FILES_MATCHING PATTERN "*.h"
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/librkap_anr.so
	DESTINATION "lib"
)

add_subdirectory(test)
