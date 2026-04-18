#include "code_8008E430.hpp"

#include "ExScene.hpp"

#include "ExController.hpp"

#include "InputCheckManager.hpp"

void fn_8008E430(void) {
    if (!CExScene::fn_8000A6B4()) {
        CExController *controllerP1 = gControllerManager->getController<CExController>(0);
        CExController *controllerP2 = gControllerManager->getController<CExController>(1);
        CExController *controllerP3 = gControllerManager->getController<CExController>(2);
        CExController *controllerP4 = gControllerManager->getController<CExController>(3);

        if (controllerP1->fn_8008CDAC()) {
            gInputCheckManager->fn_801E923C(INPUT_PX(eInputType_TriggerUp, 4));
        }
        if (controllerP1->fn_8008CE98()) {
            gInputCheckManager->fn_801E923C(INPUT_PX(eInputType_TriggerDown, 4));
        }

        if (controllerP2->fn_8008CDAC()) {
            gInputCheckManager->fn_801E923C(INPUT_PX(eInputType_TriggerLeft, 4));
        }
        if (controllerP2->fn_8008CE98()) {
            gInputCheckManager->fn_801E923C(INPUT_PX(eInputType_TriggerRight, 4));
        }

        if (controllerP3->fn_8008CDAC()) {
            gInputCheckManager->fn_801E923C(INPUT_PX(eInputType_TriggerA, 4));
        }
        if (controllerP3->fn_8008CE98()) {
            gInputCheckManager->fn_801E923C(INPUT_PX(eInputType_TriggerB, 4));
        }

        if (controllerP4->fn_8008CDAC()) {
            gInputCheckManager->fn_801E923C(INPUT_PX(eInputType_Trigger_6, 4));
        }
        if (controllerP4->fn_8008CE98()) {
            gInputCheckManager->fn_801E923C(INPUT_PX(eInputType_TriggerHome, 4));
        }

        gInputCheckManager->fn_801E8118();
    }
}
