#include "Grading/MyFlow.hpp"

#include "Grading/MyLayout.hpp"

#include "Grading/MyFlowDecl.hpp"

#include "Sound.hpp"

#include "rev_tengoku.rsid"

TICKFLOW_IMPL_CREATE_FN(Grading::CMyFlow)

Grading::CMyFlow::~CMyFlow() {}

bool Grading::CMyFlow::_1C(u32 opcode, u32 arg0, const s32 *args) {
    switch (opcode) {
    case TF_GRADING_SHOW_CAPTION:
        mScene->mLayout->fn_8000C088();
        break;
    case TF_GRADING_SHOW_COMMENT:
        mScene->mLayout->fn_8000C0B4();
        break;
    case TF_GRADING_SHOW_GRADE:
        mScene->mLayout->fn_8000C15C();
        if (mScene->mGrade == eGrade_HI) {
            gSoundManager->play(SE_RESULT_HI_LEVEL);
        }
        if (mScene->mGrade == eGrade_OK) {
            gSoundManager->play(SE_RESULT_HEIBON);
        }
        if (mScene->mGrade == eGrade_NG) {
            gSoundManager->play(SE_RESULT_BAD);
        }
        break;
    case TF_GRADING_CHECK_FOLLOW:
        if (gCheckPointManager->fn_801EB7A8()) {
            mCondvar = TRUE;
        }
        else {
            mCondvar = FALSE;
        }
        break;
    case TF_GRADING_SHOW_FOLLOW:
        mScene->mLayout->fn_8000C0F4();
        break;

    default:
        return this->CExFlow::_1C(opcode, arg0, args);
    }

    return false;
}

void Grading::CMyFlow::_14(void) {
    this->~CMyFlow();
}
