cmake_minimum_required(VERSION 3.2)

project(ANR)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
	DESTINATION "include/ANR"
	FILES_MATCHING PATTERN "*.h"
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/libvoice_anr.a
	${CMAKE_CURRENT_SOURCE_DIR}/lib/libvoice_common.a
	DESTINATION "lib"
)
