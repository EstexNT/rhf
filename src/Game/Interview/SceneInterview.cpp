#include "Interview/SceneInterview.hpp"

#include "Interview/MyFlow.hpp"

#include <revolution/OS.h>

#include "GameManager.hpp"
#include "FileManager.hpp"
#include "InputCheckManager.hpp"
#include "TickFlowManager.hpp"
#include "Controller.hpp"
#include "LayoutManager.hpp"
#include "CellAnimManager.hpp"
#include "MyCanvas.hpp"

#include "TPL.hpp"

#include "Mem.hpp"

#include "code_800D2920.hpp"

#include "PauseLayout.hpp"
#include "CursorLayout.hpp"
#include "BalloonLayout.hpp"

#include "Random.hpp"

#include "cellanim/interview/ver0/rcad_interview_bg_00_labels.h"
#include "cellanim/interview/ver0/rcad_interview_bg_01_labels.h"
#include "cellanim/interview/ver0/rcad_interview_bg_02_labels.h"
#include "cellanim/interview/ver0/rcad_interview_far_00_labels.h"
#include "cellanim/interview/ver0/rcad_interview_far_01_labels.h"
#include "cellanim/interview/ver0/rcad_interview_far_02_labels.h"
#include "cellanim/interview/ver0/rcad_interview_girl_labels.h"
#include "cellanim/interview/ver0/rcad_interview_wrestler_1P_labels.h"
#include "cellanim/interview/2play/rcad_interview_wrestler_2P_labels.h"

#include "rev_tengoku.rsid"

namespace Interview {

s32 sceneVer;

} // namespace Interview

void CSceneInterview::fn_800B5444(u32 button) {
    gGameManager->getCurrentScene<CSceneInterview>()->fn_800B6860(button, 2, 0, 0.0f);
}

SCENE_IMPL_CREATE_FN(CSceneInterview)

void CSceneInterview::fn_800B5508(void) {
    fn_801D369C(eHeapGroup_SceneAsset);

    if (gFileManager->fn_801D42E0(21)) {
        if (Interview::sceneVer == 0) {
            gFileManager->fn_801D3F94(21, "content2/cellanim/interview/ver0/cellanim.szs");
        }
        else if ((Interview::sceneVer == 1) || (Interview::sceneVer == 2) || (Interview::sceneVer == 3)) {
            gFileManager->fn_801D3F94(21, "content2/cellanim/interview/2play/cellanim.szs");
        }
        else if (Interview::sceneVer == 4) {
            gFileManager->fn_801D3F94(21, "content2/cellanim/interview/remix04/cellanim.szs");
        }
        else if (Interview::sceneVer == 5) {
            gFileManager->fn_801D3F94(21, "content2/cellanim/interview/remix09/cellanim.szs");
        }
        else if (Interview::sceneVer == 6) {
            gFileManager->fn_801D3F94(21, "content2/cellanim/interview/remix10/cellanim.szs");
        }
    }

    fn_801D3644();
}

void CSceneInterview::_10(void) {
    fn_800B5508();
}

void CSceneInterview::fn_800B5624(void) {
    if (
        (Interview::sceneVer == 0) || (Interview::sceneVer == 1) || (Interview::sceneVer == 2) ||
        (Interview::sceneVer == 3) || (Interview::sceneVer == 4) || (Interview::sceneVer == 5) ||
        (Interview::sceneVer == 6)
    ) {
        gFileManager->fn_801D41CC(21);
    }
}

bool CSceneInterview::_24(void) {
    return gFileManager->fn_801D42FC(21);
}

enum {
    bg_00,
    bg_01,
    bg_02,
    far_00,
    far_01,
    far_02,
    girl,
    wrestler_1P,
    wrestler_2P
};

