#include "Rap/SceneRap.hpp"

#include "Rap/MyFlow.hpp"

#include "Rap/MyFlowDecl.hpp"

#include "Rap/MyLayout.hpp"

#include <nw4r/math.h>

#include "GameManager.hpp"

#include "FileManager.hpp"

#include "InputCheckManager.hpp"

#include "TickFlowManager.hpp"

#include "LayoutManager.hpp"

#include "CellAnimManager.hpp"

#include "Sound.hpp"

#include "Controller.hpp"

#include "PauseLayout.hpp"
#include "CursorLayout.hpp"
#include "BalloonLayout.hpp"

#include "TPL.hpp"

#include "rev_tengoku.rsid"

#include "cellanim/rap/ver0/rcad_rap_labels.h"
#include "cellanim/rap/ver0/rcad_rap_bg_labels.h"
#include "cellanim/rap/ver0/rcad_rap_bg_01_labels.h"
#include "cellanim/rap/ver0/rcad_rap_airplane_labels.h"
#include "cellanim/rap/ver1/rcad_rap_chandelier_labels.h"

void CSceneRap::fn_80050284(u32 button) {
    gGameManager->getCurrentScene<CSceneRap>()->fn_8005128C(button, 2, 0.0f);
}

SCENE_IMPL_CREATE_FN(CSceneRap)

void CSceneRap::fn_80050340(void) {
    fn_801D369C(eHeapGroup_SceneAsset);
    if (gFileManager->getArcFree(25)) {
        if (Rap::sceneVer == 0) {
            gFileManager->startArchive(25, "content2/cellanim/rap/ver0/cellanim.szs");
            gFileManager->startArchive(78, "content2/layout/layout_rap.szs");
        }
        else if (Rap::sceneVer == 1) {
            gFileManager->startArchive(25, "content2/cellanim/rap/ver1/cellanim.szs");
            gFileManager->startArchive(78, "content2/layout/layout_rap.szs");
        }
        else if (Rap::sceneVer == 2) {
            gFileManager->startArchive(25, "content2/cellanim/rap/remix06/cellanim.szs");
            gFileManager->startArchive(78, "content2/layout/layout_rap.szs");
        }
        else if (Rap::sceneVer == 3) {
            gFileManager->startArchive(25, "content2/cellanim/rap/remix09/cellanim.szs");
            gFileManager->startArchive(78, "content2/layout/layout_rap.szs");
        }
        else if (Rap::sceneVer == 4) {
            gFileManager->startArchive(25, "content2/cellanim/rap/remix10/cellanim.szs");
            gFileManager->startArchive(78, "content2/layout/layout_rap.szs");
        }
    }
    fn_801D3644();
}

void CSceneRap::_10(void) {
    fn_80050340();
}

void CSceneRap::fn_800504DC(void) {
    if (
        (Rap::sceneVer == 0) || (Rap::sceneVer == 1) || (Rap::sceneVer == 2) ||
        (Rap::sceneVer == 3) || (Rap::sceneVer == 4)
    ) {
        gFileManager->endArchive(25);
        gFileManager->endArchive(78);
    }
}

bool CSceneRap::_24(void) {
    return gFileManager->getArcReady(25) && gFileManager->getArcReady(78);
}

