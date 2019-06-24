cmake_minimum_required (VERSION 3.10.2)

include(CPack)


if ( (NOT DEFINED ENV{KERNEL_SRC}) OR (NOT EXISTS "$ENV{KERNEL_SRC}/Makefile") )
    message(FATAL_ERROR "KERNEL_SRC variable not defined or points to an invalid location")
endif()
if ((NOT DEFINED ENV{KBUILD_OUTPUT}))
  set(ENV{KBUILD_OUTPUT} "$ENV{KERNEL_SRC}")
endif()
#if (NOT EXISTS "$ENV{KBUILD_OUTPUT}/include/generated/autoconf.h")
#  message(FATAL_ERROR "KERNEL OUTPUT directory is not configured")
#endif()

if ( NOT DEFINED ENV{KTF_INCLUDE_DIRS} )
  message(FATAL_ERROR "KTF_INCLUDE_DIRS variable not defined")
endif()


find_path (LIBKTF_INCLUDE_DIRS NAMES ktf)
if (LIBKTF_INCLUDE_DIRS-NOTFOUND)
    message(FATAL_ERROR "Unable to find ktf headers")
endif()


set ( INCLUDES
      ${CMAKE_CURRENT_SOURCE_DIR}/../../shared
      ${CMAKE_CURRENT_SOURCE_DIR}
      ${LIBKTF_INCLUDE_DIRS}
    )

find_path (KTF_INCLUDE_DIRS NAMES ktf)
if (KTF_INCLUDE_DIRS-NOTFOUND)
    message(FATAL_ERROR "Unable to find ktf headers")
endif()

# Include directories
include_directories ( ${CMAKE_CURRENT_SOURCE_DIR}/..
                      ${INCLUDES}
                      ${KTF_INCLUDE_DIRS}
                    )

link_directories    ( ${INCLUDES}
                      ${KTF_INCLUDE_DIRS}
                    )

# Target
add_custom_target (driver ALL
    COMMAND $(MAKE) -C ${CMAKE_CURRENT_SOURCE_DIR}/
)

# Install the binary
install (FILES ${DRIVERNAME}.ko DESTINATION lib/modules/${CMAKE_SYSTEM_VERSION}/kernel/drivers )
