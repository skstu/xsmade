set(WXWIDGETS_PROJECT_NAME "wxWidgets")

set(wxBUILD_SHARED
    OFF
    CACHE BOOL "Build ${WXWIDGETS_PROJECT_NAME} as shared library" FORCE)
if(xsSYSTYPE_WINDOWS)
  set(wxBUILD_TOOLKIT
      "msw"
      CACHE STRING "Choose ${WXWIDGETS_PROJECT_NAME} toolkit" FORCE)
  #[[
    set(wxUSE_ACCESSIBILITY
        OFF
        CACHE BOOL "Choose ${WXWIDGETS_PROJECT_NAME} toolkit" FORCE)
        ]]
  # add_compile_options(-Wno-deprecated-declarations)
elseif(xsSYSTYPE_APPLE)
  set(wxBUILD_TOOLKIT
      "osx_cocoa"
      CACHE STRING "Choose ${WXWIDGETS_PROJECT_NAME} toolkit" FORCE)
  set(wxUSE_WEBVIEW
      OFF
      CACHE BOOL "Choose ${WXWIDGETS_PROJECT_NAME} toolkit" FORCE)
elseif(xsSYSTYPE_LINUX)
  set(wxBUILD_TOOLKIT
      "gtk2"
      CACHE STRING "Choose ${WXWIDGETS_PROJECT_NAME} toolkit" FORCE)
endif()
set(wxBUILD_SAMPLES
    # "ALL"
    "OFF"
    CACHE STRING "Choose ${WXWIDGETS_PROJECT_NAME} toolkit" FORCE)

add_subdirectory(${xs3RDPARTY_DIR}/wxwidgets/ ${WXWIDGETS_PROJECT_NAME})

target_add_options(
  ${WXWIDGETS_PROJECT_NAME} PRIVATE -Wno-deprecated-declarations
  -Wno-unused-command-line-argument)
# add_compile_options(-Wno-deprecated-declarations
# -Wno-unused-command-line-argument)
#[[
target_compile_options(${WXWIDGETS_PROJECT_NAME}
                       PRIVATE -Wno-deprecated-declarations)
target_compile_options(${WXWIDGETS_PROJECT_NAME}
                       PRIVATE -Wno-unused-command-line-argument)
]]