void CSceneRap::_14(void) {
    this->CExScene::_14();

    gInputCheckManager->setUnk418(fn_80050284);

    gTickFlowManager->registerFlow<Rap::CMyFlow>();

    gLayoutManager->_20(2);
    gLayoutManager->_24(94, ""); // layout_common
    gLayoutManager->_24(78, ""); // layout_rap

    gLayoutManager->fn_801D6AEC(4);
    gLayoutManager->registerLayout<CPauseLayout>();   // Index 0
    gLayoutManager->registerLayout<CCursorLayout>();  // Index 1
    gLayoutManager->registerLayout<CBalloonLayout>(); // Index 2
    gLayoutManager->registerLayout<Rap::CMyLayout>(); // Index 3

    gLayoutManager->getLayout<CBalloonLayout>(2)->fn_8003A1D0(
        0, 0.0f, 20.0f, 480.0f, 120.0f, true, 0.0f, -55.0f, true
    );

    mPauseLayout = gLayoutManager->getLayout<CPauseLayout>(0);

    gLayoutManager->getLayout<CPauseLayout>(0)->setDrawEnable(false);
    gLayoutManager->getLayout<CCursorLayout>(1)->setDrawEnable(false);

    mMyLayout = gLayoutManager->getLayout<Rap::CMyLayout>(3);

    void *rap_brcadAddr = gFileManager->arcGetFileAddr(25, "./rap.brcad");
    void *rap_bg_brcadAddr = gFileManager->arcGetFileAddr(25, "./rap_bg.brcad");
    void *rap_bg_01_brcadAddr = gFileManager->arcGetFileAddr(25, "./rap_bg_01.brcad");
    void *rap_airplane_brcadAddr = gFileManager->arcGetFileAddr(25, "./rap_airplane.brcad");

    u32 tplLen = gFileManager->arcGetFileLen(25, "./cellanim.tpl");
    void *tplAddr = gFileManager->arcGetFileAddr(25, "./cellanim.tpl");

    UserTPLBind(tplAddr);
    DCStoreRange(tplAddr, tplLen);

    gCellAnimManager->registBank(rap_brcadAddr, tplAddr, 0);
    gCellAnimManager->registBank(rap_bg_brcadAddr, tplAddr, 1);
    gCellAnimManager->registBank(rap_bg_01_brcadAddr, tplAddr, 2);
    gCellAnimManager->registBank(rap_airplane_brcadAddr, tplAddr, 3);

    if (Rap::sceneVer == 1) {
        void *rap_chandelier_brcadAddr = gFileManager->arcGetFileAddr(25, "./rap_chandelier.brcad");
        gCellAnimManager->registBank(rap_chandelier_brcadAddr, tplAddr, 4);
    }

    mBGAnim = gCellAnimManager->createCellAnim(1, rap_bg_bg_evening);
    mFenceAnim = gCellAnimManager->createCellAnim(1, rap_bg_fence);
    mGroundDryAnim = gCellAnimManager->createCellAnim(1, rap_bg_ground_normal);
    mGroundWetAnim = gCellAnimManager->createCellAnim(1, rap_bg_ground_wet);

    mBGAnim->setLayer(4000);
    mFenceAnim->setLayer(2500);
    mGroundDryAnim->setLayer(3800);
    mGroundWetAnim->setLayer(3799);

    mCarAnim = gCellAnimManager->createCellAnim(0, rap_car_beat);
    mCarAnim->setLayer(2200);
    mCarAnim->goToAnimEnd();

    mCarShadowAnim = gCellAnimManager->createCellAnim(0, rap_car_shadow);
    mCarShadowAnim->setLayer(3500);

    mAirplaneAnim = gCellAnimManager->createCellAnim(3, rap_airplane_airplane);
    mAirplaneAnim->setLayer(3000);
    mAirplaneAnim->goToAnimEnd();
    mAirplaneAnim->setEnabled(false);

    mAirplaneShadowAnim = gCellAnimManager->createCellAnim(3, rap_airplane_shadow);
    mAirplaneShadowAnim->setLayer(3500);
    mAirplaneShadowAnim->setEnabled(false);
    mAirplaneShadowAnim->setOpacity(0xC0);
    mAirplaneShadowAnim->setScale(64.0f, 16.0f);

    mAirplaneTireAnim = gCellAnimManager->createCellAnim(3, rap_airplane_tire);
    mAirplaneTireAnim->setLayer(2999);
    mAirplaneTireAnim->setEnabled(false);

    mRoomAnim = gCellAnimManager->createCellAnim(2, rap_bg_01_room);
    mRoomAnim->setLayer(200);
    mRoomAnim->setScale(5.2f, 5.2f);
    mRoomAnim->setEnabled(false);

    mTVAnim = gCellAnimManager->createCellAnim(2, rap_bg_01_tv);
    mTVAnim->setLayer(300);
    mTVAnim->setBase(mRoomAnim, 0, false);
    mTVAnim->setEnabled(false);

    mSofaAnim = gCellAnimManager->createCellAnim(2, rap_bg_01_sofa);
    mSofaAnim->setLayer(100);
    mSofaAnim->setBase(mRoomAnim, 0, false);
    mSofaAnim->setAnimLoop(rap_bg_01_sofa);
    mSofaAnim->setEnabled(false);

    if (Rap::sceneVer == 1) {
        mChandelierAnim = gCellAnimManager->createCellAnim(4, rap_chandelier_chandelier);
        mChandelierAnim->setLayer(3900);
        mChandelierAnim->setPosY(-440.0f);
    }

    mPlayerChara.fn_80051770(true, this);
    mOtherChara.fn_80051770(false, this);
    mGirlChara.fn_80051DAC(mCarAnim);

    mPlane3D = new CPseudo3D;
    mPlane3D->fn_80072A14(0.0f, 240.0f, 8.0f, 0.0f, -30.0f, 0.1f);

    mPlaneY.setEasingType(0);
    mPlaneZ.setEasingType(1);

    mPlaneY.setEasingPower(1);
    mPlaneZ.setEasingPower(2);

    mPlaneY.fn_801EA698(-1800.0f, 0.0f);
    mPlaneZ.fn_801EA698(0.0f, 1.0f);

    mPlaneY.fn_801EA550(0.0f, 48.0f, true);
    mPlaneZ.fn_801EA550(0.0f, 48.0f, true);

    mPlaneY.setIsTicking(false);
    mPlaneZ.setIsTicking(false);

    mCharaDarken.setEasingType(0);
    mFenceDarken.setEasingType(0);

    mCharaDarken.setEasingPower(1);
    mFenceDarken.setEasingPower(1);

    mCharaDarken.fn_801EA698(255.0f, 0.0f);
    mFenceDarken.fn_801EA698(255.0f, 0.0f);

    mCharaDarken.fn_801EA550(0.0f, 48.0f, true);
    mFenceDarken.fn_801EA550(0.0f, 48.0f, true);

    mCharaDarken.setIsTicking(false);
    mFenceDarken.setIsTicking(false);

    mAirplaneShadowPos.setEasing(0, 1);
    mAirplaneShadowPos.fn_801EA698(1000.0f, -2000.0f);
    mAirplaneShadowPos.fn_801EA550(0.0f, 48.0f, true);
    mAirplaneShadowPos.setIsTicking(false);

    mUnk34 = 5;

    mUnk1BC = false;
    mUnk1BD = false;
    mUnk1BE = false;
    mUnk1BF = false;

    mGroundWetness.setEasing(3, 2);
    mGroundWetness.fn_801EA698(255.0f, 0.0f);
    mGroundWetness.fn_801EA550(0.0f, 48.0f, true);
    mGroundWetness.setIsTicking(false);

    mUnk1F4.setEasing(3, 2);
    mUnk1F4.fn_801EA698(4.0f, 1.0f);
    mUnk1F4.fn_801EA550(0.0f, 48.0f, true);
    mUnk1F4.setIsTicking(false);

    mUnk228.setEasing(0, 1);
}

