//===-- LocalOpts.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/Utils/LocalOpts.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstrTypes.h"
// L'include seguente va in LocalOpts.h
#include <llvm/IR/Constants.h>
#include <cmath>

using namespace llvm;

bool runOnBasicBlock(BasicBlock &B) {

    for (auto &I : B) {
        if (Instruction::Mul == I.getOpcode()) {
            outs() << "Operazione: " << I << "\n";

            bool swp = false;
            ConstantInt *power2 = nullptr;

            if (ConstantInt *secOp = dyn_cast<ConstantInt>(I.getOperand(1))) {
              if (secOp->getValue().isPowerOf2()) {
                  power2 = secOp;
              }
            }

            if (power2 == nullptr) {
              if (ConstantInt *firOp = dyn_cast<ConstantInt>(I.getOperand(0))) {
                if (firOp->getValue().isPowerOf2()) {
                    power2 = firOp;
                    swp = true;
                }
              }
            }

            if (power2 != nullptr) {
                ConstantInt *shiftOp = ConstantInt::get(power2->getType(), power2->getValue().exactLogBase2());
                outs() << "Operando: " << power2->getValue() << "\n";

                Instruction *NewI;

                if (swp) {
                  NewI = BinaryOperator::Create(Instruction::Shl, I.getOperand(1), shiftOp);
                } else {
                  NewI = BinaryOperator::Create(Instruction::Shl, I.getOperand(0), shiftOp);
                }

                NewI->insertAfter(&I);
                I.replaceAllUsesWith(NewI);
            } else {
                outs() << "Nessuna potenza di 2\n";
            }
        }
    }
    return true;
}

bool runOnAlgebraicIdentity (BasicBlock &B) {
  bool status = false;

  for (auto &I : B) {

        if (Instruction::Add == I.getOpcode() || Instruction::Mul == I.getOpcode()) {
          
            ConstantInt *imm = nullptr;

            if (ConstantInt *secOp = dyn_cast<ConstantInt>(I.getOperand(1))) {
              if (secOp->getValue().isZero() && Instruction::Add == I.getOpcode()) {
                imm = secOp;
                I.replaceAllUsesWith(I.getOperand(0));
                status = true;
              }
              else if (secOp->getValue().isOne() && Instruction::Mul == I.getOpcode()) {
                imm = secOp;
                I.replaceAllUsesWith(I.getOperand(0));
                status = true;
              }
            }

            if (imm == nullptr) {
              if (ConstantInt *firOp = dyn_cast<ConstantInt>(I.getOperand(0))) {
                if (firOp->getValue().isZero() && Instruction::Add == I.getOpcode()) {
                    imm = firOp;
                    I.replaceAllUsesWith(I.getOperand(1));
                    status = true;
                } 
                else if (firOp->getValue().isOne() && Instruction::Mul == I.getOpcode()) {
                  imm = firOp;
                  I.replaceAllUsesWith(I.getOperand(1));
                  status = true;
                }
              }
            }
        }
  }
  if (!status)
    outs()<< "Nessuna identità trovata \n";
  return status;
}

