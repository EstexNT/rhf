#include "Epilogue/MyFlow.hpp"

TICKFLOW_IMPL_CREATE_FN(Epilogue::CMyFlow)

Epilogue::CMyFlow::~CMyFlow(void) {}

bool Epilogue::CMyFlow::_1C(u32 opcode, u32 arg0, const s32 *args) {
    return this->CExFlow::_1C(opcode, arg0, args);
}

void Epilogue::CMyFlow::_14(void) {
    this->~CMyFlow();
}
