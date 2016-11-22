set(bg_INCLUUDE_DIRS ${CMAKE_SOURCE_DIR}/inc)
file(GLOB_RECURSE bg_SOURCES "*.cpp")

list(REMOVE_ITEM bg_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
list(APPEND bg_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/data.S)

include_directories(
  ${bg_INCLUUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/lib/args/)

SET(bg_DATA_DIR "${CMAKE_SOURCE_DIR}/data")
set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/data.S
  PROPERTIES OBJECT_DEPENDS "${bg_DATA_DIR}/VERSION;${bg_DATA_DIR}/VERSION_TEMPLATE;${bg_DATA_DIR}/VERSION_TEMPLATE_DEV")

add_library (bgpart SHARED ${bg_SOURCES})

add_executable (bg ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries (bg bgpart)

if (${DEVELOPMENT_BUILD} MATCHES True)
  add_definitions (-DDEVELOPMENT_BUILD)
endif()

install (TARGETS bg DESTINATION bin)
install (TARGETS bgpart DESTINATION lib)
