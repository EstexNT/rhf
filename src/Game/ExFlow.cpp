#include "ExFlow.hpp"

#include "Mem.hpp"

#include "SceneManager.hpp"
#include "GameManager.hpp"
#include "CheckPointManager.hpp"
#include "MyCanvas.hpp"

#include "ExScene.hpp"

#include "ExFlowDecl.hpp"

CExFlow::CExFlow(const TickFlowCode *code, f32 initRest) :
    CTickFlow(code, initRest)
{}

TICKFLOW_IMPL_CREATE_FN(CExFlow)

CExFlow::~CExFlow(void) {}

// TODO: many many commands
bool CExFlow::_1C(u32 opcode, u32 arg0, const s32 *args) {
    switch (opcode) {
        case TF_SET_SCENE: {
            if (arg0 == 0) {
                gSceneManager->fn_80089FE0(static_cast<ESceneID>(args[0]), reinterpret_cast<const TickFlowCode *>(args[1]));
            }
            else if (arg0 == 1) {
                gSceneManager->setUnk404(true);
            }
        } break;
        case TF_SET_SCENE_VER: {
            gSceneManager->fn_8008A4DC(static_cast<ESceneID>(args[0]), args[1]);
        } break;
        case TF_SCENE_ASSETS: {
            if (arg0 == 0) {
                gSceneManager->fn_8008A704(static_cast<ESceneID>(args[0]));
            }
            else if (arg0 == 1) {
                gSceneManager->fn_8008A82C(static_cast<ESceneID>(args[0]));
            }
        } break;
        case TF_CHECK_SCENE_HIST: {
            if (arg0 == 0) {
                mCondvar = gSceneManager->fn_8008B0FC(args[0], args[1]);
            }
            else if (arg0 == 1) {
                mCondvar = gSceneManager->fn_8008B118(static_cast<ESceneID>(args[0]));
            }
        } break;
        case TF_GET_SCENE_RUNNING: {
            if (gGameManager->getCurrentScene()->getState() == CScene::eState_Active) {
                mCondvar = true;
            }
            else {
                mCondvar = false;
            }
        } break;

        case TF_CHECKPOINT_SET_CRITERIA: {
            gCheckPointManager->setUnkC5(args[0]);
        } break;
        case TF_CHECKPOINT_ENABLE_SCORING: {
            gCheckPointManager->setUnkDD(args[0]);
        } break;
        case TF_11B: {
            gCheckPointManager->setUnkCC(args[0]);
            gCheckPointManager->setUnkD0(args[0]);
        } break;

        case TF_125: {
            if (arg0 == 0) {
                gMyCanvasManager->fn_8007BF6C(args[0], 
                    static_cast<u32>(args[1]) / 256.0f, static_cast<u32>(args[2]) / 256.0f);
            }
            else if (arg0 == 1) {
                gMyCanvasManager->fn_8007C000(args[0], args[1], (u8)args[2], args[3], 
                    static_cast<u32>(args[4]) / 256.0f, static_cast<u32>(args[5]) / 256.0f);
            }
            else if (arg0 == 2) {
                gMyCanvasManager->fn_8007C200(args[0]);
            }
        } break;

        case TF_UPDATE_PERFECT_STATUS: {
            CExScene::updatePerfectStatus(args[0] != 0);
        } break;

        case TF_LOAD_SND_GROUP: {
            fn_8008364C(args[0], static_cast<ESoundHeap>(arg0));
        } break;
        case TF_CLEAR_SND_HEAP: {
            fn_80083668(static_cast<ESoundHeap>(arg0));
        } break;
        case TF_RESET_SND_GROUP_HEAP: {
            fn_800836C0(static_cast<ESoundHeap>(arg0));
        } break;
        case TF_SND_LOADING: {
            if (arg0 == 0) {
                fn_800836E0(args[0]);
            }
            else if (arg0 == 1) {
                mCondvar = lbl_80320440;
            }
        } break;

        case TF_REMIX8_MASK: {
            if (arg0 == 0) {
                CExScene::fn_8000A084();
            }
            else if (arg0 == 1) {
                CExScene::fn_8000A0A4();
            }
            else if (arg0 == 2) {
                mCondvar = CExScene::fn_8000A0EC();
            }
            else if (arg0 == 3) {
                CExScene::fn_8000A0F8();
            }
            else if (arg0 == 4) {
                CExScene::fn_8000A1D4(args[0]);
            }
            else if (arg0 == 5) {
                CExScene::fn_8000A1E0(args[0]);
            }
        } break;

        case TF_141: {
            if (arg0 == 0) {
                mCondvar = SCGetAspectRatio() == args[0];
            }
        } break;

        default: {
            return CTickFlow::_1C(opcode, arg0, args);
        }
    }
    return false;
}

void CExFlow::_14(void) {
    this->~CExFlow();
}
