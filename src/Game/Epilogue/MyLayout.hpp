#ifndef GAME_EPILOGUE_MYLAYOUT_HPP
#define GAME_EPILOGUE_MYLAYOUT_HPP

#include <revolution/types.h>

#include "Layout.hpp"

namespace Epilogue {

void fn_8000B398(const char *);
void fn_8000B3D4(const char *);
void fn_8000B410(const char *);

class CMyLayout : public CLayout {
public:
    virtual ~CMyLayout(void);
    virtual void _10(void);

    CMyLayout(void) {
        setAnimationCount(0);
    }
};

} // namespace Epilogue

#endif
