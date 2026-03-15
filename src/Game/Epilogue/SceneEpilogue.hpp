#ifndef GAME_EPILOGUE_SCENEEPILOGUE_HPP
#define GAME_EPILOGUE_SCENEEPILOGUE_HPP

#include <revolution/types.h>

#include "ExScene.hpp"

#include "Epilogue/MyLayout.hpp"

namespace Epilogue {

class CMyFlow; // Forward-declaration
class CMyLayout; // Forward-declaration

extern s32 sceneVer;

void fn_8000B820(const char *name, s32 version);

} // namespace Epilogue

class CSceneEpilogue : public CExScene {
    friend class Epilogue::CMyFlow;
    friend class Epilogue::CMyLayout;
    
public:
    virtual ~CSceneEpilogue(void) {}
    virtual void _10(void);
    virtual void _14(void);
    virtual void _18(void);
    virtual void _1C(void);
    virtual void _20(void);
    virtual void _28(void);

    CSceneEpilogue(void) {}

    SCENE_DECL_CREATE_FN()

    static void fn_8000B518(void);
};

#endif