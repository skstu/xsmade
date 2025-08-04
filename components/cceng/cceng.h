#if !defined(__B3F92BE2_1C3F_4DCB_87C6_682D16297803__)
#define __B3F92BE2_1C3F_4DCB_87C6_682D16297803__

#include <xs.h>
#include "export.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Driver/Options.h"
#include "clang/CodeGen/ModuleBuilder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/CompilerInvocation.h"
#include "clang/FrontendTool/Utils.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/PreprocessorOptions.h"
#include "clang/Frontend/TextDiagnosticBuffer.h"
#include "clang/Parse/ParseAST.h"
#include "clang/Sema/Sema.h"
#include "clang/Frontend/Utils.h"
#include "clang/Basic/DiagnosticIDs.h"
#include "clang/Frontend/FrontendDiagnostic.h"
// #include "llvm/ADT/Triple.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Bitcode/BitcodeReader.h"
#include "llvm/CodeGen/CommandFlags.h"
#include "llvm/CodeGen/LinkAllCodegenComponents.h"
#include "llvm/Config/llvm-config.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include "llvm/ExecutionEngine/JITEventListener.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/ObjectCache.h"
#include "llvm/ExecutionEngine/Orc/DebugUtils.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/ExecutionEngine/Orc/MachOPlatform.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/Orc/TargetProcess/TargetExecutionUtils.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/Object/Archive.h"
#include "llvm/Object/ObjectFile.h"
//#include "llvm/Transforms/Instrumentation.h"
//#include "llvm/Support/Host.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/TimeProfiler.h"
#include "llvm/Support/Signals.h"
#include "llvm/Support/Process.h"
#include "llvm/Support/Timer.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/Memory.h"
#include "llvm/Support/Path.h"
#include "llvm/Support/PluginLoader.h"
#include "llvm/Support/Program.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/WithColor.h"
#include "llvm/Support/raw_ostream.h"

class CCEng final : public ICCEng {
public:
  static CCEng *Create();
  static void Destroy();

private:
  CCEng();
  virtual ~CCEng();

public:
  bool Ready() const override final;

private:
  void Init();
  void UnInit();

private:
  std::atomic_bool ready_ = false;
};

/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 02 Feb 2025 14:33:44 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__B3F92BE2_1C3F_4DCB_87C6_682D16297803__
