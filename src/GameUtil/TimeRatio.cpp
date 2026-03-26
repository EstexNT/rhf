#include "TimeRatio.hpp"

#include "TickFlowManager.hpp"

#include <nw4r/math.h>

CTimeRatio::~CTimeRatio(void) {}

void CTimeRatio::fn_801E9DE8(BOOL unk) {
    if (mTicking) {
        if (unk) {
            mLinearT += gTickFlowManager->fn_801E3EA8(32);
            if (mStopAtMaxT && (mLinearT >= mMaxT)) {
                mLinearT = mMaxT;
                mTicking = false;
            }
            fn_801E9EBC(); // Calculate mEasedT.
        }
        else {
            mLinearT += gTickFlowManager->fn_801E2698();
            if (mStopAtMaxT && (mLinearT >= mMaxT)) {
                mLinearT = mMaxT;
                mTicking = false;
            }
            fn_801E9EBC(); // Calculate mEasedT.
        }
    }
    fn_801E9EBC(); // Calculate mEasedT .. again?
}

// not matching (regswaps)
void CTimeRatio::fn_801E9EBC(void) {    
    f32 easedT = 0.0f;
    if (mMaxT != 0.0f) {
        easedT = mLinearT / mMaxT;

        switch (mEasingType) {
        case 1: {
            f32 powered = 1.0f;
            if (easedT < 0.0f) {
                easedT *= -1.0f;
            }

            for (s32 i = 0; i < mEasingPower; ++i) {
                powered *= easedT;
            }
            
            f32 scaledT = mLinearT * mEasingScale;
            f32 powerFactor = 1.0f - powered;
            f32 invNormT = 1.0f - (scaledT / mMaxT);
            f32 invEasedT = invNormT * powerFactor;
            easedT = 1.0f - invEasedT;
        } break;

        case 2: {
            easedT *= 2.0f;
            if (easedT < 1.0) {
                f32 powered = 1.0f;
                if (easedT < 0.0f) {
                    easedT *= -1.0f;
                }

                for (s32 i = 0; i < mEasingPower; i++) {
                    powered *= easedT;
                }

                f32 doubleT = mLinearT * 2.0;
                f32 powerFactor = 1.0f - powered;
                f32 invNormT = 1.0f - ((doubleT * mEasingScale) / mMaxT);
                f32 invEasedT = invNormT * powerFactor;
                easedT = 1.0f - invEasedT;
            }
            else {
                f32 powered = 1.0f;
                
                easedT -= 2.0f;
                if (easedT < 0.0f) {
                    easedT *= -1.0f;
                }

                for (s32 i = 0; i < mEasingPower; i++) {
                    powered *= easedT;
                }

                f32 invT = (mMaxT -  mLinearT) * 2.0;
                f32 powerFactor = 1.0f - powered;
                f32 invNormT = 1.0f - ((invT * mEasingScale) / mMaxT);
                f32 invEasedT = invNormT * powerFactor;
                easedT = -(1.0f - invEasedT) + 2.0;
            }

            easedT /= 2.0f;
        } break;

        case 3: {
            f32 powered = 1.0f;
            easedT -= 1.0f;
            if (easedT < 0.0f) {
                easedT *= -1.0f;
            }

            for (s32 i = 0; i < mEasingPower; i++) {
                powered *= easedT;
            }

            f32 invScaledT = (mMaxT -  mLinearT) * mEasingScale;
            f32 powerFactor = 1.0f - powered;
            f32 invNormT = 1.0f - (invScaledT / mMaxT);
            f32 invEasedT = invNormT * powerFactor;
            easedT = -(1.0f - invEasedT) + 1.0;
        } break;

        case 4: {
            easedT *= 2.0f;
            if (easedT < 1.0) {
                f32 power = 1.0f;

                easedT -= 1.0f;
                if (easedT < 0.0f) {
                    easedT *= -1.0f;
                }

                for (s32 i = 0; i < mEasingPower; i++) {
                    power *= easedT;
                }

                f32 f5 = -((2.0 * mLinearT) - mMaxT);
                
                f32 f4 = (1.0f - power);
                f32 f2 = mEasingScale * f5;
                f4 *= (1.0f - (f2 / mMaxT));
                f32 f1 = -(1.0f - f4); 
                easedT = (1.0 + f1);
            }
            else {
                f32 powered = 1.0f;
                
                easedT -= 1.0f;
                if (easedT < 0.0f) {
                    easedT *= -1.0f;
                }

                for (s32 i = 0; i < mEasingPower; i++) {
                    powered *= easedT;
                }

                f32 negT = (mLinearT * 2.0) - mMaxT;
                f32 powerFactor = 1.0f - powered;
                f32 invNormT = 1.0f - ((negT * mEasingScale) / mMaxT);
                f32 invEasedT = invNormT * powerFactor;
                easedT = 1.0f - invEasedT;

                easedT += 1.0f;
            }

            easedT = easedT / 2.0f;
        } break;

        default:
            break;
        }
    }

    mEasedT = easedT;

    _14();
}