void CSceneRap::_28(void) {
    CController *controller = gControllerManager->fn_801D5FF0(0);

    if (mPlayerChara.throughStareTimer != 0) {
        mPlayerChara.throughStareTimer--;
        if (mPlayerChara.throughStareTimer == 0) {
            mPlayerChara.headAnim->switchAnim(rap_C_head);
        }
    }

    if (mOtherChara.throughStareTimer != 0) {
        mOtherChara.throughStareTimer--;
        if (mOtherChara.throughStareTimer == 0) {
            mOtherChara.headAnim->switchAnim(rap_C_head);
        }
    }

    if (mPlaneY.getIsTicking() || mPlaneZ.getIsTicking()) {
        mPlaneY.fn_801E9DE8(FALSE);
        mPlaneZ.fn_801E9DE8(FALSE);

        fn_800516C0();

        if (mPlaneY.hasEnded() && mPlaneZ.hasEnded()) {
            mAirplaneAnim->setEnabled(false);
            mAirplaneTireAnim->setEnabled(false);
        }
    }

    if (mCharaDarken.getIsTicking()) {
        mCharaDarken.fn_801E9DE8(FALSE);

        f32 color = mCharaDarken.getCurrent();
        color = (color < 0.0f) ? 0.0f : (color > 255.0f) ? 255.0f : color;

        u8 colorInt = static_cast<u8>(color);

        mPlayerChara.footAnim->setBackColor(colorInt, colorInt, colorInt);
        mPlayerChara.bodyAnim->setBackColor(colorInt, colorInt, colorInt);
        mPlayerChara.headAnim->setBackColor(colorInt, colorInt, colorInt);
        mPlayerChara.eyeAnim->setBackColor(colorInt, colorInt, colorInt);
        mPlayerChara.mouthAnim->setBackColor(colorInt, colorInt, colorInt);

        mOtherChara.footAnim->setBackColor(colorInt, colorInt, colorInt);
        mOtherChara.bodyAnim->setBackColor(colorInt, colorInt, colorInt);
        mOtherChara.headAnim->setBackColor(colorInt, colorInt, colorInt);
        mOtherChara.eyeAnim->setBackColor(colorInt, colorInt, colorInt);
        mOtherChara.mouthAnim->setBackColor(colorInt, colorInt, colorInt);

        mGirlChara.footAnim->setBackColor(colorInt, colorInt, colorInt);
        mGirlChara.bodyAnim->setBackColor(colorInt, colorInt, colorInt);
        mGirlChara.eyeAnim->setBackColor(colorInt, colorInt, colorInt);
        mGirlChara.mouthAnim->setBackColor(colorInt, colorInt, colorInt);

        mCarAnim->setBackColor(colorInt, colorInt, colorInt);
    }

    if (mFenceDarken.getIsTicking()) {
        mFenceDarken.fn_801E9DE8(FALSE);

        f32 color = mFenceDarken.getCurrent();
        color = (color < 0.0f) ? 0.0f : (color > 255.0f) ? 255.0f : color;

        u8 colorInt = static_cast<u8>(color);

        mFenceAnim->setBackColor(colorInt, colorInt, colorInt);
    }

    if (mAirplaneShadowPos.getIsTicking()) {
        mAirplaneShadowPos.fn_801E9DE8(FALSE);

        mAirplaneShadowAnim->setPosY(mAirplaneShadowPos.getCurrent());
        if (!mAirplaneShadowPos.getIsTicking()) {
            mAirplaneShadowAnim->setEnabled(false);
        }
    }

    if (TRUE) {
        mGroundWetness.fn_801E9DE8(FALSE);

        f32 color = mGroundWetness.getCurrent();
        color = (color < 0.0f) ? 0.0f : (color > 255.0f) ? 255.0f : color;

        u8 colorInt = static_cast<u8>(color);

        mGroundWetAnim->setOpacity(255 - colorInt);
    }

    if (mUnk1F4.getIsTicking()) {
        mUnk1F4.fn_801E9DE8(FALSE);

        mSofaAnim->setEnabled(true);

        f32 scale = mUnk1F4.getCurrent();
        mSofaAnim->setScale(scale, scale);
    }

    if (mUnk228.getIsTicking()) {
        mUnk228.fn_801E9DE8(FALSE);

        f32 x = -(nw4r::math::SinDeg(mUnk228.getCurrent())) * 120.0f;
        f32 y = (nw4r::math::CosDeg(mUnk228.getCurrent()) * 20.0f) - 20.0f;

        mCarAnim->setPos(x, y);
        mCarShadowAnim->setPos(x, y);

        mMyLayout->fn_80073198(x, y);
    }
}

