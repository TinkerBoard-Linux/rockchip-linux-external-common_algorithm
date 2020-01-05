#1.cmake version
cmake_minimum_required(VERSION 3.2)

#2.project name
project(AEC_ANR_AGC)

# ----------------------------------------------------------------------------
#  install headers
# ----------------------------------------------------------------------------
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
	DESTINATION "include/AEC_ANR_AGC"
	FILES_MATCHING PATTERN "*.h"
)

# ----------------------------------------------------------------------------
#  install libs
# ----------------------------------------------------------------------------
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/lib3a_sig_aec.so
	DESTINATION "lib"
)

# ----------------------------------------------------------------------------
#  install data
# ----------------------------------------------------------------------------
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/test/RK_VoicePara_dealyoff.bin
	DESTINATION "lib")

add_subdirectory(test)
