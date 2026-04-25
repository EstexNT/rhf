#ifndef GAME_GRADING_MYLAYOUT_HPP
#define GAME_GRADING_MYLAYOUT_HPP

#include <revolution/types.h>

#include "Layout.hpp"

#include "Grading/SceneGrading.hpp"

#include "GameManager.hpp"

namespace Grading {

void fn_8000C120(const char *mesgIDStr);

class CMyLayout : public CLayout {
public:
    virtual ~CMyLayout(void);
    virtual void _10(void);

    CMyLayout(void) {
        setAnimationCount(1);
        
        mScene = gGameManager->getCurrentScene<CSceneGrading>();
    }

    void fn_8000C088(void);
    void fn_8000C0B4(void);
    void fn_8000C0F4(void);
    void fn_8000C15C(void);

private:
    CSceneGrading *mScene;

    nw4r::lyt::Pane *mCaptionWnd;
    nw4r::lyt::TextBox *mCaptionText;

    nw4r::lyt::TextBox *mCommentText[3];

    nw4r::lyt::TextBox *mFollowText;

    nw4r::lyt::Pane *mHIPane;
    nw4r::lyt::Pane *mOKPane;
    nw4r::lyt::Pane *mNGPane;

    nw4r::lyt::Pane *mMedalPane;
    nw4r::lyt::Pane *mButPane;

    nw4r::lyt::Pane *mFollowPane;
};

} // namespace Grading

#endif
