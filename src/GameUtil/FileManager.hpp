#ifndef GAMEUTIL_FILEMANAGER_HPP
#define GAMEUTIL_FILEMANAGER_HPP

#include <revolution/types.h>

#include <revolution/DVD.h>
#include <revolution/ARC.h>

#include <RVLFaceLibrary.h>

#include "Mem.hpp"

#include "Singleton.hpp"

class CFileManager;
extern CFileManager *gFileManager;

class CFileManager : public TSingleton<CFileManager> {
public:
    static const s32 DEFAULT_MAX_FILE_COUNT = 95;
    static const s32 DEFAULT_MAX_ARCHIVE_COUNT = 95;

    static const EHeapMEM DEFAULT_HEAP = eHeap_MEM2;
    static const s32 DEFAULT_ALIGN = 32;

public:
    virtual void _08(void);
    virtual ~CFileManager(void);
    virtual void _10(
        s32 maxFileCount = DEFAULT_MAX_FILE_COUNT,
        s32 maxArchiveCount = DEFAULT_MAX_ARCHIVE_COUNT
    );
    virtual void _14(void);

    CFileManager(void);

    void setLocaleDir(const char *localeDir);
    const char *getLocaleDir(void);

    // NOTE: alignment must be a multiple of 32, or DVD read will fail!
    void *loadFile(
        const char *path,
        EHeapMEM heap = DEFAULT_HEAP, s32 alignment = DEFAULT_ALIGN
    );

    bool getDVDBusy(void);
    void waitDVD(void);
    void waitDVD2(void); // NOTE: functionally equivalent to waitDVD

    // NOTE: alignment must be a multiple of 32, or DVD read will fail!
    void startArchive(
        s32 arcIndex, const char *path,
        EHeapMEM heap = DEFAULT_HEAP, s32 alignment = DEFAULT_ALIGN
    );
    void endArchive(s32 arcIndex);

    u32 arcGetFileLen(s32 arcIndex, const char *path);
    void *arcGetFileAddr(s32 arcIndex, const char *path);
    void *arcGetAddr(s32 arcIndex);
    bool getArcFree(s32 arcIndex);
    bool getArcReady(s32 arcIndex);
    bool getArcIdle(void);
    void waitArc(s32 arcIndex);
    void waitAllArc(void);

    void updateArc(void);
    void updateDVD(void);

    void setDVDErrorFuncF(void (*DVDErrorFuncF)(void)) {
        mDVDErrorFuncF = DVDErrorFuncF;
    }
    void setDVDErrorFuncB(void (*DVDErrorFuncB)(void)) {
        mDVDErrorFuncB = DVDErrorFuncB;
    }

    u32 getRFLResLen(void) {
        return arcGetFileLen(1, RFLGetArcFilePath());
    }
    void *getRFLResAddr(void) {
        return arcGetFileAddr(1, RFLGetArcFilePath());
    }

    static void *expandSZS(
        void *data, BOOL deleteSrc,
        EHeapMEM heap = DEFAULT_HEAP, s32 alignment = DEFAULT_ALIGN
    );

    static void waitTick(void) {
        gFileManager->updateDVD();
        gFileManager->updateArc();
        OSSleepTicks(OS_MSEC_TO_TICKS(10ll));
    }

private:
    s32 getFileInfoIndex(DVDFileInfo *fileInfo) {
        s32 index = -1;
        for (s32 i = 0; i < mMaxFileCount; i++) {
            if (&mDVDFileInfo[i] == fileInfo) {
                index = i;
                break;
            }
        }
        return index;
    }

    void dvdCallbackArcImpl(s32 result, DVDFileInfo *fileInfo);

    static void dvdCallbackFile(s32 result, DVDFileInfo *fileInfo);
    static void dvdCallbackArc(s32 result, DVDFileInfo *fileInfo);

    static void *tryExpandTask(void *data, BOOL deleteSrc, s32 arcInfoIdx, EHeapMEM heap, s32 alignment);
    static void *expandTaskFunc(void *);

    static bool expandSZSImpl(u8 *src, u8 *dst, u32 srcSize, u32 dstSize, s32 idx, BOOL deleteSrc);

public:
    enum EArchiveInfoState {
        eArchiveInfoState_Free = 0,          // Slot is unassigned and available.
        eArchiveInfoState_Loading = 1,       // Waiting for DVD read ..
        eArchiveInfoState_Loaded = 2,        // Waiting for decompression to start ..
        eArchiveInfoState_Decompressing = 3, // Waiting for decompression to finish ..
        eArchiveInfoState_Decompressed = 4,  // Waiting for ARCInitHandle ..
        eArchiveInfoState_Ready = 5          // Ready for access.
    };

    struct ArchiveInfo {
        DVDFileInfo *dvdFileInfo; // Will be NULL when ready for access.
        ARCHandle arcHandle;
        u8 *data;
        EHeapMEM heapType;
        u16 memGroup;
        bool compressed; // The source file was compressed.
        EArchiveInfoState state;
    };

    struct UnusedFileSub {
        u8 _pad00[0x44];
    };

public:
    char mLocaleDir[4];

    s32 mMaxFileCount;
    DVDFileInfo *mDVDFileInfo; // DVDFileInfo[mMaxFileCount]
    UnusedFileSub *mUnusedFileSub; // UnusedFileSub[mMaxFileCount]
    bool *mDVDFileInfoActive; // bool[mMaxFileCount]; describes if a mDVDFileInfo slot at the specified index is in use

    s32 mMaxArchiveCount;
    ArchiveInfo *mArchiveInfo; // ArchiveInfo[mMaxArchiveCount]

    u8 _pad20[0x10];

    OSThread mThread;
    u32 *mThreadStack;

    void (*mDVDErrorFuncF)(void);
    void (*mDVDErrorFuncB)(void);
};

#endif
