#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace {
  struct InstrumentWithCallsPass : public FunctionPass {
    static char ID;
    InstrumentWithCallsPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      LLVMContext& ctx = F.getContext();
      // getParent to F returns the pointer to the module (i.e. the translation
      // unit in llvm
      auto logfunc = F.getParent()->getOrInsertFunction("logBinaryOp", Type::getVoidTy(ctx), Type::getInt32Ty(ctx));
      for (auto& b : F) {
        for (auto& i : b) {
          // replace the first binary operator encountered with multiply
          // check for an binary operator llvm instruction
          if (auto* bi = dyn_cast<BinaryOperator>(&i)) {
            errs() << *bi << '\n';
            // IR builder is needed for creating new nodes
            auto* builder = new IRBuilder<>(bi); // create the builder with insertion point before bi
            // move builder's insertion point one after the operator as we need
            // to log the result of the operator
            builder->SetInsertPoint(&b, ++builder->GetInsertPoint());
            Value* args = {bi};
            builder->CreateCall(logfunc, args);
            return true;
          }
        }
      }
      return false;
    }
  };
}

char InstrumentWithCallsPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerInstrumentWithCallsPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new InstrumentWithCallsPass());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerInstrumentWithCallsPass);
