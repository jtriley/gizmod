# define system dependent compiler flags

include(CheckCXXCompilerFlag)

# with -fPIC
if (UNIX AND NOT WIN32)
  #if (CMAKE_SIZEOF_VOID_P MATCHES "8")
    check_cxx_compiler_flag("-fPIC" WITH_FPIC)
    if (WITH_FPIC)
      add_definitions(-fPIC)
    endif (WITH_FPIC)
  #endif (CMAKE_SIZEOF_VOID_P MATCHES "8")
endif (UNIX AND NOT WIN32)

add_definitions(-DHAVE_CONFIG_H -Wall -Werror)
