cmake_minimum_required(VERSION 3.2)

project(test_aec_anr_agc)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../include)

link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../lib)

# add executable file
add_executable(${PROJECT_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/test_aec_anr_agc.c)

# add link library
target_link_libraries(${PROJECT_NAME}
	3a_sig_aec
	m)

install(TARGETS ${PROJECT_NAME}
	RUNTIME DESTINATION bin)