void CSceneRap::_1C(void) {
    mPlayerChara.fn_8005193C();
    mOtherChara.fn_8005193C();
    this->CExScene::_1C();
}

void CSceneRap::_20(void) {
    delete mPlane3D;

    gCellAnimManager->endBank(0);
    gCellAnimManager->endBank(1);
    gCellAnimManager->endBank(2);
    gCellAnimManager->endBank(3);

    gCellAnimManager->endCellAnimByBank(0);
    gCellAnimManager->endCellAnimByBank(1);
    gCellAnimManager->endCellAnimByBank(2);
    gCellAnimManager->endCellAnimByBank(3);

    if (Rap::sceneVer == 1) {
        gCellAnimManager->endBank(4);
        gCellAnimManager->endCellAnimByBank(4);
    }

    this->CExScene::_20();
}

TFD_BEGIN(lbl_8023EDC0)
    TFC_RAP_201_0(0, 0, 0)
    TFC_PLAY_SFX(698)
    TFC_PLAY_SFX(256)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023EE1C)
    TFC_RAP_201_0(0, 0, -1)
    TFC_PLAY_SFX(698)
    TFD_CMD(TF_025, 1, 0), 192,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023EE78)
    TFC_RAP_201_0(0, 0, 1)
    TFC_PLAY_SFX(698)
    TFD_CMD(0x025, 1, 0), 320,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023EED4)
    TFC_RAP_201_0(0, 0, 0)
    TFC_PLAY_SFX(699)
    TFD_CMD(0x025, 1, 0), 256,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023EF30)
    TFC_RAP_201_0(0, 0, -1)
    TFC_PLAY_SFX(699)
    TFD_CMD(0x025, 1, 0), 192,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023EF8C)
    TFC_RAP_201_0(0, 0, 1)
    TFC_PLAY_SFX(699)
    TFD_CMD(0x025, 1, 0), 320,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023EFE8)
    TFC_RAP_201_0(0, 1, 0)
    TFC_PLAY_SFX(700)
    TFD_CMD(0x025, 1, 0), 256,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F054)
    TFC_RAP_201_0(0, 1, -1)
    TFC_PLAY_SFX(700)
    TFD_CMD(0x025, 1, 0), 192,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F0C0)
    TFC_RAP_201_0(0, 1, 1)
    TFC_PLAY_SFX(700)
    TFD_CMD(0x025, 1, 0), 320,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F12C)
    TFC_RAP_201_0(0, 1, 0)
    TFC_PLAY_SFX(701)
    TFD_CMD(0x025, 1, 0), 256,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F198)
    TFC_RAP_201_0(0, 1, -1)
    TFC_PLAY_SFX(701)
    TFD_CMD(0x025, 1, 0), 192,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F204)
    TFC_RAP_201_0(0, 1, 1)
    TFC_PLAY_SFX(701)
    TFD_CMD(0x025, 1, 0), 320,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F270)
    TFC_RAP_201_0(0, 2, 0)
    TFC_PLAY_SFX(702)
    TFD_CMD(0x025, 1, 0), 256,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F2C4)
    TFC_RAP_201_0(0, 2, -1)
    TFC_PLAY_SFX(702)
    TFD_CMD(0x025, 1, 0), 192,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F318)
    TFC_RAP_201_0(0, 2, 1)
    TFC_PLAY_SFX(702)
    TFD_CMD(0x025, 1, 0), 320,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F36C)
    TFC_RAP_201_0(0, 2, 0)
    TFC_PLAY_SFX(703)
    TFD_CMD(0x025, 1, 0), 256,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F3C0)
    TFC_RAP_201_0(0, 2, -1)
    TFC_PLAY_SFX(703)
    TFD_CMD(0x025, 1, 0), 192,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F414)
    TFC_RAP_201_0(0, 2, 1)
    TFC_PLAY_SFX(703)
    TFD_CMD(0x025, 1, 0), 320,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F468)
    TFC_RAP_201_0(0, 3, 0)
    TFC_PLAY_SFX(704)
    TFD_CMD(0x025, 1, 0), 256,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F4CC)
    TFC_RAP_201_0(0, 3, -1)
    TFC_PLAY_SFX(704)
    TFD_CMD(0x025, 1, 0), 192,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F530)
    TFC_RAP_201_0(0, 3, 1)
    TFC_PLAY_SFX(704)
    TFD_CMD(0x025, 1, 0), 320,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F594)
    TFC_RAP_201_0(0, 3, 0)
    TFC_PLAY_SFX(705)
    TFD_CMD(0x025, 1, 0), 256,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F5F8)
    TFC_RAP_201_0(0, 3, -1)
    TFC_PLAY_SFX(705)
    TFD_CMD(0x025, 1, 0), 192,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

