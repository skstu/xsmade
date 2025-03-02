# ##############################################################################
# Name:        build/cmake/functions.cmake Purpose:     Common CMake functions
# for skstu Author:      Martell Created:     2024-11-04 Copyright:   (c) 2024
# skstu development team Licence:     skstu licence
# ##############################################################################

include(CMakeDependentOption)
include(CMakeParseArguments) # For compatibility with CMake < 3.4
include(ExternalProject)
include(CMakePrintHelpers)

macro(xs_add_library name)

endmacro()

function(xs_set_common_target_properties target_name)
  # cmake_parse_arguments(wxCOMMON_TARGET_PROPS "DEFAULT_WARNINGS" "" ""
  # ${ARGN})

  set_target_properties(
    ${target_name}
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${xsOUTPUT_DIR}/bin"
               ARCHIVE_OUTPUT_DIRECTORY "${xsOUTPUT_DIR}/libs"
               RUNTIME_OUTPUT_DIRECTORY "${xsOUTPUT_DIR}/bin")

  if(xsBUILD_PIC)
    set_target_properties(${target_name} PROPERTIES POSITION_INDEPENDENT_CODE
                                                    TRUE)
  endif()

  target_compile_definitions(${target_name} PRIVATE wxUSE_GUI=1 wxUSE_BASE=0)
endfunction()

function(xs_set_target_output_dir target_name)
  get_target_property(TARGET_TYPE ${target_name} TYPE)

  if(TARGET_TYPE STREQUAL "STATIC_LIBRARY")
    set_target_properties(${target_name} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY
                                                    "${xsOUTPUT_DIR}/libs/")
  elseif(TARGET_TYPE STREQUAL "SHARED_LIBRARY" OR TARGET_TYPE STREQUAL
                                                  "MODULE_LIBRARY")
    set_target_properties(${target_name} PROPERTIES LIBRARY_OUTPUT_DIRECTORY
                                                    "${xsOUTPUT_DIR}/bin/")
  elseif(TARGET_TYPE STREQUAL "EXECUTABLE")
    set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                                    "${xsOUTPUT_DIR}/bin/")
  else()
    message(WARNING "Unknown target type for ${target_name}")
  endif()
endfunction()
