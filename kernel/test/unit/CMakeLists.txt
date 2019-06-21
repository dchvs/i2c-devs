cmake_minimum_required (VERSION 3.10.2)

include(CPack)

set (EXTRA_CFLAGS ${CMAKE_CURRENT_SOURCE_DIR}/../include
                  ${CMAKE_CURRENT_SOURCE_DIR}/../../shared
                  )

include_directories (${EXTRA_CFLAGS})