TFD_BEGIN(lbl_8023F65C)
    TFC_RAP_201_0(0, 3, -1)
    TFC_PLAY_SFX(705)
    TFD_CMD(0x025, 1, 0), 320,
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_REST(12)
    TFC_RAP_20C(1)
    TFC_IF_EQU(0)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
        TFC_REST(12)
    TFC_ENDIF()
    TFC_RAP_201_1(0)
TFD_STOP()

void CSceneRap::fn_8005128C(u32 button, s32 type, f32 ticks) {
    if (button == eInputType_TriggerA) {
        if (type == 0) {
            switch (mUnk34) {
            case 0: {
                if (mUnk1BC) {
                    gTickFlowManager->fn_801E1CC0(lbl_8023EED4, -ticks);
                }
                else {
                    gTickFlowManager->fn_801E1CC0(lbl_8023EDC0, -ticks);
                }
            } break;

            case 1: {
                if (mUnk1BC) {
                    gTickFlowManager->fn_801E1CC0(lbl_8023F12C, -ticks);
                }
                else {
                    gTickFlowManager->fn_801E1CC0(lbl_8023EFE8, -ticks);
                }
            } break;

            case 2: {
                if (mUnk1BC) {
                    gTickFlowManager->fn_801E1CC0(lbl_8023F36C, -ticks);
                }
                else {
                    gTickFlowManager->fn_801E1CC0(lbl_8023F270, -ticks);
                }
            } break;

            case 3: {
                if (mUnk1BC) {
                    gTickFlowManager->fn_801E1CC0(lbl_8023F594, -ticks);
                }
                else {
                    gTickFlowManager->fn_801E1CC0(lbl_8023F468, -ticks);
                }
            } break;
            
            default:
                break;
            }

            if (mUnk1BD) {
                for (s32 i = 0; i < 4; i++) {
                    CCellAnim *lightAnim = gCellAnimManager->createCellAnim(0, rap_car_light);
                    lightAnim->setBase(mCarAnim, 1 + i, false);
                    lightAnim->setLayer(2199);
                    lightAnim->setAnimDestroy(rap_car_light);
                }

                mCharaDarken.fn_801EA698(32.0f, 255.0f);
                mCharaDarken.fn_801EA550(0.0f, 12.0f, true);
            }

            if (mUnk1BF) {
                mPlayerChara.eyeAnim->setAnim(rap_eye_D_arrange);
                mOtherChara.eyeAnim->setAnim(rap_eye_D_arrange);
            }
        }
        else if (type == 1) {
            fn_80009ABC();

            if (ticks >= 0.0f) {
                switch (mUnk34) {
                case 0: {
                    if (mUnk1BC) {
                        gTickFlowManager->fn_801E1CC0(lbl_8023EF8C);
                    }
                    else {
                        gTickFlowManager->fn_801E1CC0(lbl_8023EE78);
                    }
                } break;

                case 1: {
                    if (mUnk1BC) {
                        gTickFlowManager->fn_801E1CC0(lbl_8023F204);
                    }
                    else {
                        gTickFlowManager->fn_801E1CC0(lbl_8023F0C0);
                    }
                } break;

                case 2: {
                    if (mUnk1BC) {
                        gTickFlowManager->fn_801E1CC0(lbl_8023F414);
                    }
                    else {
                        gTickFlowManager->fn_801E1CC0(lbl_8023F318);
                    }
                } break;

                case 3: {
                    if (mUnk1BC) {
                        gTickFlowManager->fn_801E1CC0(lbl_8023F65C);
                    }
                    else {
                        gTickFlowManager->fn_801E1CC0(lbl_8023F530);
                    }
                } break;
                
                default:
                    break;
                }

                gSoundManager->play(SE_MISS);
            }
            else {
                switch (mUnk34) {
                case 0: {
                    if (mUnk1BC) {
                        gTickFlowManager->fn_801E1CC0(lbl_8023EF30);
                    }
                    else {
                        gTickFlowManager->fn_801E1CC0(lbl_8023EE1C);
                    }
                } break;

                case 1: {
                    if (mUnk1BC) {
                        gTickFlowManager->fn_801E1CC0(lbl_8023F198);
                    }
                    else {
                        gTickFlowManager->fn_801E1CC0(lbl_8023F054);
                    }
                } break;

                case 2: {
                    if (mUnk1BC) {
                        gTickFlowManager->fn_801E1CC0(lbl_8023F3C0);
                    }
                    else {
                        gTickFlowManager->fn_801E1CC0(lbl_8023F2C4);
                    }
                } break;

                case 3: {
                    if (mUnk1BC) {
                        gTickFlowManager->fn_801E1CC0(lbl_8023F5F8);
                    }
                    else {
                        gTickFlowManager->fn_801E1CC0(lbl_8023F4CC);
                    }
                } break;
                
                default:
                    break;
                }

                gSoundManager->play(SE_MISS);
            }
        }
        else if (type == 2) {
            fn_80009ABC();

            mPlayerChara.footAnim->switchAnim(rap_P_cough);
            mPlayerChara.footAnim->playFromBegin();

            mOtherChara.fn_80051D00();

            gSoundManager->play(SE_MISS);
        }
    }
}

