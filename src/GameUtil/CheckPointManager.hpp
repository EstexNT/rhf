#ifndef GAMEUTIL_CHECKPOINTMANAGER_HPP
#define GAMEUTIL_CHECKPOINTMANAGER_HPP

#include <revolution/types.h>
#include "Singleton.hpp"

// TODO: horribly underdocumented! macros are also kinda trashy
struct GradingCriteria {
    const void *mesgPositive; // either char * for message ID, or wchar_t * for string
    const void *mesgNegative; // either char * for message ID, or wchar_t * for string
    u16 unk08;
    u16 unk0A;
    u16 unk0C;
    u16 flags;

    bool checkUnk08(void) {
        if ((unk08 & 0x8000) && ((unk08 & ~0x8000) > 100)) {
            return true;
        }
        return false;
    }
};

#define GRADE_CRITERIA_FLAG_NONE ((u16)(0))
#define GRADE_CRITERIA_FLAG_UNK0 ((u16)(1 << 0))
#define GRADE_CRITERIA_FLAG_UNK1 ((u16)(1 << 1))
#define GRADE_CRITERIA_FLAG_END ((u16)(1 << 15))

#define GRADE_CRITERIA_TABLE_BEGIN(tableName) \
    GradingCriteria tableName[] = {

#define GRADE_CRITERIA_TABLE_ENTRY(unk00, unk04, unk08, unk0A, unk0C, flags) \
    { (unk00), (unk04), (unk08), (unk0A), (unk0C), (flags) },

#define GRADE_CRITERIA_TABLE_END()                   \
    { NULL, NULL, 0, 0, 0, GRADE_CRITERIA_FLAG_END } \
    };

enum ECheckInputType {
    eCheckInputType_Hit,
    eCheckInputType_Miss,
    eCheckInputType_Through,
};

class CCheckPointManager : public TSingleton<CCheckPointManager> {
public:

    virtual void _08(void);
    virtual ~CCheckPointManager(void);
    virtual void _10(void);
    virtual void _14(void);

    CCheckPointManager(void);

    void fn_801EAE20(void);
    void fn_801EAE6C(GradingCriteria *);
    void fn_801EAEA4(void);

    void fn_801EAF2C(u8, ECheckInputType);
    void fn_801EB00C(u8, ECheckInputType);

    void fn_801EB10C(f32);
    void fn_801EB11C(void);

    void fn_801EB130(void);

    u8 fn_801EB7A8(void);
    u32 fn_801EB7B0(void);

    wchar_t *fn_801EB7D0(s32);
    wchar_t *fn_801EB7E0(void);
    wchar_t *fn_801EB7F8(void);

    u8 fn_801EB800(void);

    s32 fn_801EB808(s32);
    s32 fn_801EB8FC(s32);
    s32 fn_801EB9F0(s32);
    s32 fn_801EBAE4(s32);

    f32 fn_801EBBD8(s32);
    f32 fn_801EBE00(s32);
    f32 fn_801EC028(s32);

    void fn_801EC250(s32, wchar_t *);
    void fn_801EC260(wchar_t *);
    void fn_801EC268(wchar_t *);

    static wchar_t fn_801EC270(wchar_t c);

    void setUnk2FC(u32 arg1) {
        unk2FC = arg1;
    }
    s32 getUnk2FC(void) const {
        return unk2FC;
    }
    void setUnkC4(u8 arg0) {
        unkC4 = arg0;
    }
    void setUnkC5(u8 arg0) {
        unkC5 = arg0;
    }
    u8 getUnkC5(void) {
        return unkC5;
    }

    void setUnkCC(s32 arg0) {
        unkCC = arg0;
    }
    void setUnkD0(u32 arg0) {
        unkD0 = arg0;
    }

    void setUnkDD(bool unk) { unkDD = unk; }
    u8 getUnkDD(void) const { return unkDD; }

    bool doUnkCheck(u16 arg0, u16 arg1, f32 arg2) {
        s32 temp1 = arg0 & ~0x8000;
        if (arg0 & 0x8000) {
            return arg2 < temp1;
        }
        else {
            return arg1 < temp1;
        }
    }

    u32 getUnk2FCGrade(bool arg0, bool arg1) {
        u32 temp;
        
        if (arg0) {
            temp = 0;
        }
        else {
            temp = 1;
            if (arg1) {
                temp = 2;
            }
        }

        return temp;
    }
private:

    struct GradingState {
        u16 unk0;
        u16 unk2;
        u16 unk4;
        u16 unk6;
        f32 unk8;
        f32 unkC;
        f32 unk10;

        void reset(void) {
            unk0 = 0;
            unk2 = 0;
            unk4 = 0;
            unk6 = 0;
        }
    };

    GradingState unk04[8];
    GradingCriteria *unkA4[8];
    u8 unkC4;
    u8 unkC5;
    s32 unkC8;
    s32 unkCC;
    u32 unkD0;
    f32 unkD4;
    f32 unkD8;
    u8 unkDC;
    u8 unkDD;
    u8 unkDE;
    u8 unkDF;
    wchar_t unkE0[4][64 + 1];
    wchar_t *unk2E8[4];
    wchar_t *unk2F8;
    u32 unk2FC;
};

extern CCheckPointManager *gCheckPointManager;

#endif
