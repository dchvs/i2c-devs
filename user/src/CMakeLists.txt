cmake_minimum_required (VERSION 3.10.2)

set(SRC_NAME ${MODULENAME})
#set(SRC_NAME_2 ${MODULENAME}s)

# Add the executable
add_executable (${SRC_NAME} ${SRC_NAME}.c)

# Include directories
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/../include
                      ${CMAKE_CURRENT_SOURCE_DIR}/../../shared)

# Link required libraries
target_link_libraries(${SRC_NAME}
  "-I${CMAKE_CURRENT_SOURCE_DIR}/../include -I${CMAKE_CURRENT_SOURCE_DIR}/../../shared"
  ${CMAKE_CURRENT_SOURCE_DIR}/i2c.c
  ${CMAKE_CURRENT_SOURCE_DIR}/rtc.c
  ${CMAKE_CURRENT_SOURCE_DIR}/lcd.c)

#target_link_libraries(${SRC_NAME_2}
#  "-I${CMAKE_CURRENT_SOURCE_DIR}/../include -I${CMAKE_CURRENT_SOURCE_DIR}/../../shared"
#  ${CMAKE_CURRENT_SOURCE_DIR}/i2c.c
#  ${CMAKE_CURRENT_SOURCE_DIR}/gpio.c
#  ${CMAKE_CURRENT_SOURCE_DIR}/lcd.c
#  ${CMAKE_CURRENT_SOURCE_DIR}/rtc.c)


# Install the binary
install (TARGETS ${SRC_NAME} DESTINATION bin)

include(CPack)