void CSceneRap::fn_800516C0(void) {
    f32 x, y, scale;
    mPlane3D->fn_80072A54(0.0f, mPlaneY.getCurrent(), mPlaneZ.getCurrent(), &x, &y, &scale);

    mAirplaneAnim->setPos(x, y);
    mAirplaneAnim->setScale(scale, scale);

    mAirplaneTireAnim->setPos(x, y);
    mAirplaneTireAnim->setScale(scale, scale);
}

void CSceneRap::CharaRapper::fn_80051770(bool isPlayer, CSceneRap *_scene) {
    scene = _scene;
    amIPlayer = isPlayer;

    footAnim = gCellAnimManager->createCellAnim(0, rap_foot_MD);
    bodyAnim = gCellAnimManager->createCellAnim(0, rap_body_MD);
    eyeAnim = gCellAnimManager->createCellAnim(0, rap_eye_MD);
    mouthAnim = gCellAnimManager->createCellAnim(0, rap_mouth_MD);

    u16 headAnimID = amIPlayer ? rap_P_head : rap_C_head;
    headAnim = gCellAnimManager->createCellAnim(0, headAnimID);

    bodyAnim->setBase(footAnim, 0, false);
    headAnim->setBase(bodyAnim, 4, true);
    eyeAnim->setBase(headAnim, 0, false);
    mouthAnim->setBase(headAnim, 1, false);

    footAnim->setLayer(1000);
    bodyAnim->setLayer(999);
    headAnim->setLayer(998);
    eyeAnim->setLayer(997);
    mouthAnim->setLayer(996);

    footAnim->goToAnimEnd();
    bodyAnim->goToAnimEnd();
    headAnim->goToAnimEnd();
    eyeAnim->goToAnimEnd();
    mouthAnim->goToAnimEnd();

    if (amIPlayer) {
        footAnim->setPosX(200.0f);
    }
    else {
        footAnim->setPosX(-200.0f);
    }

    if (amIPlayer) {
        CExScene::fn_80009A40(true);
        CExScene::fn_80009950(footAnim->getPosX(), footAnim->getPosY() - 100.0f);
    }

    throughStareTimer = 0;
}