bool runOnBasicBlockAdv(BasicBlock &B) {

    for (auto &I : B) {
        if (Instruction::Mul == I.getOpcode()) {
            outs() << "Operazione: " << I << "\n";

            bool swp = false;
            ConstantInt *imm = nullptr;

            if (ConstantInt *secOp = dyn_cast<ConstantInt>(I.getOperand(1))) {
              imm = secOp;
            }
            else if (ConstantInt *firOp = dyn_cast<ConstantInt>(I.getOperand(0))) {
                imm = firOp;
                swp = true;
            }
  

            if (imm != nullptr) {

              APInt val = imm->getValue();
              if (val.isPowerOf2()) {

                ConstantInt *shiftOp = ConstantInt::get(imm->getType(), imm->getValue().exactLogBase2());
                outs() << "Operando: " << imm->getValue() << "\n";

                Instruction *NewI_1;

                if (swp) {
                  NewI_1 = BinaryOperator::Create(Instruction::Shl, I.getOperand(1), shiftOp);
                } else {
                  NewI_1 = BinaryOperator::Create(Instruction::Shl, I.getOperand(0), shiftOp);
                }

                NewI_1->insertAfter(&I);
                I.replaceAllUsesWith(NewI_1);
              } else if ((val+1).isPowerOf2()) {

                ConstantInt *shiftOp = ConstantInt::get(imm->getType(), imm->getValue().nearestLogBase2());
                outs() << "Operando: " << imm->getValue() << "\n";

                Instruction *NewI_1;
                Instruction *NewI_2;

                if (swp) {
                  NewI_1 = BinaryOperator::Create(Instruction::Shl, I.getOperand(1), shiftOp);
                  NewI_2 = BinaryOperator::Create(Instruction::Sub, NewI_1, I.getOperand(1));
                } else {
                  NewI_1 = BinaryOperator::Create(Instruction::Shl, I.getOperand(0), shiftOp);
                  NewI_2 = BinaryOperator::Create(Instruction::Sub, NewI_1, I.getOperand(0));
                }

                NewI_1->insertAfter(&I);
                NewI_2->insertAfter(NewI_1);
                I.replaceAllUsesWith(NewI_2);
            } else if ((val-1).isPowerOf2()) {

                ConstantInt *shiftOp = ConstantInt::get(imm->getType(), imm->getValue().nearestLogBase2());
                outs() << "Operando: " << imm->getValue() << "\n";

                Instruction *NewI_1;
                Instruction *NewI_2;

                if (swp) {
                  NewI_1 = BinaryOperator::Create(Instruction::Shl, I.getOperand(1), shiftOp);
                  NewI_2 = BinaryOperator::Create(Instruction::Add, NewI_1, I.getOperand(1));
                } else {
                  NewI_1 = BinaryOperator::Create(Instruction::Shl, I.getOperand(0), shiftOp);
                  NewI_2 = BinaryOperator::Create(Instruction::Add, NewI_1, I.getOperand(0));
                }

                NewI_1->insertAfter(&I);
                NewI_2->insertAfter(NewI_1);
                I.replaceAllUsesWith(NewI_2);
              }
          }
        } else if (Instruction::SDiv == I.getOpcode()) {

            bool swp = false;
            ConstantInt *imm = nullptr;

            if (ConstantInt *secOp = dyn_cast<ConstantInt>(I.getOperand(1))) {
              imm = secOp;
            }
            else if (ConstantInt *firOp = dyn_cast<ConstantInt>(I.getOperand(0))) {
                imm = firOp;
                swp = true;
            }

            if (imm != nullptr) {
              if (imm->getValue().isPowerOf2()) {
                ConstantInt *shiftOp = ConstantInt::get(imm->getType(), imm->getValue().nearestLogBase2());
                outs() << "Operando: " << imm->getValue() << "\n";

                Instruction *NewI_1;

                if (swp) {
                  NewI_1 = BinaryOperator::Create(Instruction::LShr, I.getOperand(1), shiftOp);
                } else {
                  NewI_1 = BinaryOperator::Create(Instruction::LShr, I.getOperand(0), shiftOp);
                }

                NewI_1->insertAfter(&I);
                I.replaceAllUsesWith(NewI_1);

              }
            }

        }
    }
    return true;
}


bool runOnFunction(Function &F) {
  bool Transformed = false;

  for (auto Iter = F.begin(); Iter != F.end(); ++Iter) {
    /*if (runOnAlgebraicIdentity(*Iter))
      Transformed = true;*/
    if (runOnBasicBlockAdv(*Iter)) {
      Transformed = true;
    }
    /*if (runOnBasicBlock(*Iter)) {
      Transformed = true;
    }*/
  }
  return Transformed;
}

PreservedAnalyses LocalOpts::run(Module &M,
                                      ModuleAnalysisManager &AM) {
  for (auto Fiter = M.begin(); Fiter != M.end(); ++Fiter)
    if (runOnFunction(*Fiter))
      return PreservedAnalyses::none();
  
  return PreservedAnalyses::all();
}

