cmake_minimum_required (VERSION 3.0)
project (bg C CXX ASM)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

SET(ASM_OPTIONS "${ASM_OPTIONS} -x assembler-with-cpp")
SET(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${CFLAGS} ${ASM_OPTIONS}" )

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# the RPATH to be used when installing, but only if it's not a system directory
LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
IF("${isSystemDir}" STREQUAL "-1")
  SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
ENDIF("${isSystemDir}" STREQUAL "-1")

add_subdirectory (lib/SQLiteCpp)
add_subdirectory (src)
add_subdirectory (test)

set(TESTING_ENABLED false CACHE BOOLEAN "Whether or not to build tests")

if (${TESTING_ENABLED})
enable_testing ()
endif ()
add_test (NAME unit_tests COMMAND unit_tests)

add_custom_target(version ALL)

add_custom_command(TARGET version PRE_BUILD
  COMMAND ${CMAKE_SOURCE_DIR}/gen_version.sh
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_dependencies(bgpart version)