void CSceneInterview::_14(void) {
    this->CExScene::_14();

    mIsTwoPlay = Interview::sceneVer == 3;
    mWrestlerCount = mIsTwoPlay ? 2 : 1;

    gInputCheckManager->setUnk418(fn_800B5444);
    gInputCheckManager->setUnk42E(true);
    gInputCheckManager->setUnk42B(mIsTwoPlay);

    gTickFlowManager->registerFlow<Interview::CMyFlow>();

    gControllerManager->fn_801D5FF0(0)->fn_801D5500(WPAD_BUTTON_A, 3);
    gControllerManager->fn_801D5FF0(1)->fn_801D5500(WPAD_BUTTON_A, 3);

    gLayoutManager->_20(1);
    gLayoutManager->_24(94, ""); // layout_common

    gLayoutManager->fn_801D6AEC(3);
    gLayoutManager->registerLayout<CPauseLayout>();     // Index 0
    gLayoutManager->registerLayout<CCursorLayout>();    // Index 1
    gLayoutManager->registerLayout<CBalloonLayout>();   // Index 2

    gLayoutManager->getLayout<CBalloonLayout>(2)->fn_8003A1D0(
        0, -40.0f, -60.0f, 540.0f, 120.0f, true, -180.0f, 55.0f, false
    );

    mPauseLayout = gLayoutManager->getLayout<CPauseLayout>(0);

    gLayoutManager->getLayout<CPauseLayout>(0)->setDrawEnable(false);
    gLayoutManager->getLayout<CCursorLayout>(1)->setDrawEnable(false);

    void *bg_00_brcadAddr       = gFileManager->fn_801D4270(21, "./interview_bg_00.brcad");
    void *bg_01_brcadAddr       = gFileManager->fn_801D4270(21, "./interview_bg_01.brcad");
    void *bg_02_brcadAddr       = gFileManager->fn_801D4270(21, "./interview_bg_02.brcad");
    void *far_00_brcadAddr      = gFileManager->fn_801D4270(21, "./interview_far_00.brcad");
    void *far_01_brcadAddr      = gFileManager->fn_801D4270(21, "./interview_far_01.brcad");
    void *far_02_brcadAddr      = gFileManager->fn_801D4270(21, "./interview_far_02.brcad");
    void *girl_brcadAddr        = gFileManager->fn_801D4270(21, "./interview_girl.brcad");
    void *wrestler_1P_brcadAddr = gFileManager->fn_801D4270(21, "./interview_wrestler_1P.brcad");

    u32 tplLen      = gFileManager->fn_801D422C(21, "./cellanim.tpl");
    void *tplAddr   = gFileManager->fn_801D4270(21, "./cellanim.tpl");

    UserTPLBind(tplAddr);
    DCStoreRange(tplAddr, tplLen);

    gCellAnimManager->registBank(bg_00_brcadAddr, tplAddr, bg_00);
    gCellAnimManager->registBank(bg_01_brcadAddr, tplAddr, bg_01);
    gCellAnimManager->registBank(bg_02_brcadAddr, tplAddr, bg_02);
    gCellAnimManager->registBank(far_00_brcadAddr, tplAddr, far_00);
    gCellAnimManager->registBank(far_01_brcadAddr, tplAddr, far_01);
    gCellAnimManager->registBank(far_02_brcadAddr, tplAddr, far_02);
    gCellAnimManager->registBank(girl_brcadAddr, tplAddr, girl);
    gCellAnimManager->registBank(wrestler_1P_brcadAddr, tplAddr, wrestler_1P);

    if ((Interview::sceneVer == 1) || (Interview::sceneVer == 2) || (Interview::sceneVer == 3)) {
        void *wrestler_2P_brcadAddr = gFileManager->fn_801D4270(21, "./interview_wrestler_2P.brcad");
        gCellAnimManager->registBank(wrestler_2P_brcadAddr, tplAddr, wrestler_2P);
    }

    mPanelAnim = gCellAnimManager->createCellAnim(bg_00, interview_bg_00_panel_00);
    mPanelAnim->setLayer(5000);
    mPanelAnim->setPosY(-80.0f);

    for (s32 i = 0; i < mWrestlerCount; i++) {
        u8 ID = (i == 0) ? wrestler_1P : wrestler_2P;

        mWrestler[i].bodyAnim = gCellAnimManager->createCellAnim(ID, interview_wrestler_1P_beat);
        mWrestler[i].bodyAnim->setLayer(i + 3000);
        mWrestler[i].bodyAnim->goToAnimEnd();

        if (!mIsTwoPlay) {
            mWrestler[i].bodyAnim->setPos(0.0f, 80.0f);
        }
        else {
            if (i == 0) {
                mWrestler[i].bodyAnim->setPos(-80.0f, 80.0f);
            }
            else {
                mWrestler[i].bodyAnim->setPos(80.0f, 80.0f);
            }
        }

        mWrestler[i].faceAnim = gCellAnimManager->createCellAnim(ID, interview_wrestler_1P_face);
        mWrestler[i].faceAnim->setBase(mWrestler[i].bodyAnim, 8, true);

        mWrestler[i].faceMark = gCellAnimManager->createCellAnim(ID, interview_wrestler_1P_face_mark);
        mWrestler[i].faceMark->setBase(mWrestler[i].faceAnim, 6, true);

        mWrestler[i].shadowAnim = gCellAnimManager->createCellAnim(ID, interview_wrestler_1P_shadow);
        mWrestler[i].shadowAnim->setLayer(4000);

        mWrestler[i].shadowAnim->setPos(mWrestler[i].bodyAnim->getPos());
        mWrestler[i].shadowAnim->setPosY(mWrestler[i].shadowAnim->getPosY() + 220.0f);

        mWrestler[i].sweatBase = gCellAnimManager->createCellAnim(ID, interview_wrestler_1P_sweat_base);
        mWrestler[i].sweatBase->setLayer(2500);
        mWrestler[i].sweatBase->setEnabled(false);

        mWrestler[i].bodyAnimPaper = gCellAnimManager->createCellAnim(ID, interview_wrestler_1P_beat);
        mWrestler[i].faceAnimPaper = gCellAnimManager->createCellAnim(ID, interview_wrestler_1P_face);
        mWrestler[i].faceMarkPaper = gCellAnimManager->createCellAnim(ID, interview_wrestler_1P_face_mark);
        mWrestler[i].shadowAnimPaper = gCellAnimManager->createCellAnim(ID, interview_wrestler_1P_shadow);
        mWrestler[i].sweatBasePaper = gCellAnimManager->createCellAnim(ID, interview_wrestler_1P_sweat_base);

        if (!mIsTwoPlay) {
            mWrestler[i].faceMark->setEnabled(false);
            mWrestler[i].faceMarkPaper->setEnabled(false);
        }
    }

    mGirlBodyAnim = gCellAnimManager->createCellAnim(girl, interview_girl_girl_mike_on);
    mGirlBodyAnim->setLayer(2000);
    mGirlBodyAnim->goToAnimEnd();
    mGirlBodyAnim->setPos(-260.0f, 300.0f);

    mGirlFaceAnim = gCellAnimManager->createCellAnim(girl, interview_girl_girl_face_blink);
    mGirlFaceAnim->goToAnimEnd();
    mGirlFaceAnim->setBase(mGirlBodyAnim, 11, true);

    mGirlShadowAnim = gCellAnimManager->createCellAnim(girl, interview_girl_shadow);
    mGirlShadowAnim->setLayer(4000);
    mGirlShadowAnim->setPos(mGirlBodyAnim->getPos());

    mCameramenAnim = gCellAnimManager->createCellAnim(girl, interview_girl_cameramen);
    mCameramenAnim->setLayer(1000);
    mCameramenAnim->setPosY(120.0f);

    gMyCanvasManager->fn_8007BEF8(1);

    CCellAnim *bgAnim = gCellAnimManager->createCellAnim(bg_00, interview_bg_00_bg);
    bgAnim->setLayer(6000);

    mBGFlashAnim = gCellAnimManager->createCellAnim(bg_01, interview_bg_01_bg_flash);
    mBGFlashAnim->setLayer(4500);
    mBGFlashAnim->setEnabled(false);

    mPaperAnim = gCellAnimManager->createCellAnim(bg_00, interview_bg_00_paper);
    mPaperAnim->setLayer(400);
    mPaperAnim->setEnabled(false);

    mPaperBackAnim = gCellAnimManager->createCellAnim(bg_00, interview_bg_00_paper_back);
    mPaperBackAnim->setLayer(500);
    mPaperBackAnim->setEnabled(false);

    mPaperPanelAnim = gCellAnimManager->createCellAnim(bg_00, interview_bg_00_panel_00);

    mPaperGirlBodyAnim = gCellAnimManager->createCellAnim(girl, interview_girl_girl_mike_on);
    mPaperGirlFaceAnim = gCellAnimManager->createCellAnim(girl, interview_girl_girl_face_blink);
    mPaperGirlShadowAnim = gCellAnimManager->createCellAnim(girl, interview_girl_shadow);
    mPaperCameramenAnim = gCellAnimManager->createCellAnim(girl, interview_girl_cameramen);

    mPaperGirlFaceAnim->setBase(mPaperGirlBodyAnim, 11, true);
    mPaperCameramenAnim->setBase(mPaperAnim, 1, true);
    mPaperGirlBodyAnim->setBase(mPaperAnim, 1, true);
    mPaperGirlShadowAnim->setBase(mPaperAnim, 1, true);

    for (s32 i = 0; i < mWrestlerCount; i++) {
        mWrestler[i].faceAnimPaper->setBase(mWrestler[i].bodyAnimPaper, 8, true);
        mWrestler[i].faceMarkPaper->setBase(mWrestler[i].faceAnimPaper, 6, true);
        mWrestler[i].sweatBasePaper->setBase(mPaperAnim, 1, true);
        mWrestler[i].bodyAnimPaper->setBase(mPaperAnim, 1, true);
        mWrestler[i].shadowAnimPaper->setBase(mPaperAnim, 1, true);

        mWrestler[i].bodyAnimPaper->setPos(mWrestler[i].bodyAnim->getPos());
        mWrestler[i].faceAnimPaper->setPos(mWrestler[i].faceAnim->getPos());
        mWrestler[i].shadowAnimPaper->setPos(mWrestler[i].shadowAnim->getPos());
        mWrestler[i].sweatBasePaper->setPos(mWrestler[i].sweatBase->getPos());
    }

    mPaperPanelAnim->setBase(mPaperAnim, 1, true);

    mPaperGirlBodyAnim->setPos(mGirlBodyAnim->getPos());
    mPaperGirlFaceAnim->setPos(mGirlFaceAnim->getPos());
    mPaperGirlShadowAnim->setPos(mGirlShadowAnim->getPos());
    mPaperCameramenAnim->setPos(mCameramenAnim->getPos());
    mPaperPanelAnim->setPos(mPanelAnim->getPos());

    mFarViewAnim = gCellAnimManager->createCellAnim(far_00, interview_far_00_far_view);
    mFarViewAnim->setLayer(200);
    mFarViewAnim->setEnabled(false);

    mStadiumAnim = gCellAnimManager->createCellAnim(bg_02, interview_bg_02_stadium_beat);
    mStadiumAnim->setLayer(100);
    mStadiumAnim->goToAnimEnd();
    mStadiumAnim->setEnabled(false);

    mTelopAnimBegin = gCellAnimManager->createCellAnim(bg_02, interview_bg_02_telop);
    mTelopAnimEnd = gCellAnimManager->createCellAnim(bg_02, interview_bg_02_telop);

    mTelopAnimBegin->setLayer(99);
    mTelopAnimEnd->setLayer(99);

    mTelopAnimBegin->setFrameAtKey(0);
    mTelopAnimEnd->setFrameAtKey(1);

    mTelopAnimBegin->setEnabled(false);
    mTelopAnimEnd->setEnabled(false);

    gMyCanvasManager->fn_8007BEF8(2);

    if (Interview::sceneVer == 1) {
        mWrestler[0].faceMark->setEnabled(true);
        mWrestler[0].faceMarkPaper->setEnabled(true);

        mWrestler[0].bodyAnim->setBankID(wrestler_1P);
        mWrestler[0].faceAnim->setBankID(wrestler_1P);
        mWrestler[0].faceMark->setBankID(wrestler_1P);
        mWrestler[0].shadowAnim->setBankID(wrestler_1P);
        mWrestler[0].sweatBase->setBankID(wrestler_1P);

        mWrestler[0].bodyAnimPaper->setBankID(wrestler_1P);
        mWrestler[0].faceAnimPaper->setBankID(wrestler_1P);
        mWrestler[0].faceMarkPaper->setBankID(wrestler_1P);
        mWrestler[0].shadowAnimPaper->setBankID(wrestler_1P);
        mWrestler[0].sweatBasePaper->setBankID(wrestler_1P);
    }
    else if (Interview::sceneVer == 2) {
        mWrestler[0].faceMark->setEnabled(true);
        mWrestler[0].faceMarkPaper->setEnabled(true);

        mWrestler[0].bodyAnim->setBankID(wrestler_2P);
        mWrestler[0].faceAnim->setBankID(wrestler_2P);
        mWrestler[0].faceMark->setBankID(wrestler_2P);
        mWrestler[0].shadowAnim->setBankID(wrestler_2P);
        mWrestler[0].sweatBase->setBankID(wrestler_2P);

        mWrestler[0].bodyAnimPaper->setBankID(wrestler_2P);
        mWrestler[0].faceAnimPaper->setBankID(wrestler_2P);
        mWrestler[0].faceMarkPaper->setBankID(wrestler_2P);
        mWrestler[0].shadowAnimPaper->setBankID(wrestler_2P);
        mWrestler[0].sweatBasePaper->setBankID(wrestler_2P);
    }

    mCameramenJumping.setEasing(0, 1);
    mCameramenScaling.setEasing(0, 1);

    mPaperScaling.setEasing(0, 1);
    mPaperRotation.setEasing(0, 1);

    mStadiumZooming.setEasing(0, 1);
    mStadiumOpacity.setEasing(1, 2);

    gMyCanvasManager->fn_8007BFA8(2, 140.0f, 240.0f);
    gMyCanvasManager->fn_8007BF6C(2, 1.3f, 1.3f);

    mCameramenJumping.fn_801EA8E0(0.0f, 120.0f, 0.0f, 0.0f, 120.0f, 0.0f, 1.0f);
    mCameramenJumping.fn_801EA550(0.0f, 12.0f, true);

    mCameramenScaling.setEasing(3, 2);
    mCameramenScaling.fn_801EA698(2.0f, 2.0f);
    mCameramenScaling.fn_801EA550(0.0f, 12.0f, true);

    for (s32 i = 0; i < mWrestlerCount; i++) {
        mWrestler[i].unk38 = false;
        mWrestler[i].unk28 = 2;
        mWrestler[i].unk2C = 2;
        mWrestler[i].unk30 = 2;
        mWrestler[i].unk34 = 2;
    }

    mUnk258 = eCellAnimRenderEff_5;
}

