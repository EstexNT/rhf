#ifndef GAME_EPILOGUE_MYFLOW_HPP
#define GAME_EPILOGUE_MYFLOW_HPP

#include <revolution/types.h>

#include "ExFlow.hpp"

#include "Epilogue/SceneEpilogue.hpp"

#include "GameManager.hpp"

namespace Epilogue {

class CMyFlow : public CExFlow {
public:
    virtual ~CMyFlow(void);
    virtual void _14(void);
    virtual bool _1C(u32 opcode, u32 arg0, const s32 *args);

    CMyFlow(const TickFlowCode *code, f32 initRest) :
        CExFlow(code, initRest)
    {
        mScene = gGameManager->getCurrentScene<CSceneEpilogue>();
    }

    TICKFLOW_DECL_CREATE_FN()

private:
    CSceneEpilogue *mScene;
};

} // namespace Epilogue

#endif
