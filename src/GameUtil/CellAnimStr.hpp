#ifndef GAMEUTIL_CELLANIM_STR_HPP
#define GAMEUTIL_CELLANIM_STR_HPP

#include <revolution/types.h>

#include <revolution/TPL.h>
#include <revolution/GX.h>

/*
 * Structures for CellAnim
 */

struct CellAnim_CellOBJ {
    u16 chrX, chrY; /* X- and Y absolute pixel coordinates into the character data */
    u16 width, height; /* Width and height of the object in pixels */
    u16 chrIndexCI; /* Index into bank character palette if character data is in CI format */
    s16 posX, posY; /* X- and Y-translation of the object in pixels */
    f32 scaleX, scaleY; /* X- and Y-scaling factor of the object */
    f32 angle; /* Rotation angle of the object in degrees */
    bool flipX, flipY; /* X- and Y-flip of object is enabled */
    u8 opacity; /* Alpha multiplier of object (0..255) */
};

struct CellAnim_Cell {
    u16 objCount; /* Number of objects in this cell */
    CellAnim_CellOBJ *objArr; /* Contiguous array of objects in this cell */
};

struct CellAnim_AnimKey {
    u16 cellIndex; /* Index of the cell to be displayed */
    u16 frameCount; /* Amount of frames that the key lasts for (0 is allowed) */
    s16 posX, posY; /* X- and Y-translation of the key in pixels */
    f32 scaleX, scaleY; /* X- and Y-scaling factor of the key */
    f32 angle; /* Rotation angle of the key in degrees */
    u8 opacity; /* Alpha multiplier of key (0..255) */
};

struct CellAnim_Anim {
    u16 keyCount; /* Number of keys in this animation */
    CellAnim_AnimKey *keyArr; /* Contiguous array of keys in this animation */

    u16 findKeyAtFrame(f32 frame) const {
        f32 frames = 0.0f;

        for (u16 i = 0; i < keyCount; i++) {
            frames += keyArr[i].frameCount;
            if (frames > frame) {
                return i;
            }
        }

        return keyCount - 1;
    }

    f32 getFrameOfKey(u16 keyIndex) const {
        f32 frame = 0.0f;
        for (u16 i = 0; i < keyIndex; i++) {
            frame += keyArr[i].frameCount;
        }

        return frame;
    }
};

struct CellAnim_Bank {
    TPLPalette *chrPalette; /* TPL Palette containing all character data */
    GXTexObj *texObj; /* Texture object containing character data (used if usingTexObj is set) */

    bool loaded; /* Signifies that this bank is active & ready for use */

    bool chrIsCI; /* Character data is in CI (color-index) format */
    bool usingTexObj; /* texObj will be used to obtain the character data instead of chrPalette */

    u16 chrIndex; /* Index into chrPalette for the character data */
    u16 chrWidth, chrHeight; /* Width and height of the character data in pixels */

    u16 cellCount; /* Number of cells in this bank */
    u16 animCount; /* Number of animations in this bank */
    CellAnim_Cell *cellArr; /* Contiguous array of cells in this bank */
    CellAnim_Anim *animArr; /* Contiguous array of animations in this bank */
};

/*
 * Binary structures (for BRCAD format)
 */

struct CellAnimBin_Header {
    u32 revision; /* Equal to 20100312 (12 Mar 2010) */

    bool chrIsCI; /* Character data is in CI (color-index) format  */
    u8 _reserved_06[3];
    u16 chrIndex; /* Index into TPL Palette for the character data */
    u16 _reserved_0A;
    u16 chrWidth, chrHeight; /* Width and height of the character data in pixels */

    u16 cellCount; /* Number of cells */
    u16 _reserved_12;
};

struct CellAnimBin_Cell {
    u16 objCount; /* Number of objects in this cell */
    u16 _reserved_02;
};

struct CellAnimBin_CellOBJ {
    u16 chrX, chrY; /* X- and Y absolute pixel coordinates into the character data */
    u16 width, height; /* Width and height of the object in pixels */
    u16 chrIndexCIRel; /* Relative index into bank character palette if character data is in CI format */
    u16 _reserved_0A;
    s16 posX, posY; /* X- and Y-translation of the object in pixels */
    f32 scaleX, scaleY; /* X- and Y-scaling factor of the object */
    f32 angle; /* Rotation angle of the object in degrees */
    bool flipX, flipY; /* X- and Y-flip of object is enabled */
    u8 opacity; /* Alpha multiplier of object (0..255) */
    u8 _reserved_1F;
};

struct CellAnimBin_AnimHdr {
    u16 animCount; /* Number of animations */
    u16 _reserved_02;
};

struct CellAnimBin_Anim {
    u16 keyCount; /* Number of keys in this animation */
    u16 _reserved_02;
};

struct CellAnimBin_AnimKey {
    u16 cellIndex; /* Index of the cell to be displayed */
    u16 frameCount; /* Amount of frames that the key lasts for (0 is allowed) */
    s16 posX, posY; /* X- and Y-translation of the key in pixels */
    f32 scaleX, scaleY; /* X- and Y-scaling factor of the key */
    f32 angle; /* Rotation angle of the key in degrees */
    u8 opacity; /* Alpha multiplier of key (0..255) */
    u8 _reserved_15[3];
};

#endif
