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
    PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${xsOUTPUT_DIR}${GEN_EXPR_DIR}"
               ARCHIVE_OUTPUT_DIRECTORY "${xsOUTPUT_DIR}${GEN_EXPR_DIR}"
               RUNTIME_OUTPUT_DIRECTORY "${xsOUTPUT_DIR}${GEN_EXPR_DIR}")

  if(xsBUILD_PIC)
    set_target_properties(${target_name} PROPERTIES POSITION_INDEPENDENT_CODE
                                                    TRUE)
  endif()

  target_compile_definitions(${target_name} PRIVATE wxUSE_GUI=1 wxUSE_BASE=0)
endfunction()