void CTimeRatio::_14(void) {}

void CTimeRatio::fn_801EA4D4(f32 addTime) {
    mLinearT += addTime;
    if (mStopAtMaxT && (mLinearT >= mMaxT)) {
        mLinearT = mMaxT;
        mTicking = false;
    }
    fn_801E9EBC();
}

void CTimeRatio::fn_801EA50C(f32 newTime) {
    mLinearT = newTime;
    fn_801E9EBC();
}

void CTimeRatio::fn_801EA514(f32 newTime, f32 newMaxTime) {
    mMaxT = newMaxTime;
    mLinearT = newTime;
    fn_801E9EBC();
    mTicking = true;
}

void CTimeRatio::fn_801EA550(f32 newTime, f32 newMaxTime, bool stopAtMaxTime) {
    mStopAtMaxT = stopAtMaxTime;
    mMaxT = newMaxTime;
    mLinearT = newTime;
    fn_801E9EBC();
    mTicking = true;
}


CTRFloat::CTRFloat(void) :
    CTimeRatio()
{
    mOutputEnd = 0.0f;
    mTarget = 0.0f;
    mMaxT = 48.0f;
    mLinearT = 0.0f;
    fn_801E9EBC(); // Calculate initial mEasedT.
    mTicking = false;
}

CTRFloat::~CTRFloat(void) {}

void CTRFloat::fn_801EA698(f32 a, f32 b) {
    mOutputEnd = a;
    mTarget = b;
}

void CTRFloat::_14(void) {
    f32 b = mTarget;
    f32 a = mOutputEnd;
    f32 t = mEasedT;
    
    f32 delta = b - a;
    mOutputStart = a + delta * t;
}

CTRParabola::CTRParabola(void) {
    fn_801EA8E0(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    mMaxT = 48.0f;
    mLinearT = 0.0f;
    fn_801E9EBC(); // Calculate initial mEasedT.
    mTicking = false;
}

CTRParabola::~CTRParabola(void) {}

// not matching (float regswap in the else block)
void CTRParabola::fn_801EA8E0(f32 x0, f32 y0, f32 velY0, f32 x1, f32 y1, f32 velY1, f32 curvature) {
    mOutputStart = x0;
    mY0 = y0;
    mZ0 = velY0;
    
    mOutputEnd = x1;
    mY1 = y1;
    mZ1 = velY1;
    
    calcParabola(curvature, mY1 - mY0);
}

// not matching (needs shuffling around)
void CTRParabola::_14(void) {
    f32 t = mEasedT;

    // a + (b - a) * t
    mCurrentX = mOutputStart + (mOutputEnd - mOutputStart) * t;
    // ax^2 + bx + c
    mCurrentY = (mA * (t * t)) + (mB * t) + mY0;
    // a + (b - a) * t
    mCurrentZ = mZ0 + (mZ1 - mZ0) * t;
}
