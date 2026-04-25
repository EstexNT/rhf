#ifndef GAME_GRADING_SCENEGRADING_HPP
#define GAME_GRADING_SCENEGRADING_HPP

#include <revolution/types.h>

#include "ExScene.hpp"

#include "CellAnim.hpp"

#include "CheckPointManager.hpp"

namespace Grading {

class CMyFlow; // Forward-declaration
class CMyLayout; // Forward-declaration

extern s32 sceneVer;

void fn_8000C5F4(bool);

} // namespace Grading

class CSceneGrading : public CExScene {
    friend class Grading::CMyFlow;
    friend class Grading::CMyLayout;
    
public:
    virtual ~CSceneGrading(void) {}
    virtual void _10(void);
    virtual void _14(void);
    virtual void _18(void);
    virtual void _1C(void);
    virtual void _20(void);
    virtual void _28(void);

    CSceneGrading(void) {}

    SCENE_DECL_CREATE_FN()

    static void fn_8000C348(void);

private:
    Grading::CMyLayout *mLayout;
    EGrade mGrade;
    bool mBut;
};

#endif