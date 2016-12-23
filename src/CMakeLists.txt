set(bg_INCLUUDE_DIRS ${CMAKE_SOURCE_DIR}/inc)
file(GLOB_RECURSE bg_SOURCES "*.cpp")

list(REMOVE_ITEM bg_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
list(APPEND bg_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/data.S)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
FIND_PACKAGE(ImageMagick COMPONENTS Magick++ MagickWand MagickCore REQUIRED)
find_package(X11 REQUIRED)

include_directories(
  ${bg_INCLUUDE_DIRS}
  ${ImageMagick_INCLUDE_DIRS}
  ${X11_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/lib/SQLiteCpp/include
  ${CMAKE_SOURCE_DIR}/lib/args/)

SET(bg_DATA_DIR "${CMAKE_SOURCE_DIR}/data")
SET(bg_DATA_DIR "${CMAKE_SOURCE_DIR}/data")
SET(bg_DATA_FILES "${bg_DATA_DIR}/VERSION")
list(APPEND bg_DATA_FILES "${bg_DATA_DIR}/VERSION_TEMPLATE")
list(APPEND bg_DATA_FILES "${bg_DATA_DIR}/VERSION_TEMPLATE_DEV")
list(APPEND bg_DATA_FILES "${bg_DATA_DIR}/PROGRAM_DESCRIPTION")
list(APPEND bg_DATA_FILES "${bg_DATA_DIR}/LICENSE")
set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/data.S
  PROPERTIES OBJECT_DEPENDS "${bg_DATA_FILES}")

add_library (bgpart STATIC ${bg_SOURCES})

add_executable (bground ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries (bground bgpart SQLiteCpp sqlite3 Threads::Threads
  ${CMAKE_DL_LIBS} stdc++fs ${ImageMagick_LIBRARIES} ${X11_LIBRARIES})

if (${DEVELOPMENT_BUILD} MATCHES True)
  add_definitions (-DDEVELOPMENT_BUILD)
endif()

install (TARGETS bground DESTINATION bin)
install (TARGETS bgpart DESTINATION lib)
