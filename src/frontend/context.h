#ifndef _NOTDEC_FRONTEND_CONTEXT_H_
#define _NOTDEC_FRONTEND_CONTEXT_H_

#include "llvm/IR/Module.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

namespace notdec::frontend {

struct BaseContext {
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    llvm::Module mod;
    std::map<std::string, llvm::Value *> namedValues;
    BaseContext(const char* name)
        : context(), builder(context), mod(name, context) {}
};

}

#endif

