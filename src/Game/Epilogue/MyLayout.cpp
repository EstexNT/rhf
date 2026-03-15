#include "Epilogue/MyLayout.hpp"

#include "Epilogue/SceneEpilogue.hpp"

#include "LayoutManager.hpp"

#include "MessageManager.hpp"

#include "CheckPointManager.hpp"

#include <cstdio>

// TODO
extern "C" void fn_801D8A5C(nw4r::lyt::TextBox *, f32, f32);

static const char layoutFile_epilogue[] = "epilogue.brlyt";

DECL_SECTION(".sdata") static const char *layoutFileTable[] = { layoutFile_epilogue, NULL };
// TODO: ^^ hack!

static const wchar_t *sMessageHI;
static const wchar_t *sMessageOK;
static const wchar_t *sMessageNG;

void Epilogue::CMyLayout::_10(void) {
    nw4r::lyt::MultiArcResourceAccessor *resAccessor = gLayoutManager->getResAccessor();

    u32 layoutBinSize;
    void *layoutBin = gLayoutManager->getResAccessor()->GetResource(0, layoutFileTable[0], &layoutBinSize);

    buildLayout(layoutBin, resAccessor);

    gMessageManager->fn_80088474(getLayout()->GetRootPane());

    nw4r::lyt::TextBox *textBox = static_cast<nw4r::lyt::TextBox *>(
        getLayout()->GetRootPane()->FindPaneByName("T_Message_00")
    );

    textBox->SetString(
        (gCheckPointManager->getUnk2FC() == 0) ? sMessageHI :
        (gCheckPointManager->getUnk2FC() == 1) ? sMessageOK : 
        sMessageNG
    );

    fn_801D8A5C(textBox, 32.0f, 38.0f);

    this->CLayout::_10();
}

void Epilogue::fn_8000B398(const char *mesgIDStr) {
    sMessageHI = gMessageManager->getString(mesgIDStr, eMesgSource_Comment);
}

void Epilogue::fn_8000B3D4(const char *mesgIDStr) {
    sMessageOK = gMessageManager->getString(mesgIDStr, eMesgSource_Comment);
}

void Epilogue::fn_8000B410(const char *mesgIDStr) {
    sMessageNG = gMessageManager->getString(mesgIDStr, eMesgSource_Comment);
}

Epilogue::CMyLayout::~CMyLayout(void) {
    _14();
}
