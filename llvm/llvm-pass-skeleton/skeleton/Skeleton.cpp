#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

namespace {
  struct SkeletonPass : public FunctionPass {
    static char ID;
    SkeletonPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {
      for (auto& b : F) {
        for (auto& i : b) {
          // replace the first binary operator encountered with multiply
          // check for an binary operator llvm instruction
          if (auto* bi = dyn_cast<BinaryOperator>(&i)) {
            errs() << *bi << '\n';
            // IR builder is needed for creating new nodes
            auto* builder = new IRBuilder<>(bi);
            // create the multiply instruction
            Value* lhs = bi->getOperand(0);
            Value* rhs = bi->getOperand(1);
            auto* mi = builder->CreateMul(lhs, rhs);
            // replace mi in all uses of bi, then compiler will automatically
            // remove bi as the dead code
            for(auto& u : bi->uses()) {
              errs() << "replacing use : " << u << "\n";
              auto* user = u.getUser();
              user->setOperand(u.getOperandNo(), mi); 
            } 
            return true;
          }
        }
      }
      return false;
    }
  };
}

char SkeletonPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new SkeletonPass());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerSkeletonPass);
