#include "CheckPointManager.hpp"

#include <cstring>
#include <cwchar>

#include "TickFlowManager.hpp"
#include "InputCheckManager.hpp"

CCheckPointManager::CCheckPointManager(void) {

}

CCheckPointManager::~CCheckPointManager(void) {
    _08();
}

void CCheckPointManager::_10(void) {

}

void CCheckPointManager::_08(void) {

}

// not matching (instruction reordering at start)
void CCheckPointManager::_14(void) {
    static wchar_t *empty = L"";

    unkC4 = 0;
    fn_801EAEA4();
    unkC5 = 0;
    unkCC = 0;
    unkD0 = 0;
    fn_801EB11C();
    unkDD = 0;

    for (s32 i = 0; i < ARRAY_LENGTH(unk2E8); i++) {
        fn_801EC250(i, empty);
    }
    fn_801EC268(empty);
}

void CCheckPointManager::fn_801EAE20(void) {
    if (unkD8 > 0.0f) {
        unkD8 -= gTickFlowManager->fn_801E2698();
    }
}

void CCheckPointManager::fn_801EAE6C(GradingCriteria *criteria) {
    unkC4 = 0;
    while (!(criteria->flags & GRADE_CRITERIA_FLAG_END)) {
        unkA4[unkC4++] = criteria++;
    }
}

void CCheckPointManager::fn_801EAEA4(void) {
    for (s32 i = 0; i < ARRAY_LENGTH(unk04); i++) {
        unk04[i].reset();
    }
}

void CCheckPointManager::fn_801EAF2C(u8 arg0, ECheckInputType type) {
    if (!unkDD) {
        return;
    }

    if (type == eCheckInputType_Through) {
        if ((unkD8 > 0.0f) && (unkDC == arg0)) {
            return;
        }
        unkD8 = unkD4;
        unkDC = arg0;
    }
    else {
        unkD8 = 0.0f;
    }

    if (type == eCheckInputType_Through) {
        if ((unkCC > 0) && (!(unkA4[arg0]->flags & GRADE_CRITERIA_FLAG_UNK1))) {
            unkCC--;
            return;
        }
    }
    
    unk04[arg0].unk0++;
    switch (type) {
        case eCheckInputType_Hit:
            unk04[arg0].unk2++;
            break;
        case eCheckInputType_Miss:
            unk04[arg0].unk4++;
            break;
        case eCheckInputType_Through:
            unk04[arg0].unk6++;
            break;
    }
}

void CCheckPointManager::fn_801EB00C(u8 arg0, ECheckInputType type) {
    if (!unkDD) {
        return;
    }

    gInputCheckManager->fn_801E9488(0);
    switch (type) {
        case eCheckInputType_Hit:
            unk04[arg0].unk2--;
            unk04[arg0].unk0--;
            break;
        case eCheckInputType_Miss:
            unk04[arg0].unk4--;
            unk04[arg0].unk0--;
            break;
    }

    if ((unkCC > 0) && (!(unkA4[arg0]->flags & GRADE_CRITERIA_FLAG_UNK1))) {
        unkCC--;
    }
    else {
        unk04[arg0].unk6++;
        unk04[arg0].unk0++;
    }
}

void CCheckPointManager::fn_801EB10C(f32 arg0) {
    unkD4 = arg0;
    unkD8 = 0.0f;
}

void CCheckPointManager::fn_801EB11C(void) {
    fn_801EB10C(60.0f);
}

// not matching (regswaps)
void CCheckPointManager::fn_801EB130(void) {
    unkC8 = 0;
    unkDE = 0;

    for (s32 i = 0; i < ARRAY_LENGTH(unk04); i++) {
        if (unk04[i].unk0) {
            unk04[i].unk8 =  (unk04[i].unk2 * 100) / unk04[i].unk0;
            unk04[i].unkC =  (unk04[i].unk4 * 100) / unk04[i].unk0;
            unk04[i].unk10 = (unk04[i].unk6 * 100) / unk04[i].unk0;
        }
    }

    for (s32 i = 0; i < unkC4; i++) {
        if (!unk04[i].unk0) {
            continue;
        }

        bool check = (!doUnkCheck(unkA4[i]->unk0C, unk04[i].unk6, unk04[i].unk10)) || 
                      (doUnkCheck(unkA4[i]->unk0A, unk04[i].unk2, unk04[i].unk8));
        if (!check) {
            continue;
        }

        if (unkA4[i]->flags & GRADE_CRITERIA_FLAG_UNK0) {
            unkC8 = 1;
            memset(unkE0[0], 0, sizeof(unkE0[0]) - 2);
            wcscat(unkE0[0], reinterpret_cast<const wchar_t *>(unkA4[i]->mesgNegative));
            break;
        }

        if (unkC8 < 3) {
            memset(unkE0[unkC8], 0, sizeof(unkE0[unkC8]) - 2);
            wcscat(unkE0[unkC8], unk2E8[unkC8]);
            wcscat(unkE0[unkC8], reinterpret_cast<const wchar_t *>(unkA4[i]->mesgNegative));

            if (unkC8 > 0) {
                s32 chari = wcslen(unk2E8[unkC8]);
                unkE0[unkC8][chari] = fn_801EC270(unkE0[unkC8][chari]);
            }

            unkC8++;
        }
    }

    bool goodC8 = unkC8 > 0;
    s32 unki = 0;
    s32 unkj = 0;
    s32 sp8[3];
    for (s32 i = 0; i < unkC4; i++) {
        if (!unk04[i].unk0) {
            continue;
        }
        if (unkA4[i]->checkUnk08()) {
            continue;
        }
        unki++;
        
        if (unk04[i].unk6) {
            continue;
        }
        if (doUnkCheck(unkA4[i]->unk08, unk04[i].unk2, unk04[i].unk8)) {
            continue;
        }
        unkj++;

        if (goodC8) {
            if (unkDE) {
                unkC8--;
            }
            memset(unkE0[unkC8], 0, sizeof(unkE0[unkC8]) - 2);
            wcscat(unkE0[unkC8], reinterpret_cast<const wchar_t *>(unkA4[i]->mesgPositive));
            unkDE = 1;
            unkC8++;
        }
        else {
            if (unkC8 < 3) {
                sp8[unkC8] = i;
                unkC8++;
            }
            else {
                sp8[0] = sp8[1];
                sp8[1] = sp8[2];
                sp8[2] = i;
            }
        }
    }

    if (!goodC8) {
        for (s32 i = 0; i < unkC8; i++) {
            memset(unkE0[i], 0, sizeof(unkE0[i]) - 2);
            wcscat(unkE0[i], unk2E8[i]);
            wcscat(unkE0[i], reinterpret_cast<const wchar_t *>(unkA4[sp8[i]]->mesgPositive));
            if (i > 0) {
                s32 chari = wcslen(unk2E8[i]);
                unkE0[i][chari] = fn_801EC270(unkE0[i][chari]);
            }
        }
    }

    bool isHi = false;
    bool tempbool = false;

    bool badC8 = !goodC8;
    if (badC8 && (unki > 0)) {
       tempbool = true;
    }
    if (tempbool && (unkj == unki)) {
       isHi = true;
    }

    unkDF = ((unkj > 0) && (!isHi) && badC8) ? 1 : 0;

    unk2FC = getUnk2FCGrade(isHi, goodC8);

    if (unkC8 == 0) {
       memset(unkE0[0], 0, sizeof(unkE0[0]) - 2);
       wcscat(unkE0[0], unk2F8);
       unkC8 = 1;
    }
}

