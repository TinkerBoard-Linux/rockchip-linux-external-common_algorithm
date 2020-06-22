cmake_minimum_required(VERSION 3.2)

project(ANR)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
	DESTINATION "include"
	FILES_MATCHING PATTERN "*.h"
)

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/libRKAP_ANR.so
	DESTINATION "lib"
)

if(COMPILES_EXAMPLES)
	add_subdirectory(test)
endif()