void CSceneInterview::_28(void) {
    CController *controller = gControllerManager->fn_801D5FF0(0);

    if (mPaperScaling.getIsTicking() || mPaperRotation.getIsTicking()) {
        mPaperScaling.fn_801E9DE8(FALSE);
        mPaperRotation.fn_801E9DE8(FALSE);

        mPaperAnim->setScale(mPaperScaling.getCurrent(), mPaperScaling.getCurrent());
        mPaperAnim->setAngle(mPaperRotation.getCurrent());

        if (mPaperScaling.hasEnded()) {
            f32 rotateBy = mPaperRotateCounterclock ? -3.0f : 3.0f;
            
            mPaperScaling.fn_801EA698(mPaperScaling.getCurrent(), mPaperScaling.getCurrent() * 0.9f);
            mPaperRotation.fn_801EA698(mPaperRotation.getCurrent(), rotateBy + mPaperRotation.getCurrent());

            mPaperScaling.fn_801EA550(0.0f, 192.0f, false);
            mPaperRotation.fn_801EA550(0.0f, 192.0f, false);

            bool miss = false;
            for (s32 i = 0; i < mWrestlerCount; i++) {
                if (mWrestler[i].bodyAnimPaper->getAnimID() == interview_wrestler_1P_pose_miss) {
                    miss = true;
                }
            }

            gSoundManager->play(miss ? SE_WRESTLER_POSE_MISS : SE_WRESTLER_POSE_SUCCESS);
        }
    }

    if (!mBGFlashAnim->getEnabled()) {
        for (s32 i = 0; i < mWrestlerCount; i++) {
            s32 sweatCount = sRandom.nextU32(4);
            for (s32 j = 0; j < sweatCount; j++) {
                CCellAnim *sweatAnim = gCellAnimManager->createCellAnim(wrestler_1P, interview_wrestler_1P_sweat);
                sweatAnim->setBase(mWrestler[i].sweatBase, 0, true);
                sweatAnim->setAnimDestroy(interview_wrestler_1P_sweat);
                sweatAnim->setPos(mWrestler[i].bodyAnim->getPos());

                f32 ofsX, ofsY;
                f32 temp;
                do {
                    ofsX = sRandom.nextF32(300.0f) - 150.0f;
                    ofsY = sRandom.nextF32(600.0f);

                    temp = ofsX;
                    if (temp <= 0.0f) {
                        temp = -ofsX;
                    }
                } while ((60.0f < temp) && (ofsY - 400.0f) < -280.0f);

                sweatAnim->setPosX(sweatAnim->getPosX() + ofsX);
                sweatAnim->setPosY(sweatAnim->getPosY() + (ofsY - 400.0f));
            }
        }
    }

    u16 girlFaceAnimID = mGirlFaceAnim->getAnimID();
    if (
        ((girlFaceAnimID == interview_girl_girl_face_blink)   ||
         (girlFaceAnimID == interview_girl_girl_face_talk_00) ||
         (girlFaceAnimID == interview_girl_girl_face_talk_01) ||
         (girlFaceAnimID == interview_girl_girl_face_talk_02) ||
         (girlFaceAnimID == interview_girl_girl_face_talk_03)
        ) && !mGirlFaceAnim->getPlaying()
    ) {
        if (sRandom.nextU32(180) == 0) {
            mGirlFaceAnim->setAnim(interview_girl_girl_face_blink);
        }
    }

    if (mCameramenJumping.getIsTicking()) {
        mCameramenJumping.fn_801E9DE8(FALSE);
        mCameramenAnim->setPosY(mCameramenJumping.getCurrentY());
    }

    if (mCameramenScaling.getIsTicking()) {
        mCameramenScaling.fn_801E9DE8(FALSE);
        mCameramenAnim->setScale(mCameramenScaling.getCurrent(), mCameramenScaling.getCurrent());
    }

    if (mStadiumZooming.getIsTicking()) {
        mStadiumZooming.fn_801E9DE8(FALSE);
        mStadiumAnim->setScale(mStadiumZooming.getCurrent(), mStadiumZooming.getCurrent());
    }

    if (mStadiumOpacity.getIsTicking()) {
        mStadiumOpacity.fn_801E9DE8(FALSE);
        mStadiumAnim->setOpacity(mStadiumOpacity.getCurrent());
        mTelopAnimBegin->setOpacity(mStadiumOpacity.getCurrent());
        mTelopAnimEnd->setOpacity(mStadiumOpacity.getCurrent());
    }
}

