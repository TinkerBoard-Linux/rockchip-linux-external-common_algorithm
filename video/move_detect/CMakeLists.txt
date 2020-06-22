#1.cmake version
cmake_minimum_required(VERSION 3.2)

#2.project name
project(move_detect)

install(DIRECTORY include/ DESTINATION "include/move_detect")
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/libmd_share.so
	DESTINATION "lib"
)

if(COMPILES_EXAMPLES)
	add_subdirectory(test)
endif()
