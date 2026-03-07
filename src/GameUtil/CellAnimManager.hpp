#ifndef GAMEUTIL_CELLANIMMANAGER_HPP
#define GAMEUTIL_CELLANIMMANAGER_HPP

#include <revolution/types.h>

#include <revolution/GX.h>
#include <revolution/TPL.h>
#include <revolution/MEM.h>
#include <revolution/MTX.h>
#include <revolution/SC.h>

#include "Singleton.hpp"

#include "CellAnim.hpp"
#include "CellAnimStr.hpp"

class CCellAnimManager : public TSingleton<CCellAnimManager> {
public:
    typedef void (*DrawSetupFn)();
    typedef void (*DrawRestoreFn)();
    typedef void (*BaseUpdateCallbackFn)();

    virtual void _08(void);
    virtual ~CCellAnimManager(void);
    virtual void _10(s32 cellAnimCount);
    virtual void _14(void);
    virtual void _18(void);
    virtual void _1C(DrawSetupFn, DrawRestoreFn);
    virtual void _20(s32, DrawSetupFn, DrawRestoreFn);
    virtual void _24(s32, DrawSetupFn, DrawRestoreFn);

    CCellAnimManager(void);

    bool fn_801DB558(u8 bankID); // bankIsActive
    void fn_801DB568(void *brcadAddr, void *tplAddr, u8 bankID); // registBank
    void fn_801DB86C(GXTexObj *texObj, s32 width, s32 height, f32 scaleX, f32 scaleY, u8 bankID); // createBankTex
    void fn_801DB9C0(GXTexObj *texObj, u8 bankID); // createBankScreen
    void fn_801DBA98(u8 bankID); // endBank
    u16 fn_801DBB58(CCellAnim *cellAnim); // getCurrAnimFrames
    CellAnim_Anim *fn_801DBC5C(CCellAnim *cellAnim); // getCurrentAnim
    CellAnim_AnimKey *fn_801DBC7C(CCellAnim *cellAnim); // getCurrentKey
    CellAnim_Cell *fn_801DBD38(CCellAnim *cellAnim); // getCurrentCell
    u16 fn_801DBE04(u8 bankID); // getBankChrWidth
    u16 fn_801DBE14(u8 bankID); // getBankChrHeight
    void fn_801DBE24(CCellAnim *cellAnim); // destroyCellAnim
    void fn_801DB3D8(u8 bankID, CellAnim_CellOBJ *obj, BOOL linearFilter, s32 chrIndex); // loadChrForDraw
    CCellAnim *fn_801DBE7C(u8 bankID, u16 animID); // createCellAnim
    void DONT_INLINE fn_801DBFA0(CCellAnim *cellAnim); // endCellAnim
    void fn_801DC068(u8 bankID); // endCellAnimByBank
    void fn_801DC0D4(CCellAnim *cellAnim); // layerReorder
    void fn_801DC164(CCellAnim *baseCell); // setBaseDefault
    CCellAnim *fn_801DC16C(void); // getBaseDefault
    void fn_801DC174(BaseUpdateCallbackFn callback); // setBaseCallback
    void fn_801DC17C(bool update, u16 tempo); // setTempoUpdate

private:
    void fn_801DB28C(void); // drawSetupDefault

    void insertCellAnim(CCellAnim *cellAnim) {
        CCellAnim *current = mCellAnimHead;
        CCellAnim *prev = NULL;

        while (current != NULL) {
            if (cellAnim->getLayer() < current->getLayer()) {
                prev = current;
                current = current->getNext();
            }
            else {
                break;
            }
        }

        if (current == mCellAnimHead) {
            mCellAnimHead = cellAnim;
        }

        if (current != NULL) {
            cellAnim->insertBefore(current);
        }
        else {
            cellAnim->insertAfter(prev);
        }
    }

    bool containsCellAnim(CCellAnim *cellAnim) {
        CCellAnim *current = mCellAnimHead;
        while (current != NULL) {
            if (current == cellAnim) {
                return true;
            }
            current = current->getNext();
        }
        return false;
    }

    CellAnim_AnimKey* lol(CCellAnim *cellAnim) {
        bool isReverse = cellAnim->getPlaybackReverse();

        CellAnim_Anim *anim = &mBank[cellAnim->getBankID()].animArr[cellAnim->getAnimID()];

        f32 currentFrame = 0.0f;
        f32 lastFrame = cellAnim->getFrame();

        for (s32 i = 0; i < anim->keyCount; i++) {
            s32 keyIdx = isReverse ? ((anim->keyCount - 1) - i) : i;

            currentFrame += anim->keyArr[keyIdx].frameCount;
            if (currentFrame > lastFrame)
                return &anim->keyArr[keyIdx];
        }

        return &anim->keyArr[isReverse ? 0 : (anim->keyCount - 1)];
    }

private:
    enum { BANK_COUNT = 0x100 };

    CellAnim_Bank mBank[BANK_COUNT];
    CCellAnim *mCellAnimHead;

    CCellAnim *mCellAnimBase;
    BaseUpdateCallbackFn mCellAnimBaseCallback;

    u8 *mHeapStart;
    MEMiHeapHead *mHeap;

    bool mCellAnimTempoUpdate;
    u16 mCellAnimTempo;
};

extern CCellAnimManager *gCellAnimManager;

#endif