void CSceneInterview::_1C(void) {
    for (s32 i = 0; i < mWrestlerCount; i++) {
        fn_800B70F4(i);
    }
    this->CExScene::_1C();
}

void CSceneInterview::_20(void) {
    if (mUnk258 != eCellAnimRenderEff_5) {
        fn_8009E1B4(mUnk258);
    }

    gCellAnimManager->endBank(bg_00);
    gCellAnimManager->endBank(bg_01);
    gCellAnimManager->endBank(bg_02);
    gCellAnimManager->endBank(far_00);
    gCellAnimManager->endBank(far_01);
    gCellAnimManager->endBank(far_02);
    gCellAnimManager->endBank(girl);
    gCellAnimManager->endBank(wrestler_1P);

    gCellAnimManager->endCellAnimByBank(bg_00);
    gCellAnimManager->endCellAnimByBank(bg_01);
    gCellAnimManager->endCellAnimByBank(bg_02);
    gCellAnimManager->endCellAnimByBank(far_00);
    gCellAnimManager->endCellAnimByBank(far_01);
    gCellAnimManager->endCellAnimByBank(far_02);
    gCellAnimManager->endCellAnimByBank(girl);
    gCellAnimManager->endCellAnimByBank(wrestler_1P);

    if ((Interview::sceneVer == 1) || (Interview::sceneVer == 2) || (Interview::sceneVer == 3)) {
        gCellAnimManager->endBank(wrestler_2P);
        gCellAnimManager->endCellAnimByBank(wrestler_2P);
    }

    this->CExScene::_20();
}

