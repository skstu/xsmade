if(NOT CMAKE_CONFIGURATION_TYPES)
  get_property(HAVE_MULTI_CONFIG_GENERATOR GLOBAL
               PROPERTY GENERATOR_IS_MULTI_CONFIG)
  if(HAVE_MULTI_CONFIG_GENERATOR)
    set(CMAKE_CONFIGURATION_TYPES
        "Debug;Release"
        CACHE STRING "Available build types" FORCE)
  endif()
endif()

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(default_build_type "Debug")
  message(
    STATUS
      "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE
      "${default_build_type}"
      CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
                                               "RelWithDebInfo" "MinSizeRel")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG -D_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g") # Release with Debug Info
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG") # MinSizeRel

option(xsBUILD_PIC "Enable configure position independent code" ON)
if(xsBUILD_PIC)
  set_property(GLOBAL PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()
# if(CMAKE_CONFIGURATION_TYPES) gfn_message_info( "Multi-config generator
# detected. Available build types: ${CMAKE_CONFIGURATION_TYPES}" ) else()
# gfn_message_info( "Single-config generator detected. Build type:
# ${CMAKE_BUILD_TYPE}") endif()
