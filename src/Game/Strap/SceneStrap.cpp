#include "Strap/SceneStrap.hpp"

#include "Strap/MyFlow.hpp"

#include "Mem.hpp"

#include <revolution/SC.h>
#include <revolution/OS.h>
#include <revolution/WPAD.h>

#include "FileManager.hpp"
#include "InputCheckManager.hpp"
#include "CellAnimManager.hpp"
#include "HBMManager.hpp"
#include "RFLManager.hpp"

#include "TickFlowManager.hpp"
#include "ExFlowDecl.hpp"

#include "Controller.hpp"

#include "TPL.hpp"

#include "cellanim/strap/verE/rcad_strap_labels.h"

namespace Strap {

s32 sceneVer;

} // namespace Strap

void CSceneStrap::fn_8007B270(u32) {}

SCENE_IMPL_CREATE_FN(CSceneStrap)

void CSceneStrap::fn_8007B2D8(void) {
    memPushGroup(eMemGroup_SceneAsset);

    if (gFileManager->getArcFree(2)) {
        switch (SCGetLanguage()) {
        case SC_LANG_FR:
            gFileManager->startArchive(2, "content2/cellanim/strap/verF/cellanim.szs");
            break;
        case SC_LANG_SP:
            gFileManager->startArchive(2, "content2/cellanim/strap/verS/cellanim.szs");
            break;
        default:
            gFileManager->startArchive(2, "content2/cellanim/strap/verE/cellanim.szs");
            break;
        }
    }

    memPopGroup();
}

void CSceneStrap::_10(void) {
    fn_8007B2D8();
}

bool CSceneStrap::_24(void) {
    return gFileManager->getArcReady(2);
}

void CSceneStrap::_14(void) {
    this->CExScene::_14();

    gInputCheckManager->setUnk418(fn_8007B270);

    gTickFlowManager->registerFlow<Strap::CMyFlow>();

    void *brcadAddr = gFileManager->arcGetFileAddr(2, "./strap.brcad");

    u32 tplLen = gFileManager->arcGetFileLen(2, "./cellanim.tpl");
    void *tplAddr = gFileManager->arcGetFileAddr(2, "./cellanim.tpl");
    UserTPLBind(tplAddr);
    DCStoreRange(tplAddr, tplLen);

    gCellAnimManager->registBank(brcadAddr, tplAddr, 0);

    mStrapAnim = gCellAnimManager->createCellAnim(0, strap_fade_in);

    mStrapAnim->prepareAnim(strap_show_a, NULL);
    mStrapAnim->playFromBegin();

    gHBMManager->setUnk416(false);

    mFrameCounter = 0;
    mFadeOpacity = -1;

    gRFLManager->fn_800C2C40();
}

TFD_EXTERN(lbl_80256044)

void CSceneStrap::_28(void) {
    CController *controller = gControllerManager->fn_801D5FF0(0);

    mFrameCounter++;
    if (mFadeOpacity > 0) {
        mFadeOpacity -= 8;
        mStrapAnim->setOpacity(mFadeOpacity);
        if (mFadeOpacity == 0) {
            gTickFlowManager->fn_801E1CC0(lbl_80256044);
        }
    }
    else if (mFadeOpacity != 0) {
        if (!mStrapAnim->getPlaying()) {
            mFadeOpacity = 0x100;
        }
        else if (mFrameCounter >= 90) {
            u32 button = WPAD_BUTTON_LEFT  | WPAD_BUTTON_RIGHT |
                         WPAD_BUTTON_DOWN  | WPAD_BUTTON_UP    |
                         WPAD_BUTTON_A     | WPAD_BUTTON_B     |
                         WPAD_BUTTON_1     | WPAD_BUTTON_2     |
                         WPAD_BUTTON_PLUS  | WPAD_BUTTON_MINUS;
            if (controller->checkTrig(button)) {
                mFadeOpacity = 0x100;
            }
        }
    }
}

void CSceneStrap::_1C(void) {
    this->CExScene::_1C();
}

void CSceneStrap::_20(void) {
    gFileManager->waitArc(1);

    gRFLManager->fn_800C2CA4();
    gRFLManager->fn_800C2E04();
    gRFLManager->fn_800C2C98();

    gHBMManager->setUnk416(true);

    gCellAnimManager->endBank(0);
    gCellAnimManager->endCellAnimByBank(0);

    gFileManager->endArchive(2);

    this->CExScene::_20();
}

void CSceneStrap::fn_8007B6C4(u32, u32) {}

void CSceneStrap::_18(void) {
    this->CExScene::_18();
}
