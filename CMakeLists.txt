cmake_minimum_required (VERSION 3.10.2)

set (MODULENAME
    "i2c_devs")
set (DRIVERNAME
    "i2c-devs")

# Errors on warnings
#set(C_WARNINGS "-Wall -Wstrict-prototypes -Wshadow -Werror")
#set(CXX_WARNINGS "-Wall -Wshadow -Werror") ${C_WARNINGS} ${CXX_WARNINGS}
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")

include_directories (shared)
add_subdirectory (user)
add_subdirectory (kernel)