void CSceneInterview::fn_800B6860(u32 button, s32 type, s32 param_3, f32 ticks) {
    bool fromP1 = (button == INPUT_P1(eInputType_TriggerA)) || (button == INPUT_P1(eInputType_Trigger_6));
    s32 wrestlerID = fromP1 ? 0 : 1;

    if (
        (!mPaperAnim->getEnabled() && !mWrestler[wrestlerID].unk38 && !mFarViewAnim->getEnabled()) ||
        (type != 2)
    ) {
        if (
            ((button == INPUT_P1(eInputType_TriggerA)) || (button == INPUT_P1(eInputType_Trigger_6)) ||
            ((button == INPUT_P2(eInputType_TriggerA)) || (button == INPUT_P2(eInputType_Trigger_6)))) &&
            (type == 2)
        ) {
            fn_80009ABC();
        }

        if ((button == INPUT_P1(eInputType_TriggerA)) || (button == INPUT_P2(eInputType_TriggerA))) {
            if (param_3 == 0) {
                mWrestler[wrestlerID].unk28 = type;
                if (type == 0) {
                    CCellAnim *wrestlerBody = mWrestler[wrestlerID].bodyAnim;
                    if (
                        (wrestlerBody->getAnimID() != interview_wrestler_1P_beat) &&
                        (wrestlerBody->getAnimID() != interview_wrestler_1P_beat_chest) &&
                        (wrestlerBody->getAnimID() != interview_wrestler_1P_ready)
                    ) {
                        wrestlerBody->setAnim(interview_wrestler_1P_beat);
                    }

                    mWrestler[wrestlerID].faceAnim->setAnim(interview_wrestler_1P_face_nod);

                    fn_800D2920(
                        SE_WRESTLER_UNAZUKI,
                        SE_WRESTLER_UNAZUKI, SE_WRESTLER_UNAZUKI_2P,
                        mIsTwoPlay, fromP1
                    );
                    if (mIsTwoPlay) {
                        gSoundManager->tune_volume(0.8f);
                    }
                }
                else if (type == 1) {
                    CCellAnim *wrestlerBody = mWrestler[wrestlerID].bodyAnim;
                    if (
                        (wrestlerBody->getAnimID() != interview_wrestler_1P_beat) &&
                        (wrestlerBody->getAnimID() != interview_wrestler_1P_beat_chest) &&
                        (wrestlerBody->getAnimID() != interview_wrestler_1P_ready)
                    ) {
                        wrestlerBody->setAnim(interview_wrestler_1P_beat);
                    }

                    mWrestler[wrestlerID].faceAnim->setAnim(interview_wrestler_1P_face_nod_miss);

                    fn_800D2920(
                        SE_WRESTLER_UNAZUKI_MISS_VOICE_OSII,
                        SE_WRESTLER_UNAZUKI_MISS_VOICE_OSII, SE_WRESTLER_UNAZUKI_MISS_VOICE_OSII_2P,
                        mIsTwoPlay, fromP1
                    );
                    if (mIsTwoPlay) {
                        gSoundManager->tune_volume(0.8f);
                    }
                }
                else if (type == 2) {
                    CCellAnim *wrestlerBody = mWrestler[wrestlerID].bodyAnim;
                    if (
                        (wrestlerBody->getAnimID() == interview_wrestler_1P_beat) ||
                        (wrestlerBody->getAnimID() == interview_wrestler_1P_beat_chest) ||
                        (wrestlerBody->getAnimID() == interview_wrestler_1P_ready)
                    ) {
                        mWrestler[wrestlerID].faceAnim->setAnim(interview_wrestler_1P_face_nod_out);

                        if (
                            ((mGirlFaceAnim->getAnimID() != interview_girl_girl_face_talk_00) &&
                             (mGirlFaceAnim->getAnimID() != interview_girl_girl_face_talk_01) &&
                             (mGirlFaceAnim->getAnimID() != interview_girl_girl_face_talk_02) &&
                             (mGirlFaceAnim->getAnimID() != interview_girl_girl_face_talk_03)) ||
                            !mGirlFaceAnim->getPlaying()
                        ) {
                            mGirlFaceAnim->setAnim(interview_girl_girl_face_nod_out);
                        }

                        fn_800D2920(
                            SE_WRESTLER_UNAZUKI_MISS_VOICE,
                            SE_WRESTLER_UNAZUKI_MISS_VOICE, SE_WRESTLER_UNAZUKI_MISS_VOICE_2P,
                            mIsTwoPlay, fromP1
                        );
                        if (mIsTwoPlay) {
                            gSoundManager->tune_volume(0.8f);
                        }
                    }
                }

                if (mUnk264 == mWrestlerCount) {
                    fn_800B7AA8(ticks);
                    mUnk264 = 0;
                }
            }
            else if (param_3 == 1) {
                mWrestler[wrestlerID].unk2C = type;

                mWrestler[wrestlerID].bodyAnim->setAnim(interview_wrestler_1P_pose2_a);
                mWrestler[wrestlerID].faceAnim->setAnimFreezeFrame(interview_wrestler_1P_face, 2.0f);

                fn_800D2920(
                    SE_WRESTLER_TERE1,
                    SE_WRESTLER_TERE1, SE_WRESTLER_TERE1_2P,
                    mIsTwoPlay, fromP1
                );
                if (mIsTwoPlay) {
                    gSoundManager->tune_volume(0.8f);
                }

                if (mUnk264 == mWrestlerCount) {
                    mUnk264 = 0;
                }
            }
            else if (param_3 == 2) {
                mWrestler[wrestlerID].unk30 = type;
                
                mWrestler[wrestlerID].bodyAnim->setAnim(interview_wrestler_1P_pose2_b);
                mWrestler[wrestlerID].faceAnim->setAnim(interview_wrestler_1P_face_pose2);

                fn_800D2920(
                    SE_WRESTLER_TERE2,
                    SE_WRESTLER_TERE2, SE_WRESTLER_TERE2_2P,
                    mIsTwoPlay, fromP1
                );
                if (mIsTwoPlay) {
                    gSoundManager->tune_volume(0.8f);
                }

                if (mUnk264 == mWrestlerCount) {
                    fn_800B7BE4(ticks);
                    mUnk264 = 0;
                }
            }
        }
        else if ((button == INPUT_P1(eInputType_Trigger_6)) || (button == INPUT_P2(eInputType_Trigger_6))) {
            s32 random;
            do {
                random = sRandom.nextU32(6);
                if (5 < mWrestler[wrestlerID].bodyAnim->getAnimID()) {
                    break;
                }
            } while ((u16)random == mWrestler[wrestlerID].bodyAnim->getAnimID());

            
        }
    }
}