u8 CCheckPointManager::fn_801EB7A8(void) {
    return unkDE;
}

u32 CCheckPointManager::fn_801EB7B0(void) {
    return (unkDE != 0) ? (unkC8 - 1) : unkC8;
}

wchar_t *CCheckPointManager::fn_801EB7D0(s32 i) {
    return unkE0[i];
}

wchar_t *CCheckPointManager::fn_801EB7E0(void) {
    return fn_801EB7D0(unkC8 - 1);
}

wchar_t *CCheckPointManager::fn_801EB7F8(void) {
    return unk2E8[3];
}

u8 CCheckPointManager::fn_801EB800(void) {
    return unkDF;
}

s32 CCheckPointManager::fn_801EB808(s32 i) {
    s32 retVal = 0;
    if (i == -1) {
        for (s32 j = 0; j < unkC4; j++) {
            retVal += unk04[j].unk0;
        }
    }
    else {
        retVal = unk04[i].unk0;
    }
    return retVal;
}

s32 CCheckPointManager::fn_801EB8FC(s32 i) {
    s32 retVal = 0;
    if (i == -1) {
        for (s32 j = 0; j < unkC4; j++) {
            retVal += unk04[j].unk2;
        }
    }
    else {
        retVal = unk04[i].unk2;
    }
    return retVal;
}

s32 CCheckPointManager::fn_801EB9F0(s32 i) {
    s32 retVal = 0;
    if (i == -1) {
        for (s32 j = 0; j < unkC4; j++) {
            retVal += unk04[j].unk4;
        }
    }
    else {
        retVal = unk04[i].unk4;
    }
    return retVal;
}

s32 CCheckPointManager::fn_801EBAE4(s32 i) {
    s32 retVal = 0;
    if (i == -1) {
        for (s32 j = 0; j < unkC4; j++) {
            retVal += unk04[j].unk6;
        }
    }
    else {
        retVal = unk04[i].unk6;
    }
    return retVal;
}

f32 CCheckPointManager::fn_801EBBD8(s32 i) {
    s32 temp0 = fn_801EB808(i);
    s32 temp1 = fn_801EB8FC(i);

    return (temp0 == 0) ? 0.0f : ((f32)temp1 / (f32)temp0);
}

f32 CCheckPointManager::fn_801EBE00(s32 i) {
    s32 temp0 = fn_801EB808(i);
    s32 temp1 = fn_801EB9F0(i);

    return (temp0 == 0) ? 0.0f : ((f32)temp1 / (f32)temp0);
}

f32 CCheckPointManager::fn_801EC028(s32 i) {
    s32 temp0 = fn_801EB808(i);
    s32 temp1 = fn_801EBAE4(i);

    return (temp0 == 0) ? 0.0f : ((f32)temp1 / (f32)temp0);
}

void CCheckPointManager::fn_801EC250(s32 i, wchar_t *string) {
    unk2E8[i] = string;
}

void CCheckPointManager::fn_801EC260(wchar_t *string) {
    unk2E8[3] = string;
}

void CCheckPointManager::fn_801EC268(wchar_t *string) {
    unk2F8 = string;
}

wchar_t CCheckPointManager::fn_801EC270(wchar_t c) {
    static const wchar_t upper[26] = { 
        'A', 'B', 'C', 'D', 'E', 'F', 'G',
        'H', 'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q', 'R', 'S', 'T', 'U',
        'V', 'W', 'X', 'Y', 'Z' };
    static const wchar_t lower[26] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g',
        'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u',
        'v', 'w', 'x', 'y', 'z' };

    for (int i = 0; i < 26; i++) {
        if (c == upper[i]) {
            return lower[i];
        }
    }
    return c;
}
