#ifndef GAME_EXCONTROLLER_HPP
#define GAME_EXCONTROLLER_HPP

#include <revolution/types.h>

#include "Controller.hpp"

class CExController : public CController {
public:
    CExController(s32 channel);

    bool fn_8008CDAC(void);
    bool fn_8008CE98(void);

    // CController::CreateFn
    static CController *create(s32 channel) {
        return static_cast<CController *>(new CExController(channel));
    }

private:
    char _pad[0x52f8 - 0x13b8];
};

#endif