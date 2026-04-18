#include "Epilogue/SceneEpilogue.hpp"

#include "Epilogue/MyLayout.hpp"
#include "Epilogue/MyFlow.hpp"

#include "CellAnim.hpp"

#include "FileManager.hpp"
#include "CellAnimManager.hpp"
#include "CheckPointManager.hpp"
#include "LayoutManager.hpp"
#include "TickFlowManager.hpp"

#include "TPL.hpp"

static char lbl_8032A378[256];

namespace Epilogue {

s32 sceneVer;

} // namespace Epilogue

SCENE_IMPL_CREATE_FN(CSceneEpilogue)

void CSceneEpilogue::fn_8000B518(void) {
    fn_80008EFC();

    fn_801D369C(eHeapGroup_SceneAsset);
    if (gFileManager->fn_801D42E0(52)) {
        gFileManager->fn_801D3F94(52, lbl_8032A378);
        gFileManager->fn_801D3F94(92, "content2/layout/layout_epilogue.szs");
    }
    fn_801D3644();
}

void CSceneEpilogue::_10(void) {
    fn_8000B518();
}

void CSceneEpilogue::_14(void) {
    this->CExScene::_14();

    void *epilogue_brcadAddr = gFileManager->fn_801D4270(52, "./epilogue.brcad");

    u32 tplLen      = gFileManager->fn_801D422C(52, "./cellanim.tpl");
    void *tplAddr   = gFileManager->fn_801D4270(52, "./cellanim.tpl");

    UserTPLBind(tplAddr);
    DCStoreRange(tplAddr, tplLen);

    gCellAnimManager->registBank(epilogue_brcadAddr, tplAddr, 0);

    CCellAnim *anim = gCellAnimManager->createCellAnim(0, 0);
    anim->setPlaying(false);

    s32 frame;
    if (gCheckPointManager->getUnk2FC() == 0) {
        frame = 0;
    }
    else if (gCheckPointManager->getUnk2FC() == 1) {
        frame = 1;
    }
    else {
        frame = 2;
    }

    anim->setFrame(frame);

    gLayoutManager->_20(1);
    gLayoutManager->_24(92, ""); // layout_epilogue

    gLayoutManager->fn_801D6AEC(1);
    gLayoutManager->registerLayout<Epilogue::CMyLayout>(); // Index 0

    gTickFlowManager->registerFlow<Epilogue::CMyFlow>();

    fn_801D3638(300);
}

void CSceneEpilogue::_28(void) {}

void CSceneEpilogue::_1C(void) {
    this->CExScene::_1C();
}

void CSceneEpilogue::_20(void) {
    gCellAnimManager->endBank(0);
    gCellAnimManager->endCellAnimByBank(0);

    gFileManager->fn_801D41CC(52);
    gFileManager->fn_801D41CC(92);

    this->CExScene::_20();
}

void Epilogue::fn_8000B820(const char *name, s32 version) {
    sprintf(lbl_8032A378, "content2/cellanim/%s/ver%d/cellanim_epilogue.szs", name, version);
}

void CSceneEpilogue::_18(void) {
    this->CExScene::_18();
}
