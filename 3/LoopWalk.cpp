#include "llvm/Transforms/Utils/LoopWalk.h"
#include "llvm/Analysis/ValueTracking.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstrTypes.h"
#include <cmath>

using namespace llvm;

std::vector<Instruction*> ToMove;
std::set<Instruction*> Invariants;

bool isOpInv(Value *operand, Loop &loop) {
  if (isa<llvm::Constant>(operand) || isa<llvm::Argument>(operand)) {
    return true;
  }

  if (llvm::Instruction *inst = dyn_cast<llvm::Instruction>(operand)) {
    if (!loop.contains(inst->getParent()) || Invariants.count(inst)) {
      return true;
    }
  }
  return false;
}

bool isInstInv(Instruction *I, Loop &loop) {
 
  if (!isSafeToSpeculativelyExecute(I)) {
    outs() << *I << " - Errore! L'istruzione non può essere spostata \n";
    return false;
  }
 
  for(auto it = I->op_begin(); it != I->op_end(); ++it) {
    if (!isOpInv(*it, loop)) 
      return false;
  }
  outs() << "Istruzione removibile: " << *I << "\n";
  
  return true;
}

void findInstInv(BasicBlock &block, Loop &loop) {
  for(auto &I : block) {
    if (isInstInv(&I, loop)) {
        ToMove.push_back(&I);
        Invariants.insert(&I);
      }
  } 
}

bool runOnLoop(Loop &loop, LoopAnalysisManager &LAM, LoopStandardAnalysisResults &LAR, LPMUpdater &LU) {

  // controllo e visualizzazione preheader
  BasicBlock* preheader = loop.getLoopPreheader();
  preheader->print(outs());

  if (!preheader) {
    return false;
  }

  SmallVector<BasicBlock*> vec {};
  loop.getExitBlocks(vec);
  BasicBlock * exitBlock = loop.getUniqueExitBlock();
  exitBlock->print(outs());
  llvm::DominatorTree &DT = LAR.DT;
  DT.print(outs());

  BasicBlock *BB = (DT.getRootNode())->getBlock();
  BB->print(outs());

  auto loopBlocks = loop.getBlocks();
  for (auto &block : loopBlocks) {
      bool dominateExits = true;
      block->print(outs());

      for(auto it = vec.begin(); it != vec.end(); ++it) {
          BasicBlock *exitBlock = *it;
          outs() << "Exit Block: " << exitBlock->getName() << "\n\n";
          if(!DT.dominates(block, exitBlock))
              dominateExits = false;
      }
      
      outs() << block->getName() << " - Dominate Exit: " << dominateExits << "\n";

      if (dominateExits) 
        findInstInv(*block, loop);
  }

  for (auto &I : ToMove) {
    outs () << "Instruction to move: " << *I << "\n";
    I->moveBefore(preheader->getTerminator());
  }

  preheader->print(outs());

  return true;
}


PreservedAnalyses LoopWalk::run(Loop &L, LoopAnalysisManager &LAM, LoopStandardAnalysisResults &LAR, LPMUpdater &LU) {

  if (!runOnLoop(L,LAM,LAR,LU)){
    return PreservedAnalyses::none();
  }
  
  return PreservedAnalyses::all();
}

