# ##############################################################################
# Name:        build/cmake/main.cmake Purpose:     Main CMake file Author:
# Martell Created:     2024-11-08 Copyright:   (c) 2024 skstu development team
# Licence:     skstu licence
# ##############################################################################
# C:\Users\k34ub\source\skstu\xsmade\build\installed\Debug\include\wx-3.3\wx\msw
macro(GFN_FIND_WXWIDGETS OUT_WX_INCLUDES OUT_WX_LIBS OUT_WX_MSW_RC)
  if(WIN32)
    set(wxVERSION 3.3)
    set(${OUT_WX_MSW_RC}
        "${xsBUILD_INSTALLED_DIR}/${CMAKE_BUILD_TYPE}/include/wx-${wxVERSION}/wx/msw/wx.rc"
    )
    set(${OUT_WX_INCLUDES}
        "${xsBUILD_INSTALLED_DIR}/${CMAKE_BUILD_TYPE}/include/"
        "${xsBUILD_INSTALLED_DIR}/${CMAKE_BUILD_TYPE}/include/wx-${wxVERSION}/"
        "${xsBUILD_INSTALLED_DIR}/${CMAKE_BUILD_TYPE}/lib/wx/include/msw-unicode-static-${wxVERSION}/"
    )
    set(wxLIBS_DIR ${xsBUILD_INSTALLED_DIR}/${CMAKE_BUILD_TYPE}/lib)
    set(${OUT_WX_LIBS}
        "${wxLIBS_DIR}/libwx_baseu_net-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_baseu_xml-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_baseu-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_mswu_adv-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_mswu_aui-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_mswu_core-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_mswu_gl-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_mswu_html-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_mswu_media-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_mswu_propgrid-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_mswu_qa-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_mswu_ribbon-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_mswu_richtext-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_mswu_stc-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_mswu_webview-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwx_mswu_xrc-${wxVERSION}-Windows.a"
        "${wxLIBS_DIR}/libwxexpat-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwxjpeg-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwxlexilla-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwxpng-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwxregexu-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwxscintilla-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwxtiff-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwxzlib-${wxVERSION}.a")
  elseif(APPLE)
    set(wxVERSION 3.3)
    set(${OUT_WX_INCLUDES}
        "${xs3RDPARTY_DIR}/wxWidgets/include/"
        "${xsOUTPUT_DIR}/wxWidgets/lib/wx/include/osx_cocoa-unicode-static-3.3/"
    )
    set(wxLIBS_DIR ${xsOUTPUT_DIR}/wxWidgets/lib)

    set(${OUT_WX_LIBS}
        "${wxLIBS_DIR}/libwx_baseu_net-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_baseu_xml-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_baseu-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_osx_cocoau_adv-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_osx_cocoau_aui-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_osx_cocoau_core-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_osx_cocoau_gl-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_osx_cocoau_html-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_osx_cocoau_media-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_osx_cocoau_propgrid-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_osx_cocoau_qa-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_osx_cocoau_ribbon-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_osx_cocoau_richtext-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_osx_cocoau_stc-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwx_osx_cocoau_xrc-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwxjpeg-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwxlexilla-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwxpng-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwxregexu-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwxscintilla-${wxVERSION}.a"
        "${wxLIBS_DIR}/libwxtiff-${wxVERSION}.a")
  endif()
endmacro()