void CSceneRap::CharaRapper::fn_8005193C(void) {
    if (throughStareTimer != 0) {
        bodyAnim->setEnabled(true);
        headAnim->setEnabled(true);
        eyeAnim->setEnabled(false);
        mouthAnim->setEnabled(false);
    }
    else if (footAnim->getAnimID() == rap_P_cough) {
        bodyAnim->setEnabled(false);
        headAnim->setEnabled(false);
        eyeAnim->setEnabled(false);
        mouthAnim->setEnabled(false);
    }
    else {
        bodyAnim->setEnabled(true);
        headAnim->setEnabled(true);
        eyeAnim->setEnabled(true);
        mouthAnim->setEnabled(true);
    }
}

void CSceneRap::CharaRapper::fn_800519D4(void) {
    if ((footAnim->getAnimID() != rap_P_cough) || !footAnim->getPlaying()) {
        footAnim->switchAnim(rap_foot_beat);
        footAnim->playFromBegin();
    }
}

void CSceneRap::CharaRapper::fn_80051A2C(s32 type, s32 unk) {
    if ((footAnim->getAnimID() != rap_P_cough) || !footAnim->getPlaying() || (unk != 2)) {
        switch (type) {
        case 0: {
            footAnim->setAnim(rap_foot_D);
            bodyAnim->setAnim(rap_body_D);
            mouthAnim->setAnim(rap_mouth_D);
            if (eyeAnim->getAnimID() != rap_eye_D_arrange) {
                eyeAnim->setAnim(rap_eye_D);
            }
        } break;

        case 1: {
            footAnim->setAnim(rap_foot_MD);
            bodyAnim->setAnim(rap_body_MD);
            eyeAnim->setAnim(rap_eye_MD);
            mouthAnim->setAnim(scene->mUnk1BC ? rap_mouth_MD_ura : rap_mouth_MD);
        } break;

        case 2: {
            footAnim->setAnim(rap_foot_H);
            bodyAnim->setAnim(rap_body_H);
            eyeAnim->setAnim(rap_eye_H);
            mouthAnim->setAnim(scene->mUnk1BC ? rap_mouth_H_ura : rap_mouth_H);
        } break;

        case 3: {
            footAnim->setAnim(rap_foot_S);
            bodyAnim->setAnim(rap_body_S);
            eyeAnim->setAnim(rap_eye_S);
            mouthAnim->setAnim(rap_mouth_S);
        } break;
        
        default:
            break;
        }

        if (throughStareTimer != 0) {
            fn_80051D34();
        }
    }
}

void CSceneRap::CharaRapper::fn_80051BB8(s32 type) {
    if ((footAnim->getAnimID() != rap_P_cough) || !footAnim->getPlaying()) {
        switch (type) {
        case 0: {
            footAnim->setAnim(rap_foot_D_B);
            bodyAnim->setAnim(rap_body_D_B);
            eyeAnim->setAnim(rap_eye_D_B);
            mouthAnim->setAnim(rap_mouth_D_B);
        } break;

        case 1: {
            footAnim->setAnim(rap_foot_MD_B);
            bodyAnim->setAnim(rap_body_MD_B);
            eyeAnim->setAnim(rap_eye_MD_B);
            mouthAnim->setAnim(rap_mouth_MD_B);
        } break;

        case 2: {
            footAnim->setAnim(rap_foot_H_B);
            bodyAnim->setAnim(rap_body_H_B);
            eyeAnim->setAnim(rap_eye_H_B);
            mouthAnim->setAnim(rap_mouth_H_B);
        } break;

        case 3: {
            footAnim->setAnim(rap_foot_S_B);
            bodyAnim->setAnim(rap_body_S_B);
            eyeAnim->setAnim(rap_eye_S_B);
            mouthAnim->setAnim(rap_mouth_S_B);
        } break;
        
        default:
            break;
        }

        if (throughStareTimer != 0) {
            fn_80051D34();
        }
    }
}

void CSceneRap::CharaRapper::fn_80051D00(void) {
    fn_80051D34();
    throughStareTimer = 120;
}

void CSceneRap::CharaRapper::fn_80051D34(void) {
    u16 animID = bodyAnim->getAnimID();
    if ((animID == rap_body_D) || (animID == rap_body_D_B)) {
        headAnim->switchAnim(rap_C_head_through_D);
    }
    else if ((animID == rap_body_MD) || (animID == rap_body_MD_B)) {
        headAnim->switchAnim(rap_C_head_through_MD);
    }
    else if ((animID == rap_body_H) || (animID == rap_body_H_B)) {
        headAnim->switchAnim(rap_C_head_through_H);
    }
    else if ((animID == rap_body_S) || (animID == rap_body_S_B)) {
        headAnim->switchAnim(rap_C_head_through_S);
    }
}

