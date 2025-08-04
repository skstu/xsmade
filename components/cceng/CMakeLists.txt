project(cceng)

gfn_project_source_get(${CMAKE_CURRENT_SOURCE_DIR} OUT_HEADER_S OUT_SOURCE_S)
set(SOURCES ${OUT_HEADER_S} ${OUT_SOURCE_S})

add_definitions(-DSHARED_IMPLEMENTATION)
add_library(${PROJECT_NAME} SHARED ${SOURCES})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${xsINCLUDE_DIR}
          ${xsBUILD_INSTALLED_INCLUDE_DIR} ${MSYS2_MINGW64_DIR}/include/c++)

target_link_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${xsLIBS_DIR}
  ${xsLIBS_LIB_DIR}
  ${xsBUILD_INSTALLED_LIB_DIR}
  ${MSYS2_CLANG64_DIR}/lib
  ${MSYS2_MINGW64_DIR}/lib)

set(LLVM_PROJECT_LIBS
    libLLVMAArch64CodeGen.a
    libLLVMAArch64AsmParser.a
    libLLVMAArch64Desc.a
    libLLVMAArch64Disassembler.a
    libLLVMAArch64Info.a
    libLLVMAArch64Utils.a
    libLLVMAMDGPUCodeGen.a
    libLLVMAMDGPUAsmParser.a
    libLLVMAMDGPUDesc.a
    libLLVMAMDGPUDisassembler.a
    libLLVMAMDGPUInfo.a
    libLLVMAMDGPUUtils.a
    libLLVMARMCodeGen.a
    libLLVMARMAsmParser.a
    libLLVMARMDesc.a
    libLLVMARMDisassembler.a
    libLLVMARMInfo.a
    libLLVMARMUtils.a
    libLLVMAVRCodeGen.a
    libLLVMAVRAsmParser.a
    libLLVMAVRDesc.a
    libLLVMAVRDisassembler.a
    libLLVMAVRInfo.a
    libLLVMBPFCodeGen.a
    libLLVMBPFAsmParser.a
    libLLVMBPFDesc.a
    libLLVMBPFDisassembler.a
    libLLVMBPFInfo.a
    libLLVMHexagonCodeGen.a
    libLLVMHexagonAsmParser.a
    libLLVMHexagonDesc.a
    libLLVMHexagonDisassembler.a
    libLLVMHexagonInfo.a
    libLLVMLanaiCodeGen.a
    libLLVMLanaiAsmParser.a
    libLLVMLanaiDesc.a
    libLLVMLanaiDisassembler.a
    libLLVMLanaiInfo.a
    libLLVMMipsCodeGen.a
    libLLVMMipsAsmParser.a
    libLLVMMipsDesc.a
    libLLVMMipsDisassembler.a
    libLLVMMipsInfo.a
    libLLVMMSP430CodeGen.a
    libLLVMMSP430AsmParser.a
    libLLVMMSP430Desc.a
    libLLVMMSP430Disassembler.a
    libLLVMMSP430Info.a
    libLLVMNVPTXCodeGen.a
    libLLVMNVPTXDesc.a
    libLLVMNVPTXInfo.a
    libLLVMPowerPCCodeGen.a
    libLLVMPowerPCAsmParser.a
    libLLVMPowerPCDesc.a
    libLLVMPowerPCDisassembler.a
    libLLVMPowerPCInfo.a
    libLLVMRISCVCodeGen.a
    libLLVMRISCVAsmParser.a
    libLLVMRISCVDesc.a
    libLLVMRISCVDisassembler.a
    libLLVMRISCVInfo.a
    libLLVMSparcCodeGen.a
    libLLVMSparcAsmParser.a
    libLLVMSparcDesc.a
    libLLVMSparcDisassembler.a
    libLLVMSparcInfo.a
    libLLVMSystemZCodeGen.a
    libLLVMSystemZAsmParser.a
    libLLVMSystemZDesc.a
    libLLVMSystemZDisassembler.a
    libLLVMSystemZInfo.a
    libLLVMWebAssemblyCodeGen.a
    libLLVMWebAssemblyAsmParser.a
    libLLVMWebAssemblyDesc.a
    libLLVMWebAssemblyDisassembler.a
    libLLVMWebAssemblyInfo.a
    libLLVMWebAssemblyUtils.a
    libLLVMX86CodeGen.a
    libLLVMX86AsmParser.a
    libLLVMX86Desc.a
    libLLVMX86Disassembler.a
    libLLVMX86Info.a
    libLLVMXCoreCodeGen.a
    libLLVMXCoreDesc.a
    libLLVMXCoreDisassembler.a
    libLLVMXCoreInfo.a
    libLLVMAnalysis.a
    libLLVMCodeGen.a
    libLLVMCore.a
    libLLVMipo.a
    libLLVMAggressiveInstCombine.a
    libLLVMInstCombine.a
    libLLVMInstrumentation.a
    libLLVMMC.a
    libLLVMMCParser.a
    libLLVMObjCARCOpts.a
    libLLVMOption.a
    libLLVMScalarOpts.a
    libLLVMSupport.a
    libLLVMTransformUtils.a
    libLLVMVectorize.a
    libLLVMMIRParser.a
    libLLVMGlobalISel.a
    libLLVMCFGuard.a
    libLLVMAsmPrinter.a
    libLLVMDebugInfoDWARF.a
    libLLVMDebugInfoMSF.a
    libLLVMSelectionDAG.a
    libLLVMMCDisassembler.a
    libLLVMCoverage.a
    libLLVMLTO.a
    libLLVMPasses.a
    libLLVMTarget.a
    libLLVMCoroutines.a
    libLLVMIRReader.a
    libLLVMAsmParser.a
    libLLVMBitWriter.a
    libLLVMLinker.a
    libLLVMExtensions.a
    libLLVMFrontendOpenMP.a
    libLLVMProfileData.a
    libLLVMObject.a
    libLLVMDebugInfoCodeView.a
    libLLVMBitReader.a
    libLLVMTextAPI.a
    libLLVMBinaryFormat.a
    libLLVMRemarks.a
    libLLVMBitstreamReader.a
    libLLVMDemangle.a
    libLLVMExecutionEngine.a
    libLLVMInterpreter.a
    libLLVMJITLink.a
    libLLVMMCJIT.a
    libLLVMOrcShared.a
    libLLVMOrcJIT.a
    libLLVMOrcTargetProcess.a
    libLLVMRuntimeDyld.a
    libLLVMVEInfo.a
    libLLVMVEDesc.a
    libLLVMVEDisassembler.a
    libLLVMVEAsmParser.a
    libLLVMVECodeGen.a
    libLLVMLoongArchInfo.a
    libLLVMLoongArchDesc.a
    libLLVMLoongArchCodeGen.a
    libLLVMTargetParser.a
    libLLVMWindowsDriver.a
    libLLVMIRPrinter.a
    libLLVMFrontendHLSL.a
    libLLVMLoongArchAsmParser.a
    libclangCodeGen.a
    libclangSupport.a
    libclangFrontendTool.a
    libclangExtractAPI.lib
    libclangSema.lib)