void CSceneRap::CharaGirl::fn_80051DAC(CCellAnim *carAnim) {
    footAnim = gCellAnimManager->createCellAnim(0, rap_girl_foot_MD);
    bodyAnim = gCellAnimManager->createCellAnim(0, rap_girl_body_MD);
    eyeAnim = gCellAnimManager->createCellAnim(0, rap_girl_eye_MD);
    mouthAnim = gCellAnimManager->createCellAnim(0, rap_girl_mouth_MD);

    footAnim->setBase(carAnim, 0, false);
    bodyAnim->setBase(footAnim, 4, true);
    eyeAnim->setBase(bodyAnim, 0, false);
    mouthAnim->setBase(bodyAnim, 1, false);

    footAnim->setLayer(2000);
    bodyAnim->setLayer(1999);
    eyeAnim->setLayer(1998);
    mouthAnim->setLayer(1997);

    footAnim->goToAnimEnd();
    bodyAnim->goToAnimEnd();
    eyeAnim->goToAnimEnd();
    mouthAnim->goToAnimEnd();
}

void CSceneRap::CharaGirl::fn_80051ED0(void) {
    footAnim->switchAnim(rap_girl_foot_beat);
    footAnim->playFromBegin();
}

void CSceneRap::CharaGirl::fn_80051F0C(s32 type, bool unk) {    
    switch (type) {
    case 0: {
        footAnim->switchAnim(rap_girl_foot_D);
        bodyAnim->switchAnim(rap_girl_body_D);
        eyeAnim->switchAnim(rap_girl_eye_D);
        mouthAnim->switchAnim(rap_girl_mouth_D);
    } break;

    case 1: {
        footAnim->switchAnim(rap_girl_foot_MD);
        bodyAnim->switchAnim(rap_girl_body_MD);
        eyeAnim->switchAnim(rap_girl_eye_MD);
        mouthAnim->switchAnim(unk ? rap_girl_mouth_MD_ura : rap_girl_mouth_MD);
    } break;

    case 2: {
        footAnim->switchAnim(rap_girl_foot_H);
        bodyAnim->switchAnim(rap_girl_body_H);
        eyeAnim->switchAnim(rap_girl_eye_H);
        mouthAnim->switchAnim(unk ? rap_girl_mouth_H_ura : rap_girl_mouth_H);
    } break;

    case 3: {
        footAnim->switchAnim(rap_girl_foot_S);
        bodyAnim->switchAnim(rap_girl_body_S);
        eyeAnim->switchAnim(rap_girl_eye_S);
        mouthAnim->switchAnim(rap_girl_mouth_S);
    } break;
    
    default:
        break;
    }

    footAnim->playFromBegin();
    bodyAnim->playFromBegin();
    eyeAnim->playFromBegin();
    mouthAnim->playFromBegin();
}

void CSceneRap::CharaGirl::fn_80052070(s32 type) {
    switch (type) {
    case 0: {
        footAnim->switchAnim(rap_girl_foot_D_B);
        bodyAnim->switchAnim(rap_girl_body_D_B);
        eyeAnim->switchAnim(rap_girl_eye_D_B);
        mouthAnim->switchAnim(rap_girl_mouth_D_B);
    } break;

    case 1: {
        footAnim->switchAnim(rap_girl_foot_MD_B);
        bodyAnim->switchAnim(rap_girl_body_MD_B);
        eyeAnim->switchAnim(rap_girl_eye_MD_B);
        mouthAnim->switchAnim(rap_girl_mouth_MD_B);
    } break;

    case 2: {
        footAnim->switchAnim(rap_girl_foot_H_B);
        bodyAnim->switchAnim(rap_girl_body_H_B);
        eyeAnim->switchAnim(rap_girl_eye_H_B);
        mouthAnim->switchAnim(rap_girl_mouth_H_B);
    } break;

    case 3: {
        footAnim->switchAnim(rap_girl_foot_S_B);
        bodyAnim->switchAnim(rap_girl_body_S_B);
        eyeAnim->switchAnim(rap_girl_eye_S_B);
        mouthAnim->switchAnim(rap_girl_mouth_S_B);
    } break;
    
    default:
        break;
    }

    footAnim->playFromBegin();
    bodyAnim->playFromBegin();
    eyeAnim->playFromBegin();
    mouthAnim->playFromBegin();
}

void CSceneRap::CharaGirl::fn_800521A8(void) {
    bodyAnim->setAnim(rap_girl_body_blow_loop);
    bodyAnim->prepareAnim(rap_girl_body_blow_loop, NULL);
    bodyAnim->prepareAnim(rap_girl_body_blow_loop, NULL);
    bodyAnim->prepareAnim(rap_girl_body_blow_end, NULL);
}

void CSceneRap::_18(void) {
    this->CExScene::_18();
}