set(CLANG_PROJECT_LIBS
    libclangFormat.a
    libclangToolingInclusions.a
    libclangToolingCore.a
    libclangRewrite.a
    libclangLex.a
    libclangBasic.a
    libclangCodeGen.a
    libclangDriver.a
    libclangFrontend.a
    libclangFrontendTool.a
    libclangSerialization.a
    libclangRewriteFrontend.a
    libclangARCMigrate.a
    libclangStaticAnalyzerFrontend.a
    libclangStaticAnalyzerCheckers.a
    libclangStaticAnalyzerCore.a
    libclangCrossTU.a
    libclangIndex.a
    libclangParse.a
    libclangSema.a
    libclangAnalysis.a
    libclangASTMatchers.a
    libclangEdit.a
    libclangAST.a)
if(xsSYSTYPE_WINDOWS)
  target_link_libraries(
    ${PROJECT_NAME}
    LLVM-20
    libffi.a
    libzstd.a
    libz.a
    libmd5.a
    libryml.a
    wldap32.lib
    winmm.lib
    Bcrypt.lib
    Crypt32.lib
    Normaliz.lib
    ws2_32.lib
    ntdll.lib
    libfmt.a
    libsys.a
    libstl.a
    libpthread.a
    # ${LLVM_PROJECT_LIBS} ${CLANG_PROJECT_LIBS}
  )

  add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}>
      C:/Users/k34ub/AppData/Roaming/MarsProjects/plugins/${PROJECT_NAME}.dll)
elseif(xsSYSTYPE_APPLE)
  target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${xsINCLUDE_DIR} ${xs3RDPARTY_DIR}/utfcpp/source/
            ${xsOPENSSL_INCLUDE} ${wxINCLUDES}
            /opt/homebrew/Cellar/fmt/11.0.2/include/)
  target_link_directories(${PROJECT_NAME} PRIVATE ${xsLIBS_DIR})
  target_link_libraries(
    ${PROJECT_NAME}
    "-framework CoreFoundation"
    "-framework Cocoa"
    "-framework CoreServices"
    # "-lCarbon.framework"
    "-framework ApplicationServices"
    "-framework Carbon"
    "-framework CoreGraphics"
    "-framework IOKit"
    "-framework QuartzCore"
    "-liconv"
    libsys.a
    libstl.a
    libzipcc.a
    libpthread.a
    /opt/homebrew/Cellar/fmt/11.0.2/lib/libfmt.a
    /opt/homebrew/Cellar/libuv/1.49.2/lib/libuv.a
    /opt/homebrew/Cellar/zlib/1.3.1/lib/libz.a
    ${xsOPENSSL_LIBRARY}
    ${wxLIBS})
endif()
# xs_set_common_target_properties(${PROJECT_NAME})
# xs_set_target_output_dir(${PROJECT_NAME})

add_custom_command(
  TARGET ${PROJECT_NAME}
  POST_BUILD
  COMMAND
    echo
    "Output file: ${xsOUTPUT_COMPONENTS_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}>
          ${xsOUTPUT_COMPONENTS_DIR}/$<TARGET_FILE_NAME:${PROJECT_NAME}>
  COMMENT "Printing output file path and copying file")
